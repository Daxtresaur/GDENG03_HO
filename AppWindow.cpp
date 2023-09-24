#include "AppWindow.h"
#include <Windows.h>

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	WINDOW::onCreate();
	GRAPHICS_ENGINE::get()->init();

	m_swap_chain = GRAPHICS_ENGINE::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*
	vertex list[] =
	{
		//X - Y - Z
		{0.f, 0.0f, 0.0f}, // POS1
		{0.f, 1.f, 0.0f}, // POS2
		{1.f, 1.f, 0.0f},
		{1.f, 0.f, 0.f},
		{0.f, 0.0f, 0.0f},
		{0.f, 0.0f, 0.0f}
	};
	*/

	Quad* quadA = new Quad(
		changingvertex{ -0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 },
		changingvertex{ -0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 },
		changingvertex{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },
		changingvertex{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	);

	primitive_List.push_back(quadA);

	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(Triangle1.acq_VerX_List());

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GRAPHICS_ENGINE::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	std::vector<changingvertex> vertexVector;
	changingvertex* currentSet = nullptr;
	int currentCount = 0;
	int totalCount = 0;

	for (int i = 0; i < primitive_List.size(); i++) {
		currentSet = primitive_List[i]->acq_VerX_List(&currentCount);
		for (int j = 0; j < currentCount; j++) {
			vertexVector.push_back(currentSet[j]);
		}
		totalCount += currentCount;
	}

	changingvertex* complete_vertex_list = new changingvertex[totalCount];
	std::copy(vertexVector.begin(), vertexVector.end(), complete_vertex_list);

	m_vs = GRAPHICS_ENGINE::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(complete_vertex_list, sizeof(vertex), totalCount, shader_byte_code, size_shader);

	GRAPHICS_ENGINE::get()->releaseCompiledShader();

	GRAPHICS_ENGINE::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GRAPHICS_ENGINE::get()->createPixelShader(shader_byte_code, size_shader);
	GRAPHICS_ENGINE::get()->releaseCompiledShader();

	delete[] complete_vertex_list;

	constant cc;
	cc.m_angle = 0;

	m_cb = GRAPHICS_ENGINE::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	WINDOW::onUpdate();
	//CLEAR THE RENDER TARGET 
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.2, 0.6, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GRAPHICS_ENGINE::get()->getImmediateDeviceContext(), &cc);

	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	UINT vertexIndex = 0;
	for (int i = 0; i < primitive_List.size(); i++) {
		primitive_List[i]->drawShape(&vertexIndex);
	}


	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	WINDOW::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	for (int i = 0; i < primitive_List.size(); i++) {
		delete primitive_List[i];
	}

	GRAPHICS_ENGINE::get()->release();
}

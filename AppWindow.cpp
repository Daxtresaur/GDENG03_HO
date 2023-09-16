#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

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

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f}, // POS1
		{0.0f,0.5f,0.0f}, // POS2
		{ 0.5f,-0.5f,0.0f}
	};

	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GRAPHICS_ENGINE::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GRAPHICS_ENGINE::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);



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
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GRAPHICS_ENGINE::get()->setShaders();
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);


	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	WINDOW::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	GRAPHICS_ENGINE::get()->release();
}

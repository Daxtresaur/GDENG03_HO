#include "AppWindow.h"
#include <Windows.h>
#include "VECTOR3D.h"
#include "MATRIX4X4.h"

#include "RENDERER.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->onDestroy();
	}
}

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

	RENDERER::initialize();
	vertexAnim list_anim[] =
	{
		//X - Y - Z
		{-0.1f,-0.3f,0.0f,    -0.3f,-0.3f,0.0f,   1,1,0,  0,1,0 }, // POS1
		{-0.1f,0.95f,0.0f,     -0.3f,0.5f,0.0f,    1,1,0,  0,1,1 },// POS2
		{ 0.1f,-0.95f,0.0f,    0.3f,-0.5f,0.0f,   0,1,1,  1,0,0 },// POS2
		{ 0.1f,0.5f,0.0f,      0.3f,0.5f,0.0f,    1,1,1,  0,0,1 }

	};

	vertexAnim list_anim2[] =
	{
		//X - Y - Z
		{-0.78f,-0.8f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.9f,0.08f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.1f,-0.2f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ -0.05f,0.15f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }

	};

	vertexAnim list_anim3[] =
	{
		//X - Y - Z
		{  -0.75f,-0.8f,0.0f,  -0.15f,-0.4f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{  -0.9f,-0.1f,0.0f, -0.05f,0.45f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{  0.85f,-0.55f,0.0f, 0.0f,-0.75f,0.0f,   0,0,1,  1,0,0 },// POS2
		{  -0.75f,-0.8f,0.0f,  0.85f,0.4f,0.0f,     1,1,1,  0,0,1 }
	};

	vertex list1[] =
	{
		{-0.1f,-0.3f,0.0f,   1,1,0}, // POS1
		{-0.1f,0.95f,0.0f,    1,0,0}, // POS2
		{ 0.1f,-0.95f,0.0f,   0,0,1}, // POS3
		{ 0.1f,0.5f,0.0f,    0,1,0.4f}
	};

	vertex list2[] =
	{
		{-0.9f,-0.9f,0.0f,   1,0,0}, // POS1
		{-0.9f,0.9f,0.0f,    0,1,0}, // POS2
		{ -0.3f,-0.9f,0.0f,   0,0,1}, // POS3
		{ -0.3f,0.9f,0.0f,    1,1,0}
	};

	vertex list3[] =
	{
		{0.3f,-0.6f,0.0f,   1,1,0},
		{0.3f,0.7f,0.0f,    0,1,1},
		{ 0.6f,-0.9f,0.0f,   0,0,1},
		{ 0.9f,0.8f,0.0f,    1,0.3f,0.4f}
	};

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GRAPHICS_ENGINE::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GRAPHICS_ENGINE::get()->createVertexShader(shader_byte_code, size_shader);

	RENDERER::getInstance()->initializeQuadsAnim(list_anim2, shader_byte_code, size_shader);

	GRAPHICS_ENGINE::get()->releaseCompiledShader();

	GRAPHICS_ENGINE::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GRAPHICS_ENGINE::get()->createPixelShader(shader_byte_code, size_shader);
	GRAPHICS_ENGINE::get()->releaseCompiledShader();

	RENDERER::getInstance()->initializeQuadConst();

}

void AppWindow::onUpdate()
{
	WINDOW::onUpdate();
	//CLEAR THE RENDER TARGET 
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3, 0.3, 0.3, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = getClientWindowRect();
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (auto const& i :RENDERER::getInstance()->getQuadList()) {
		i->drawShape(m_vs, m_ps);
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	WINDOW::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	GRAPHICS_ENGINE::get()->release();
}

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
	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GRAPHICS_ENGINE::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GRAPHICS_ENGINE::get()->createVertexShader(shader_byte_code, size_shader);

	RENDERER::getInstance()->initializeCube("CUBE1",shader_byte_code, size_shader, 0);
	RENDERER::getInstance()->initializeCube("CUBE2", shader_byte_code, size_shader, 0);
	RENDERER::getInstance()->initializeCube("CUBE3", shader_byte_code, size_shader, 0);
	RENDERER::getInstance()->initializeCube("CUBE4", shader_byte_code, size_shader, 0);


	GRAPHICS_ENGINE::get()->releaseCompiledShader();

	GRAPHICS_ENGINE::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GRAPHICS_ENGINE::get()->createPixelShader(shader_byte_code, size_shader);
	GRAPHICS_ENGINE::get()->releaseCompiledShader();

	RENDERER::getInstance()->initializeCubeConst();

	

}

void AppWindow::onUpdate()
{

	WINDOW::onUpdate();
	//CLEAR THE RENDER TARGET 
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3, 0.3, 0.3, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW

	RECT rc = getClientWindowRect();
	
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (auto const& i :RENDERER::getInstance()->getCubeList()) {
		std::cout << "Marker App 1" << std::endl;
		i->drawShape(m_vs, m_ps);
		std::cout << "Marker App 2" << std::endl;
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

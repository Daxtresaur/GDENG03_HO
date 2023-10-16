#include "AppWindow.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	EngineTime::initialize();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = getClientWindowRect();

	std::cout << "hwnd: " << this->m_hwnd;
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	//compile basic vertex shader
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->m_vs = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	for (int i = 0; i < 15; i++) {
		float x = MathUtils::randomFloat(-0.75, 0.75f);
		float y = MathUtils::randomFloat(-0.75, 0.75f);
		float z = MathUtils::randomFloat(-0.75, 0.75f);

		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		cubeObject->setAnimSpeed(MathUtils::randomFloat(-3.75f, 3.75f));
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
		this->cubeList.push_back(cubeObject);
	}

	graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

	//compile basic pixel shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_ps = graphEngine->createPixelShader(shaderByteCode, sizeShader);

	graphEngine->releaseCompiledShader();
}

void AppWindow::onUpdate()
{

	ticks += EngineTime::getDeltaTime() * 1.0f;

	InputSystem::getInstance()->update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0.2f, 0.2f, 0.2f, 1);

	RECT rc = getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->update(EngineTime::getDeltaTime());
		cubeList[i]->draw(width, height, m_vs, m_ps);
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vb->release();
	m_ib->release();
	m_cb->release();

	m_vs->release();
	m_ps->release();

	InputSystem::destroy();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	cout << "onkeydown:\n";
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "W pressed\n";
	}
}

void AppWindow::onKeyUp(int key)
{
	cout << "onkeyup:\n";
	if (InputSystem::getInstance()->isKeyUp('W'))
	{
		cout << "W released\n";
	}
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}


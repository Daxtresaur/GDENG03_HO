#pragma once
#include <vector>

#include"Window.h"
#include"GraphicsEngine.h"
#include"InputSystem.h"

#include"SwapChain.h"
#include"DeviceContext.h"

#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"ConstantBuffer.h"

#include"VertexShader.h"
#include"PixelShader.h"

#include"AGameObject.h"
#include"Cube.h"

#include"Vector3D.h"
#include"Matrix4x4.h"

#include "MathUtils.h"
#include "Utilities.h"

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	//Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);

private:
	static AppWindow* sharedInstance;

	std::vector<Cube*> cubeList;

	float ticks = 0.0f;

	SwapChain* m_swap_chain;
	
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	VertexShader* m_vs;
	PixelShader* m_ps;
	
};


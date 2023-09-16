#pragma once
#include <d3d11.h>
#include "SWAPCHAIN.h"


class SWAPCHAIN;
class DEVICECONTEXT;
class VERTEXBUFFER;


class GRAPHICS_ENGINE
{
public:
	GRAPHICS_ENGINE();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~GRAPHICS_ENGINE();

	SWAPCHAIN* createSwapChain();
	DEVICECONTEXT* getImmediateDeviceContext();
	VERTEXBUFFER* createVertexBuffer();

	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

	static GRAPHICS_ENGINE* get();
	

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

	// for swap chain creation
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	DEVICECONTEXT* m_imm_device_context;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class SWAPCHAIN;
	friend class VERTEXBUFFER;

};


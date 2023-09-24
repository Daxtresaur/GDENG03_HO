#pragma once
#include <d3d11.h>


class SWAPCHAIN;
class DEVICECONTEXT;
class VERTEXBUFFER;
class CONSTANTBUFFER;
class VERTEXSHADER;
class PIXELSHADER;


class GRAPHICS_ENGINE
{
public:
	GRAPHICS_ENGINE();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~GRAPHICS_ENGINE();

	// Device Creation
	SWAPCHAIN* createSwapChain();
	DEVICECONTEXT* getImmediateDeviceContext();

	VERTEXBUFFER* createVertexBuffer();
	CONSTANTBUFFER* createConstantBuffer();

	VERTEXSHADER* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PIXELSHADER* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

	//Shader Functions
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);


	void releaseCompiledShader();


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

	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class SWAPCHAIN;
	
	friend class VERTEXBUFFER;
	friend class CONSTANTBUFFER;

	friend class VERTEXSHADER;
	friend class PIXELSHADER;
	

};


#pragma once
#include <d3d11.h>


class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;


class GraphicsEngine
{
public:
	GraphicsEngine();

	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();

	~GraphicsEngine();

	static GraphicsEngine* get();

	// Device Creation
	SwapChain* createSwapChain();
	ID3D11Device* getDirect3DDevice();
	DeviceContext* getImmediateDeviceContext();

	VertexBuffer* createVertexBuffer();
	ConstantBuffer* createConstantBuffer();
	IndexBuffer* createIndexBuffer();

	//Shader Functions
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);


private:
	static GraphicsEngine* sharedInstance;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

	// for swap chain creation
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	DeviceContext* m_imm_device_context;

	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class SwapChain;
	
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class IndexBuffer;

	friend class VertexShader;
	friend class PixelShader;
	

};


#include "GraphicsEngine.h"

#include "DeviceContext.h"
#include "SwapChain.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Utilities.h"

#include <d3dcompiler.h>
#include <iostream>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine() : m_feature_level()
{
	m_d3d_device = nullptr;
	m_imm_context = nullptr;

	m_dxgi_device = nullptr;
	m_dxgi_adapter = nullptr;
	m_dxgi_factory = nullptr;

	m_blob = nullptr;
}

bool GraphicsEngine::init()
{
	sharedInstance = new GraphicsEngine();

	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	constexpr UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	constexpr UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	ID3D11DeviceContext* imm_context = NULL;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res)) 
		{
			m_imm_device_context = new DeviceContext(imm_context);
			std::cout << "D3D11Device Created: " << driver_types[driver_type_index] << std::endl;
			break;
		}
			
		++driver_type_index;
	}

	if (FAILED(res))
	{
		return false;
	}

	// Without using CreateDeviceAndSwapChain Swap chain can only be created through idxgifactory
	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();


	m_d3d_device->Release();

	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

ID3D11Device* GraphicsEngine::getDirect3DDevice()
{
	return m_d3d_device;
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", NULL, NULL, &m_blob, &error_blob);

	Utilities::PrintHResult("CompileVertexShader:", hres);
	if (FAILED(hres))
	{

		if (error_blob) {
			OutputDebugString(L"Error blob:");
			OutputDebugString(static_cast<LPCWSTR>(error_blob->GetBufferPointer()));
			error_blob->Release();
		}
		return false;
	}
	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", NULL, NULL, &m_blob, &error_blob);

	Utilities::PrintHResult("CompilePixelShader:", hres);
	if (FAILED(hres))
	{

		if (error_blob) {
			OutputDebugString(L"Error blob:");
			OutputDebugString(reinterpret_cast<LPCWSTR>(error_blob->GetBufferPointer()));
			error_blob->Release();
		}
		return false;
	}
	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine instance;
	return &instance;
}

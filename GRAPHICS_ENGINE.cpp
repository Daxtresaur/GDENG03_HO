#include "GRAPHICS_ENGINE.h"

#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"

#include "VERTEXBUFFER.h"
#include "CONSTANTBUFFER.h"

#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

#include <d3dcompiler.h>

GRAPHICS_ENGINE* GRAPHICS_ENGINE::sharedInstance = nullptr;

GRAPHICS_ENGINE::GRAPHICS_ENGINE()
{
	
}

void GRAPHICS_ENGINE::initialize()
{
	sharedInstance = new GRAPHICS_ENGINE();
	sharedInstance->init();
}

void GRAPHICS_ENGINE::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

bool GRAPHICS_ENGINE::init()
{
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
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
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

	m_imm_device_context = new DEVICECONTEXT(m_imm_context);

	return true;
}

bool GRAPHICS_ENGINE::release()
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
	return true;
}

GRAPHICS_ENGINE::~GRAPHICS_ENGINE()
{
}

SWAPCHAIN* GRAPHICS_ENGINE::createSwapChain()
{
	return new SWAPCHAIN();
}

DEVICECONTEXT* GRAPHICS_ENGINE::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VERTEXBUFFER* GRAPHICS_ENGINE::createVertexBuffer()
{
	return new VERTEXBUFFER();
}

CONSTANTBUFFER* GRAPHICS_ENGINE::createConstantBuffer()
{
	return new CONSTANTBUFFER();
}

VERTEXSHADER* GRAPHICS_ENGINE::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VERTEXSHADER* vs = new VERTEXSHADER();

	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PIXELSHADER* GRAPHICS_ENGINE::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PIXELSHADER* ps = new PIXELSHADER();

	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GRAPHICS_ENGINE::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GRAPHICS_ENGINE::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GRAPHICS_ENGINE::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

GRAPHICS_ENGINE* GRAPHICS_ENGINE::get()
{
	static GRAPHICS_ENGINE engine;
	return &engine;
}

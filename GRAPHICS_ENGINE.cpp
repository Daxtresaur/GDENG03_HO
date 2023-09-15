#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"

GRAPHICS_ENGINE::GRAPHICS_ENGINE()
{
	
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
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_context->Release();
	m_d3d_device->Release();

	m_imm_device_context->release();

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

GRAPHICS_ENGINE* GRAPHICS_ENGINE::get()
{
	static GRAPHICS_ENGINE engine;
	return &engine;
}

#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"

DEVICECONTEXT::DEVICECONTEXT(ID3D11DeviceContext* device_context) :m_device_context(device_context)
{
}

bool DEVICECONTEXT::clearRenderTargetColor(SWAPCHAIN* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);


	return true;
}


bool DEVICECONTEXT::release()
{
	m_device_context->Release();
	delete this;
	return true;
}

DEVICECONTEXT::~DEVICECONTEXT()
{
}
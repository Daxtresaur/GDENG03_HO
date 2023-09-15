#pragma once
#include <d3d11.h>

class SWAPCHAIN;

class DEVICECONTEXT
{
public:
	DEVICECONTEXT(ID3D11DeviceContext* device_context);
	bool clearRenderTargetColor(SWAPCHAIN* swap_chain, float red, float green, float blue, float alpha);

	bool release();
	~DEVICECONTEXT();
private:
	ID3D11DeviceContext* m_device_context;

};


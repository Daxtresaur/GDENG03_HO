#pragma once
#include "d3d11.h"


class DEVICECONTEXT;

class SWAPCHAIN
{
public:
	SWAPCHAIN();
	//Initialize SWAPCHAIN for a window
	bool init(HWND hwnd, UINT width, UINT height);
	//Release the swap chain
	bool release();
	~SWAPCHAIN();

	bool present(bool vsync);


private:
	IDXGISwapChain* m_swap_chain;

	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;

	friend class DEVICECONTEXT;

};


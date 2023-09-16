#pragma once
#include <d3d11.h>

class SWAPCHAIN;
class VERTEXBUFFER;

class DEVICECONTEXT
{
public:
	DEVICECONTEXT(ID3D11DeviceContext* device_context);

	void clearRenderTargetColor(SWAPCHAIN* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VERTEXBUFFER* vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);

	bool release();
	~DEVICECONTEXT();



private:
	ID3D11DeviceContext* m_device_context;

};


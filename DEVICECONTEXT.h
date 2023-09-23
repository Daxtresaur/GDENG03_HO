#pragma once
#include <d3d11.h>

class SWAPCHAIN;
class VERTEXBUFFER;
class VERTEXSHADER;
class PIXELSHADER;

class DEVICECONTEXT
{
public:
	DEVICECONTEXT(ID3D11DeviceContext* device_context);

	void clearRenderTargetColor(SWAPCHAIN* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VERTEXBUFFER* vertex_buffer);

	//Primitive Drawing
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	// Viewport Setup
	void setViewportSize(UINT width, UINT height);

	//Shader Setup
	void setVertexShader(VERTEXSHADER* vertex_shader);
	void setPixelShader(PIXELSHADER* pixel_shader);

	bool release();
	~DEVICECONTEXT();



private:
	ID3D11DeviceContext* m_device_context;

};


#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"

#include "VERTEXBUFFER.h"
#include "CONSTANTBUFFER.h"
#include "INDEXBUFFER.h"

#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

DEVICECONTEXT::DEVICECONTEXT(ID3D11DeviceContext* device_context) :m_device_context(device_context)
{
}

void DEVICECONTEXT::clearRenderTargetColor(SWAPCHAIN* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);

	
}

void DEVICECONTEXT::setVertexBuffer(VERTEXBUFFER* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DEVICECONTEXT::setIndexBuffer(INDEXBUFFER* index_buffer)
{
	m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DEVICECONTEXT::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);

}

void DEVICECONTEXT::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DEVICECONTEXT::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DEVICECONTEXT::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_device_context->RSSetViewports(1, &vp);
}


void DEVICECONTEXT::setVertexShader(VERTEXSHADER* vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DEVICECONTEXT::setPixelShader(PIXELSHADER* pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DEVICECONTEXT::setConstantBuffer(VERTEXSHADER* vertex_shader, CONSTANTBUFFER* buffer)
{
	m_device_context->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DEVICECONTEXT::setConstantBuffer(PIXELSHADER* pixel_shader, CONSTANTBUFFER* buffer)
{
	m_device_context->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
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
#include "CONSTANTBUFFER.h"
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"

CONSTANTBUFFER::CONSTANTBUFFER()
{
}

bool CONSTANTBUFFER::load(void* buffer, UINT size_buffer)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(GRAPHICS_ENGINE::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	return true;
}

void CONSTANTBUFFER::update(DEVICECONTEXT* context, void* buffer)
{
	context->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

bool CONSTANTBUFFER::release()
{
	if (m_buffer)m_buffer->Release();
	delete this;
	return true;
}

CONSTANTBUFFER::~CONSTANTBUFFER()
{
}

#include "VERTEXSHADER.h"
#include "GRAPHICS_ENGINE.h"

VERTEXSHADER::VERTEXSHADER()
{
}

bool VERTEXSHADER::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GRAPHICS_ENGINE::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		return false;

	return true;
}

void VERTEXSHADER::release()
{
	m_vs->Release();
	delete this;
}

VERTEXSHADER::~VERTEXSHADER()
{
}



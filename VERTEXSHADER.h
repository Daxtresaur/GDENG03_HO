#pragma once
#include <d3d11.h>

class GRAPHICS_ENGINE;
class DEVICECONTEXT;

class VERTEXSHADER
{
public:

	VERTEXSHADER();
	void release();
	~VERTEXSHADER();


private:

	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11VertexShader* m_vs;

	friend class GRAPHICS_ENGINE;
	friend class DEVICECONTEXT;
};


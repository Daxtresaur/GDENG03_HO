#pragma once
#include <d3d11.h>

class GRAPHICS_ENGINE;
class DEVICECONTEXT;

class PIXELSHADER
{
public:

	PIXELSHADER();
	void release();
	~PIXELSHADER();


private:

	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11PixelShader* m_ps;

	friend class GRAPHICS_ENGINE;
	friend class DEVICECONTEXT;
};

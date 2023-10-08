#pragma once
#include <iostream>
#include "PRIMITIVE.h"
#include "GRAPHICS_ENGINE.h"
#include "MATRIX4X4.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VECTOR3D.h"

class Cube : public PRIMITIVE
{
public:
	Cube();
	~Cube();

	void initialize() override;
	void destroy() override;

	void initBuffers(void* shader_byte_code, size_t size_shader, int num);
	void initConstBuffers();
	void drawShape(VERTEXSHADER* m_vs,PIXELSHADER* m_ps) override;
	void releaseBuffers();

	void updateTransforms();
	void setInitTransforms(VECTOR3D pos, VECTOR3D rot);

private:

	VERTEXBUFFER* m_vb;
	CONSTANTBUFFER* m_cb;
	INDEXBUFFER* m_ib;

	constant cc;
	double speed = 2;
	bool decrease = false;

	MATRIX4X4 temp;

	float m_delta_pos;
	float m_delta_scale;

	VECTOR3D initPos;
	VECTOR3D initRot;

	Cube(Cube const&) {}
	Cube& operator=(Cube const&) {}

};

#pragma once
#pragma once
#include <iostream>
#include "PRIMITIVE.h"
#include "GRAPHICS_ENGINE.h"
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"
#include "VECTOR3D.h"
#include "Quad.h"

class CUBE : public PRIMITIVE
{
public:
	CUBE();
	~CUBE();

	void initialize(std::string name) override;
	void destroy() override;

	void initBuffers(void* shader_byte_code, size_t size_shader, int num);
	void initConstBuffers();
	void drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps) override;
	void releaseBuffers();

	void updatePosition();

private:
	VERTEXBUFFER* m_vb;
	CONSTANTBUFFER* m_cb;
	INDEXBUFFER* m_ib;

	constant cc;


	//no.2
	VECTOR3D rotation;

	//no.3
	VECTOR3D translation;
	VECTOR3D scaling;
	bool i_trans;
	bool i_scale;


	int num = 0;

	CUBE(CUBE const&) {}
	CUBE& operator=(CUBE const&) {}

};


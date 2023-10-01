#pragma once
#include "PRIMITIVE.h"
#include <iostream>
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include "CONSTANTBUFFER.h"
#include "VERTEXBUFFER.h"
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

struct vertexAnim
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


__declspec(align(16))

struct constant
{
	float m_angle;
};

class Quad : public PRIMITIVE
{
public:
	Quad();
	~Quad();

	void initialize() override;
	void destroy() override;

	void initBuffers(struct vertex list[], void* shader_byte_code, size_t size_shader);
	void initAnimBuffers(struct vertexAnim list[], void* shader_byte_code, size_t size_shader);
	void initConstBuffers();
	void drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps) override;
	void releaseBuffers();

	//changingvertex* acq_VerX_List(int* vertex_count) override;

private:
	VERTEXBUFFER* m_vb;
	CONSTANTBUFFER* m_cb;

	constant cc;
	double speed = 2;
	bool decrease = false;

	Quad(Quad const&) {}
	Quad& operator=(Quad const&) {}
	
};


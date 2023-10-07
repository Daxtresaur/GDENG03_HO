#pragma once
#include <iostream>
#include "PRIMITIVE.h"
#include "GRAPHICS_ENGINE.h"
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

class Quad : public PRIMITIVE
{
public:
	Quad();
	~Quad();

	void initialize(std::string name) override;
	void destroy() override;

	void initBuffers(void* shader_byte_code, size_t size_shader);
	void initAnimBuffers(void* shader_byte_code, size_t size_shader);
	void initConstBuffers();
	void drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps) override;
	void releaseBuffers();

	void updatePosition();

private:
	VERTEXBUFFER* m_vb;
	CONSTANTBUFFER* m_cb;

	constant cc;
	double speed = 2;
	bool decrease = false;

	float m_delta_pos;
	float m_delta_scale;

	Quad(Quad const&) {}
	Quad& operator=(Quad const&) {}

};
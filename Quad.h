#pragma once
#include "PRIMITIVE.h"
#include <iostream>
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include "CONSTANTBUFFER.h"
#include "VERTEXBUFFER.h"
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"


class Quad : public PRIMITIVE
{
public:
	Quad();
	~Quad();

	void initialize(std::string name) override;
	void destroy() override;

	void initBuffers(struct vertexAnim list[], void* shader_byte_code, size_t size_shader);
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


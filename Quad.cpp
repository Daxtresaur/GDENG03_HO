#include "Quad.h"
#include "GRAPHICS_ENGINE.h"
#include "ENGINETIME.h"
#include <vector>
#include<iostream>

Quad::Quad()
{
}

Quad::~Quad()
{
}

void Quad::initialize(std::string name)
{
	PRIMITIVE::initialize(name);
}

void Quad::destroy()
{
	PRIMITIVE::destroy();
}

void Quad::initBuffers(struct vertexAnim list_anim[], void* shader_byte_code, size_t size_shader)
{
	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	m_vb->load(list_anim, sizeof(vertexAnim), 4, shader_byte_code, size_shader);
}

void Quad::initAnimBuffers(struct vertexAnim listAnim[], void* shader_byte_code, size_t size_shader)
{
	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	std::cout << listAnim->position.m_x << std::endl;
	m_vb->load(listAnim, sizeof(vertexAnim), 4, shader_byte_code, size_shader);
}

void Quad::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GRAPHICS_ENGINE::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Quad::drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps)
{
	
	cc.m_angle += static_cast<float>(speed * ENGINETIME::getDeltaTime());
	
	if (!decrease) {
		speed += ENGINETIME::getDeltaTime();
		if (speed >= 10)
		{
			decrease = true;
		}
	}
	if (decrease) {
		speed -= ENGINETIME::getDeltaTime();
		if (speed <= 2)
		{
			decrease = false;
		}
	}

	m_cb->update(GRAPHICS_ENGINE::get()->getImmediateDeviceContext(), &cc);


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::releaseBuffers()
{
}

#include "Triangle.h"
#include "GRAPHICS_ENGINE.h"
#include "ENGINETIME.h"
#include <vector>

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void Triangle::initialize()
{
	PRIMITIVE::initialize();
}

void Triangle::destroy()
{
	PRIMITIVE::destroy();
}

void Triangle::initBuffers(vertex list[], void* shader_byte_code, size_t size_shader)
{
	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	std::cout << list->position.x << std::endl;
	m_vb->load(list, sizeof(vertex), 3, shader_byte_code, size_shader);
}

void Triangle::initAnimBuffers(vertexAnim listAnim[], void* shader_byte_code, size_t size_shader)
{
	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	std::cout << listAnim->position.x << std::endl;
	m_vb->load(listAnim, sizeof(vertexAnim), 4, shader_byte_code, size_shader);
}

void Triangle::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GRAPHICS_ENGINE::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Triangle::drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps)
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
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
}

void Triangle::releaseBuffers()
{
}

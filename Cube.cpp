#include "Cube.h"
#include "Cube.h"
#include <random>
#include "AppWindow.h"
#include "RENDERER.h"
#include "DEVICECONTEXT.h"
#include "CONSTANTBUFFER.h"
#include "ENGINETIME.h"
#include "INDEXBUFFER.h"
#include "VERTEXBUFFER.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::initialize(std::string name)
{
	PRIMITIVE::initialize(name);
}

void Cube::destroy()
{
	PRIMITIVE::destroy();
}

void Cube::initBuffers(void* shader_byte_code, size_t size_shader, int num = 0)
{
	vertexCube cube_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{VECTOR3D(-0.5f,-0.5f,-0.5f),    VECTOR3D(1,0,0),  VECTOR3D(1.f,0,0) },
		{VECTOR3D(-0.5f,0.5f,-0.5f),    VECTOR3D(1,1,0), VECTOR3D(1.2f,0.2f,0) },
		{ VECTOR3D(0.5f,0.5f,-0.5f),   VECTOR3D(1,1,0),  VECTOR3D(0.2f,1.2f,0) },
		{ VECTOR3D(0.5f,-0.5f,-0.5f),     VECTOR3D(1,0,0), VECTOR3D(1.2f,0,0) },

		//BACK FACE
		{ VECTOR3D(0.5f,-0.5f,0.5f),    VECTOR3D(0,1,0), VECTOR3D(0,1.2f,0) },
		{ VECTOR3D(0.5f,0.5f,0.5f),    VECTOR3D(0,1,1), VECTOR3D(0,0.2f,0.2f) },
		{ VECTOR3D(-0.5f,0.5f,0.5f),   VECTOR3D(0,1,1),  VECTOR3D(0,1.2f,1.2f) },
		{ VECTOR3D(-0.5f,-0.5f,0.5f),     VECTOR3D(0,1,0), VECTOR3D(0,1.2f,0) }

	};

	vertexCube plane_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{VECTOR3D(-0.5f,-0.5f,-0.5f),    VECTOR3D(0,0,0),  VECTOR3D(0,0,0) },
		{VECTOR3D(-0.5f,-0.5f,-0.5f),    VECTOR3D(0,0,0), VECTOR3D(0,0,0) },
		{ VECTOR3D(0.5f,0.5f,-0.5f),   VECTOR3D(0,0,0),  VECTOR3D(0,0,0) },
		{ VECTOR3D(0.5f,0.5f,-0.5f),     VECTOR3D(0,0,0), VECTOR3D(0,0,0) },

		//BACK FACE
		{ VECTOR3D(0.5f,-0.5f,0.5f),    VECTOR3D(0,0,0), VECTOR3D(0,0,0) },
		{ VECTOR3D(0.5f,-0.5f,0.5f),    VECTOR3D(0,0,0), VECTOR3D(0,0,0) },
		{ VECTOR3D(-0.5f,0.5f,0.5f),   VECTOR3D(0,0,0),  VECTOR3D(0,0,0) },
		{ VECTOR3D(-0.5f,0.5f,0.5f),     VECTOR3D(0,0,0), VECTOR3D(0,0,0) }

	};

	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	
		UINT size_list = ARRAYSIZE(cube_vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(cube_vertex_list, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
	
	



	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GRAPHICS_ENGINE::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib->load(index_list, size_index_list);

}

void Cube::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GRAPHICS_ENGINE::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Cube::drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps)
{
	
	PRIMITIVE::drawShape(m_vs, m_ps);
	
	updateTransforms();

	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	

	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	
	//SET THE INDECES OF THE TRIANGLE TO DRAW
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	
	// FINALLY DRAW THE TRIANGLE
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	
}

void Cube::releaseBuffers()
{

}

void Cube::updateTransforms()
{
	std::cout << "Cube Test 1" << std::endl;
	constant cc;
	cc.m_angle = ::GetTickCount();

	m_delta_pos += ENGINETIME::getDeltaTime() / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	if (name == "CUBE1") {
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(1.5f, 0.9f, 0.0f));
	}
	if (name == "CUBE2")
	{
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(0.0f, 0.9f, 0.0f));
	}
	if (name == "CUBE3")
	{
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(-1.5f, 2.0f, 0));
	}
	if (name == "CUBE4")
	{
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(-1.5f, 3.0f, -2.0f));
	}


	MATRIX4X4 temp;

	m_delta_scale += ENGINETIME::getDeltaTime() / 0.55f;


	cc.m_world.setScale(VECTOR3D(1, 1, 1));

	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
	cc.m_world *= temp;

	std::cout << "Cube Test 2" << std::endl;
	cc.m_view.setIdentity();
	std::cout << "Cube Test 3" << std::endl;

	//PROJ MATRIX
	//int width = ((AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left) / 300.0f);
	
	//int height = ((AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top) / 300.0f);
	std::cout << "Cube Test 4" << std::endl;
	//cc.m_proj.setOrthoLH(1.57f, ((float)width / (float)height), 0.1f, 1000.0f);
	cc.m_proj.setOrthoLH(
		10,
		10,
		-4.0f,
		4.0f
		);

	

	m_cb->update(GRAPHICS_ENGINE::get()->getImmediateDeviceContext(), &cc);
	std::cout << "Cube Test 5" << std::endl;
}

void Cube::setInitTransforms(VECTOR3D pos, VECTOR3D rot)
{
	initPos = pos;
	initRot = rot;
}
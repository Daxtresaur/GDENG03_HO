#include "CUBE.h"

#include <random>

#include "AppWindow.h"
#include "RENDERER.h"
#include "DEVICECONTEXT.h"
#include "CONSTANTBUFFER.h"
#include "ENGINETIME.h"
#include "INDEXBUFFER.h"
#include "VERTEXBUFFER.h"



CUBE::CUBE()
{
}

CUBE::~CUBE()
{
}

void CUBE::initialize(std::string name)
{
	PRIMITIVE::initialize(name);

	rotation = getLocalRotation();
	translation = getLocalPosition();
	scaling = getLocalScale();
	i_scale = false;
	i_trans = false;
}

void CUBE::destroy()
{
	PRIMITIVE::destroy();
}

void CUBE::initBuffers(void* shader_byte_code, size_t size_shader, int num = 0)
{
	this->num = num;
	vertexCube vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{VECTOR3D(-0.25f,-0.25f,-0.25f),    VECTOR3D(1,0,1),  VECTOR3D(0.2f,0,1) },
		{VECTOR3D(-0.25f,0.25f,-0.25f),    VECTOR3D(1,1,0), VECTOR3D(0,0.2f,0) },
		{ VECTOR3D(0.25f,0.25f,-0.25f),   VECTOR3D(1,1,0),  VECTOR3D(0.2f,1,0) },
		{ VECTOR3D(0.25f,-0.25f,-0.25f),     VECTOR3D(0,0,1), VECTOR3D(0.2f,0,0) },

		//BACK FACE
		{ VECTOR3D(0.25f,-0.25f,0.25f),    VECTOR3D(1,0,0), VECTOR3D(0,0.2f,0) },
		{ VECTOR3D(0.25f,0.25f,0.25f),    VECTOR3D(0,1,1), VECTOR3D(0,0.2f,0.2f) },
		{ VECTOR3D(-0.25f,0.25f,0.25f),   VECTOR3D(0,0,1),  VECTOR3D(0,0.2f,0.2f) },
		{ VECTOR3D(-0.25f,-0.25f,0.25f),     VECTOR3D(0,1,0), VECTOR3D(1,0,0) }

	};

	vertexCube vertex_list_white_cube[] =
	{
		//X - Y - Z
		//FRONT FACE
		{VECTOR3D(-1.0f,-1.0f,-1.0f),    VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{VECTOR3D(-1.0f,1.0f,-1.0f),    VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{ VECTOR3D(1.0f,1.0f,-1.0f),   VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{ VECTOR3D(1.0f,-1.0f,-1.0f),     VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },

		//BACK FACE
		{ VECTOR3D(1.0f,-1.0f,1.0f),    VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{ VECTOR3D(1.0f,1.0f,1.0f),    VECTOR3D(1,1,1),  VECTOR3D(1,1,1)},
		{ VECTOR3D(-1.0f,1.0f,1.0f),   VECTOR3D(1,1,1),  VECTOR3D(1,1,1)},
		{ VECTOR3D(-1.0f,-1.0f,1.0f),     VECTOR3D(1,1,1),  VECTOR3D(1,1,1)}

	};

	vertexCube plane_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{VECTOR3D(-1.0f,0.0f,-1.0f),    VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{VECTOR3D(-1.0f,0.0f,-1.0f),    VECTOR3D(1,1,1), VECTOR3D(1,1,1) },
		{ VECTOR3D(1.0f,.0f,-1.0f),   VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{ VECTOR3D(1.0f,0.0f,-1.0f),     VECTOR3D(1,1,1), VECTOR3D(1,1,1) },

		//BACK FACE
		{ VECTOR3D(1.0f,0.0f,1.0f),    VECTOR3D(1,1,1), VECTOR3D(1,1,1) },
		{ VECTOR3D(1.0f,0.0f,1.0f),    VECTOR3D(1,1,1), VECTOR3D(1,1,1) },
		{ VECTOR3D(-1.0f,0.0f,1.0f),   VECTOR3D(1,1,1),  VECTOR3D(1,1,1) },
		{ VECTOR3D(-1.0f,0.0f,1.0f),     VECTOR3D(1,1,1), VECTOR3D(1,1,1) }

	};

	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	if (this->num == 0) {
		UINT size_list = ARRAYSIZE(vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(vertex_list_white_cube, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
	}
	else {
		UINT size_list = ARRAYSIZE(plane_vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(plane_vertex_list, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
	}

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

void CUBE::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GRAPHICS_ENGINE::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void CUBE::drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps)
{
	PRIMITIVE::drawShape(m_vs, m_ps);
	updatePosition();


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

void CUBE::releaseBuffers()
{

}

void CUBE::updatePosition()
{
	float speed = 1.5f / 5;

	//WORLD MATRIX
	cc.m_world.setIdentity();
	MATRIX4X4 allMatrix; allMatrix.setIdentity();
	

	//no6
	if (name == "plane") {
		setScale(VECTOR3D(4, 4, 4));
	}
	if (name == "cube0")
	{
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(0.0f, 0.9f, 0.0f));
	}
	if (name == "cube1")
	{
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(-1.5f, 2.0f, 0));
	}
	if (name == "cube2")
	{
		setScale(VECTOR3D(0.5, 0.5, 0.5));
		setPosition(VECTOR3D(-1.5f, 3.0f, -2.0f));
	}


	MATRIX4X4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	MATRIX4X4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());


	

	MATRIX4X4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(getLocalRotation().m_z);
	allMatrix *= w_zMatrix;

	MATRIX4X4 w_xMatrix; w_xMatrix.setIdentity();
	w_xMatrix.setRotationX(rotation.m_x);
	allMatrix *= w_xMatrix;

	MATRIX4X4 w_yMatrix; w_yMatrix.setIdentity();
	w_yMatrix.setRotationY(rotation.m_y);
	allMatrix *= w_yMatrix;

	//scaleMatrix *= rotMatrix;
	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	//VIEW MATRIX
	cc.m_view.setIdentity();
	//cc.m_view = SceneCameraHandler::get()->getSceneCameraViewMatrix();

	//PROJ MATRIX
	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	//cc.m_proj.setOrthoLH(1.57f, ((float)width / (float)height), 0.1f, 1000.0f);
	cc.m_proj.setPerspectiveFovLH(1.57, ((float)width / (float)height), 0.1f, 1000.0f);

	//std::cout << getLocalPosition().m_x << ", " << getLocalPosition().m_y << ", " << getLocalPosition().m_z << std::endl;

	m_cb->update(GRAPHICS_ENGINE::get()->getImmediateDeviceContext(), &cc);

}
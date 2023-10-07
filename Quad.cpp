#include "Quad.h"

#include "AppWindow.h"
#include "ENGINETIME.h"
<<<<<<< HEAD
#include "RENDERER.h"
#include "DEVICECONTEXT.h"
#include "CONSTANTBUFFER.h"
#include "VERTEXBUFFER.h"

=======
#include <vector>
>>>>>>> parent of ffd8982 (Stop Point 1 - Progress 4)

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

void Quad::initBuffers(void* shader_byte_code, size_t size_shader)
{
	vertexAnim list_anim[] =
	{
		//X - Y - Z
		{VECTOR3D(-0.1f,-0.3f,0.0f),    VECTOR3D(-0.3f,-0.3f,0.0f),   VECTOR3D(1,1,0),  VECTOR3D(0,1,0)}, // POS1
		{VECTOR3D(-0.1f,0.95f,0.0f),     VECTOR3D(-0.3f,0.5f,0.0f),   VECTOR3D(1,1,0),  VECTOR3D(0,1,1)},// POS2
		{ VECTOR3D(0.1f,-0.95f,0.0f),    VECTOR3D(0.3f,-0.5f,0.0f),   VECTOR3D(0,1,1),  VECTOR3D(1,0,0)},// POS2
		{ VECTOR3D(0.1f,0.5f,0.0f),      VECTOR3D(0.3f,0.5f,0.0f),    VECTOR3D(1,1,1),  VECTOR3D(0,0,1)}

	};

	//SLIDE 13 CHALLENGE
	vertexAnim list_anim2[] =
	{
		//X - Y - Z
		{VECTOR3D(-0.78f,-0.8f,0.0f),    VECTOR3D(-0.32f,-0.11f,0.0f),   VECTOR3D(0,0,0),  VECTOR3D(0,1,0) }, // POS1
		{VECTOR3D(-0.9f,0.08f,0.0f),     VECTOR3D(-0.11f,0.78f,0.0f),    VECTOR3D(1,1,0),  VECTOR3D(0,1,1) }, // POS2
		{ VECTOR3D(0.1f,-0.2f,0.0f),     VECTOR3D(0.75f,-0.73f,0.0f),   VECTOR3D(0,0,1),  VECTOR3D(1,0,0) },// POS2
		{ VECTOR3D(-0.05f,0.15f,0.0f),      VECTOR3D(0.88f,0.77f,0.0f),    VECTOR3D(1,1,1),  VECTOR3D(0,0,1) }

	};

	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	m_vb->load(list_anim, sizeof(vertex), 4, shader_byte_code, size_shader);
}

void Quad::initAnimBuffers(void* shader_byte_code, size_t size_shader)
{
	vertexAnim list_anim[] =
	{
		//X - Y - Z
		{VECTOR3D(-0.1f,-0.3f,0.0f),   VECTOR3D(1,1,0),  VECTOR3D(0,1,0)}, // POS1
		{VECTOR3D(-0.1f,0.95f,0.0f),   VECTOR3D(1,1,0),  VECTOR3D(0,1,1)},// POS2
		{VECTOR3D(0.1f,-0.95f,0.0f),   VECTOR3D(0,1,1),  VECTOR3D(1,0,0)},// POS2
		{VECTOR3D(0.1f,0.5f,0.0f),    VECTOR3D(1,1,1),  VECTOR3D(0,0,1)}

	};

	//SLIDE 13 CHALLENGE
	vertexAnim list_anim2[] =
	{
		//X - Y - Z
		{VECTOR3D(-0.78f,-0.8f,0.0f),    VECTOR3D(-0.32f,-0.11f,0.0f),   VECTOR3D(0,0,0),  VECTOR3D(0,1,0) }, // POS1
		{VECTOR3D(-0.9f,0.08f,0.0f),     VECTOR3D(-0.11f,0.78f,0.0f),    VECTOR3D(1,1,0),  VECTOR3D(0,1,1) }, // POS2
		{ VECTOR3D(0.1f,-0.2f,0.0f),     VECTOR3D(0.75f,-0.73f,0.0f),   VECTOR3D(0,0,1),  VECTOR3D(1,0,0) },// POS2
		{ VECTOR3D(-0.05f,0.15f,0.0f),      VECTOR3D(0.88f,0.77f,0.0f),    VECTOR3D(1,1,1),  VECTOR3D(0,0,1) }

	};

	m_vb = GRAPHICS_ENGINE::get()->createVertexBuffer();
	m_vb->load(list_anim, sizeof(vertexAnim), 4, shader_byte_code, size_shader);
}

void Quad::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GRAPHICS_ENGINE::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Quad::drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps)
{
<<<<<<< HEAD
	
	updatePosition();
=======
	ENGINETIME::initialize();

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
>>>>>>> parent of ffd8982 (Stop Point 1 - Progress 4)


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

void Quad::updatePosition()
{
	//WORLD MATRIX
	cc.m_world.setIdentity();
	MATRIX4X4 allMatrix; allMatrix.setIdentity();

	//Vector3D moveX = Vector3D(AppWindow::getInstance()->move_cube, 0, 0);
	//this->setPosition(moveX);

	MATRIX4X4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	MATRIX4X4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	VECTOR3D rotation = getLocalRotation();

	MATRIX4X4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(rotation.m_z);
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

	//PROJ MATRIX
	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	//cc.m_proj.setOrthoLH(1.57f, ((float)width / (float)height), 0.1f, 1000.0f);
	cc.m_proj.setPerspectiveFovLH(1.57, ((float)width / (float)height), 0.1f, 1000.0f);

	m_cb->update(GRAPHICS_ENGINE::get()->getImmediateDeviceContext(), &cc);


}
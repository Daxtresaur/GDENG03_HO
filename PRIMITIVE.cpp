#include "PRIMITIVE.h"

void PRIMITIVE::initialize(std::string name)
{
	this->name = name;
	this->localRotation = VECTOR3D::zeros();
	this->localPosition = VECTOR3D::zeros();
	this->localScale = VECTOR3D::ones();
	this->localMatrix.setIdentity();
	this->localMatrix.setTranslation(VECTOR3D(0, 0, -2));
}

void PRIMITIVE::destroy()
{

}

void PRIMITIVE::drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps)
{

}

void PRIMITIVE::setPosition(float x, float y, float z)
{
	this->localPosition = VECTOR3D(x, y, z);
}

void PRIMITIVE::setPosition(VECTOR3D pos)
{
	this->localPosition = pos;
}

VECTOR3D PRIMITIVE::getLocalPosition()
{
	return this->localPosition;
}

void PRIMITIVE::setScale(float x, float y, float z)
{
	this->localScale = VECTOR3D(x, y, z);
}

void PRIMITIVE::setScale(VECTOR3D scale)
{
	this->localScale = scale;
}

VECTOR3D PRIMITIVE::getLocalScale()
{
	return this->localScale;
}

void PRIMITIVE::setRotation(float x, float y, float z)
{
	this->localRotation = VECTOR3D(x, y, z);
}

void PRIMITIVE::setRotation(VECTOR3D rot)
{
	this->localRotation = rot;
}

VECTOR3D PRIMITIVE::getLocalRotation()
{
	return this->localRotation;
}
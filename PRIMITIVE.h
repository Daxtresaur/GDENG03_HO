#pragma once
#include <string>
#include "MATRIX4X4.h"
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"
#include "VECTOR3D.h"

struct vertex
{
	VECTOR3D position;
	VECTOR3D color;
};

struct vertexAnim
{
	VECTOR3D position;
	VECTOR3D position1;
	VECTOR3D color;
	VECTOR3D color1;
};

struct vertexCube
{
	VECTOR3D position;
	VECTOR3D color;
	VECTOR3D color1;
};

__declspec(align(16)) struct constant
{
	MATRIX4X4 m_world;
	MATRIX4X4 m_view;
	MATRIX4X4 m_proj;
	float m_angle;
};

class PRIMITIVE
{
public:

	virtual void initialize(std::string name);
	virtual void destroy();
	virtual void drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps);

	void setPosition(float x, float y, float z);
	void setPosition(VECTOR3D pos);
	VECTOR3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(VECTOR3D scale);
	VECTOR3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(VECTOR3D rot);
	VECTOR3D getLocalRotation();



protected:
	std::string name;
	VECTOR3D localPosition;
	VECTOR3D localRotation;
	VECTOR3D localScale;
	MATRIX4X4 localMatrix;

};


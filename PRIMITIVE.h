#pragma once
#include <string>

#include "MATRIX4X4.h"
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

	virtual void initialize();
	virtual void destroy();
	virtual void drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps);

	//virtual changingvertex* acq_VerX_List(int* vertex_count)=0;

protected:
	std::string name;
	//changingvertex* VerX_List = nullptr;

};


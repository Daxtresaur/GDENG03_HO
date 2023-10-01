#pragma once
#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

struct changingvertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


__declspec(align(16))

struct constant
{
	float m_angle;
};

class PRIMITIVE
{
public:
	PRIMITIVE(changingvertex origin);

	//virtual void setPosition(vertex newPos) = 0;
	//virtual void getVertexSize() = 0;

	virtual changingvertex* acq_VerX_List(int* vertex_count)=0;
	virtual void drawShape(UINT* vertex_index)=0;


	~PRIMITIVE();

protected:
	changingvertex* VerX_List = nullptr;

};


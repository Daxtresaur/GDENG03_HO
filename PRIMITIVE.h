#pragma once
#include <d3d11.h>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

class PRIMITIVE
{
public:
	PRIMITIVE(vertex origin);

	//virtual void setPosition(vertex newPos) = 0;
	//virtual void getVertexSize() = 0;

	virtual vertex* acq_VerX_List(int* vertex_count)=0;
	virtual void drawShape(UINT* vertex_index)=0;


	~PRIMITIVE();

protected:
	vertex* VerX_List = nullptr;

};


#include "Triangle.h"
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include <vector>

Triangle::Triangle(vertex origin, vertex pointA, vertex pointB): PRIMITIVE(origin)
{
	this->VertexList = new vertex[3];

	this->VertexList[0] = origin;
	this->VertexList[1] = pointA;
	this->VertexList[2] = pointB;
}

vertex* Triangle::getVertexList(int* vertex_count)
{
	*vertex_count = 3;
	return this->VertexList;
}

void Triangle::drawShape(UINT* vertex_index)
{
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleList(3, *vertex_index);
	*vertex_index += 3;
}

Triangle::~Triangle()
{
}

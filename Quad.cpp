#include "Quad.h"
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include <vector>

Quad::Quad(vertex origin, vertex pointA, vertex pointB, vertex pointC) : PRIMITIVE(origin)
{
	this->VertexList = new vertex[4];

	this->VertexList[0] = origin;
	this->VertexList[1] = pointA;
	this->VertexList[2] = pointB;
	this->VertexList[3] = pointC;
}

vertex* Quad::getVertexList(int* vertex_count)
{
	*vertex_count = 4;
	return this->VertexList;
}

void Quad::drawShape(UINT* vertex_index)
{
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleStrip(4, *vertex_index);
	*vertex_index += 4;
}

Quad::~Quad()
{
}

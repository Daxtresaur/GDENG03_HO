#include "Triangle.h"



Triangle::Triangle()
{
}

vertex* Triangle::getVertexList()
{
	vertex vert;

	return &vert;
}

void Triangle::setVertexList(vertex* list_vertices)
{
	list = list_vertices;
}


Triangle::~Triangle()
{
}

#include "Triangle.h"
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include <vector>

Triangle::Triangle(vertex origin, vertex pointA, vertex pointB): PRIMITIVE(origin)
{
	this->VerX_List = new vertex[3];

	this->VerX_List[0] = origin;
	this->VerX_List[1] = pointA;
	this->VerX_List[2] = pointB;
}

vertex* Triangle::acq_VerX_List(int* vertex_count)
{
	*vertex_count = 3;
	return this->VerX_List;
}

void Triangle::drawShape(UINT* vertex_index)
{
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleList(3, *vertex_index);
	*vertex_index += 3;
}

Triangle::~Triangle()
{
}

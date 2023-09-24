#include "Quad.h"
#include "GRAPHICS_ENGINE.h"
#include "DEVICECONTEXT.h"
#include <vector>

Quad::Quad(changingvertex origin, changingvertex pointA, changingvertex pointB, changingvertex pointC) : PRIMITIVE(origin)
{
	this->VerX_List = new changingvertex[4];

	this->VerX_List[0] = origin;
	this->VerX_List[1] = pointA;
	this->VerX_List[2] = pointB;
	this->VerX_List[3] = pointC;
}

changingvertex* Quad::acq_VerX_List(int* vertex_count)
{
	*vertex_count = 4;
	return this->VerX_List;
}

void Quad::drawShape(UINT* vertex_index)
{
	GRAPHICS_ENGINE::get()->getImmediateDeviceContext()->drawTriangleStrip(4, *vertex_index);
	*vertex_index += 4;
}

Quad::~Quad()
{
}

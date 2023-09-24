#pragma once
#include "PRIMITIVE.h"
#include <vector>

class Triangle : public PRIMITIVE
{
public:

	Triangle(changingvertex origin, changingvertex pointA, changingvertex pointB);

	changingvertex* acq_VerX_List(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;

	~Triangle();
	

};


#pragma once
#include "PRIMITIVE.h"
#include <vector>

class Triangle : public PRIMITIVE
{
public:

	Triangle(vertex origin,vertex pointA, vertex pointB);

	vertex* acq_VerX_List(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;

	~Triangle();
	

};


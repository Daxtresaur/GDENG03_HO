#pragma once
#include "PRIMITIVE.h"
#include <vector>

class Triangle : public PRIMITIVE
{
public:

	Triangle(vertex origin,vertex pointA, vertex pointB);

	vertex* getVertexList(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;

	~Triangle();
	

};


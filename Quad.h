#pragma once
#include "PRIMITIVE.h"

class Quad : public PRIMITIVE
{
public:
	Quad(vertex origin, vertex pointA, vertex pointB, vertex pointC);

	vertex* getVertexList(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;

	~Quad();
};


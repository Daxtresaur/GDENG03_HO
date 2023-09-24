#pragma once
#include "PRIMITIVE.h"

class Quad : public PRIMITIVE
{
public:
	Quad(changingvertex origin, changingvertex pointA, changingvertex pointB, changingvertex pointC);

	changingvertex* acq_VerX_List(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;

	~Quad();
};


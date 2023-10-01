#pragma once
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

class PRIMITIVE
{
public:

	virtual void initialize();
	virtual void destroy();
	virtual void drawShape(VERTEXSHADER* m_vs, PIXELSHADER* m_ps);

	//virtual changingvertex* acq_VerX_List(int* vertex_count)=0;

	//changingvertex* VerX_List = nullptr;

};


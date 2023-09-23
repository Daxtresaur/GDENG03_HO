#include "PRIMITIVE.h"

PRIMITIVE::PRIMITIVE(vertex origin)
{
}

PRIMITIVE::~PRIMITIVE()
{
	delete[] VerX_List;
}

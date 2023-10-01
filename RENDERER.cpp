#include "RENDERER.h"

RENDERER* RENDERER::sharedInstance = nullptr;

RENDERER* RENDERER::getInstance()
{
	return sharedInstance;
}

void RENDERER::initialize()
{
	sharedInstance = new RENDERER();
}

void RENDERER::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->releaseQuads();
	}

}

void RENDERER::initializeQuads(struct vertex list[], void* shader_byte_code, size_t size_shader)
{
	Quad* tempQuad = new Quad();
	tempQuad->initialize();
	tempQuad->initBuffers(list, shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void RENDERER::initializeQuadsAnim(struct vertexAnim list[], void* shader_byte_code, size_t size_shader)
{
	Quad* tempQuad = new Quad();
	tempQuad->initialize();
	tempQuad->initAnimBuffers(list, shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void RENDERER::initializeQuadConst()
{
	for (auto const& i : sharedInstance->getQuadList()) {
		i->initConstBuffers();
	}
}

void RENDERER::insertQuads(Quad* quad)
{
	vertexBufferList.push_front(quad);
}

void RENDERER::releaseQuads()
{

}

std::list<Quad*>  RENDERER::getQuadList()
{

	return vertexBufferList;
}

RENDERER::RENDERER()
{

}

RENDERER::~ RENDERER()
{

}
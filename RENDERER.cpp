#include "RENDERER.h"
#include "AppWindow.h"
#include "SWAPCHAIN.h"


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

void RENDERER::initializeQuads(std::string name, void* shader_byte_code, size_t size_shader)
{
	Quad* tempQuad = new Quad();
	tempQuad->initialize(name);
	tempQuad->initBuffers(shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void RENDERER::initializeQuadsAnim(std::string name, void* shader_byte_code, size_t size_shader)
{
	Quad* tempQuad = new Quad();
	tempQuad->initialize(name);
	tempQuad->initAnimBuffers(shader_byte_code, size_shader);
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
	quadList.push_front(quad);
}

void RENDERER::releaseQuads()
{

}

std::list<Quad*> RENDERER::getQuadList()
{
	return quadList;
}

void RENDERER::initializeCube(std::string name, void* shader_byte_code, size_t size_shader, int num = 0)
{
	CUBE* cube = new CUBE();
	cube->initialize(name);
	cube->initBuffers(shader_byte_code, size_shader, num);
	insertCube(cube);
}

void RENDERER::initializeCubeConst()
{
	int num = 0;

	for (auto const& i : sharedInstance->getCubeList()) {
		i->initConstBuffers();

		num++;
	}
}

void RENDERER::insertCube(CUBE* cube)
{
	cubeList.push_front(cube);
}

void RENDERER::releaseCubes()
{
}

std::list<CUBE*> RENDERER::getCubeList()
{
	return cubeList;
}

RENDERER::RENDERER()
{

}

RENDERER::~RENDERER()
{

}
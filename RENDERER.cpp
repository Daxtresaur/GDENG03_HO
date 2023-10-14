#include "RENDERER.h"
#include <cstdlib>
#include <random>



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

void RENDERER::initializeQuads(std::string name, struct vertexAnim list[], void* shader_byte_code, size_t size_shader)
{
	Quad* tempQuad = new Quad();
	tempQuad->initialize(name);
	tempQuad->initBuffers(list, shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void RENDERER::initializeQuadsAnim(std::string name, struct vertexAnim list[], void* shader_byte_code, size_t size_shader)
{
	Quad* tempQuad = new Quad();
	tempQuad->initialize(name);
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

void RENDERER::initializeCube(std::string name, void* shader_byte_code, size_t size_shader, int num = 0)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_real_distribution<> distr(-0.75, 0.75); // define the range

	Cube* cube = new Cube();
	cube->initialize(name);
	cube->initBuffers(shader_byte_code, size_shader, num);

	float x = distr(gen);
	float y = distr(gen);
	VECTOR3D rot = VECTOR3D(distr(gen), distr(gen), distr(gen));
	if (num == 0)
		cube->setInitTransforms(VECTOR3D(0, 0, 0.0f), rot);
	else
		cube->setInitTransforms(VECTOR3D(0, 0, 0.0f), VECTOR3D(0, 0, 0));

	insertCube(cube);
}

void RENDERER::initializeCubeConst()
{
	
	for (auto const& i : sharedInstance->getCubeList()) {
		i->initConstBuffers();
	}
}

void RENDERER::insertCube(Cube* cube)
{
	cubeList.push_front(cube);
}

void RENDERER::releaseCubes()
{
}

std::list<Cube*> RENDERER::getCubeList()
{
	std::cout << cubeList.size() << std::endl;
	return cubeList;
}



RENDERER::RENDERER()
{

}

RENDERER::~ RENDERER()
{

}
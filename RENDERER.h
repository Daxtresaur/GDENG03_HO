#pragma once
#include "Quad.h"
#include "Cube.h"
#include "AppWindow.h"
#include "GRAPHICS_ENGINE.h"
#include "SWAPCHAIN.h"
#include "DEVICECONTEXT.h"
#include "VERTEXBUFFER.h"
#include "CONSTANTBUFFER.h"
#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"
#include <list>

class RENDERER
{
public:
	RENDERER();
	~RENDERER();

	static RENDERER* getInstance();
	static void initialize();
	static void destroy();

	void initializeQuads(std::string name, vertexAnim list[], void* shader_byte_code, size_t size_shader);
	void initializeQuadsAnim(std::string name, vertexAnim list[], void* shader_byte_code, size_t size_shader);
	void initializeQuadConst();
	void insertQuads(class Quad* quad);
	void releaseQuads();
	std::list<class Quad*> getQuadList();

	void initializeCube(std::string name, void* shader_byte_code, size_t size_shader, int num);
	void initializeCubeConst();
	void insertCube(class Cube* cube);
	void releaseCubes();
	std::list<class Cube*> getCubeList();

private:
	static RENDERER* sharedInstance;
	std::list<class Quad*> vertexBufferList;
	std::list<class Cube*> cubeList;

	RENDERER(RENDERER const&) {};
	RENDERER& operator=(RENDERER const&) {};
};


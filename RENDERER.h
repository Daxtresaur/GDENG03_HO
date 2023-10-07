#pragma once
#include <list>

#include "Quad.h"
#include "CUBE.h"

class RENDERER
{
public:
	RENDERER();
	~RENDERER();

	static RENDERER* getInstance();
	static void initialize();
	static void destroy();

	void initializeQuads(std::string name, void* shader_byte_code, size_t size_shader);
	void initializeQuadsAnim(std::string name, void* shader_byte_code, size_t size_shader);
	void initializeQuadConst();
	void insertQuads(class Quad* quad);
	void releaseQuads();
	std::list<class Quad*> getQuadList();

	void initializeCube(std::string name, void* shader_byte_code, size_t size_shader, int num);
	void initializeCubeConst();
	void insertCube(class CUBE* cube);
	void releaseCubes();
	std::list<class CUBE*> getCubeList();


private:
	static RENDERER* sharedInstance;
	std::list<class Quad*> quadList;
	std::list<class CUBE*> cubeList;

	RENDERER(RENDERER const&) {};
	RENDERER& operator=(RENDERER* const&) {};


};
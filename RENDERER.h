#pragma once
#include "Quad.h"
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

	void initializeQuads(vertex list[], void* shader_byte_code, size_t size_shader);
	void initializeQuadsAnim(vertexAnim list[], void* shader_byte_code, size_t size_shader);
	void initializeQuadConst();
	void insertQuads(class Quad* quad);
	void releaseQuads();
	std::list<class Quad*> getQuadList();

private:
	static RENDERER* sharedInstance;
	std::list<class Quad*> vertexBufferList;

	RENDERER(RENDERER const&) {};
	RENDERER& operator=(RENDERER const&) {};
};


#pragma once
#include "WINDOW.h"
#include "GRAPHICS_ENGINE.h"

#include "SWAPCHAIN.h"
#include "DEVICECONTEXT.h"

#include "VERTEXBUFFER.h"

#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

#include "PRIMITIVE.h"
#include "Triangle.h"
#include "Quad.h"

#include <vector>

class AppWindow: public WINDOW
{
public:
	AppWindow();
	~AppWindow();

	//Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

private:
	SWAPCHAIN* m_swap_chain;
	VERTEXBUFFER* m_vb;
	VERTEXSHADER* m_vs;
	PIXELSHADER* m_ps;

	std::vector<PRIMITIVE*> primitive_List;

	
};


#pragma once
#include "WINDOW.h"
#include "GRAPHICS_ENGINE.h"

#include "SWAPCHAIN.h"
#include "DEVICECONTEXT.h"

#include "VERTEXBUFFER.h"
#include "CONSTANTBUFFER.h"
#include "INDEXBUFFER.h"

#include "VERTEXSHADER.h"
#include "PIXELSHADER.h"

#include "PRIMITIVE.h"
#include "Quad.h"
#include "Cube.h"

#include <vector>

class AppWindow: public WINDOW
{
public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();

	AppWindow();
	~AppWindow();

	//Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;


private:
	static AppWindow* sharedInstance;

	SWAPCHAIN* m_swap_chain;
	
	VERTEXBUFFER* m_vb;
	CONSTANTBUFFER* m_cb;
	INDEXBUFFER* m_ib;

	VERTEXSHADER* m_vs;
	PIXELSHADER* m_ps;
	
	

	std::vector<PRIMITIVE*> primitive_List;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

	float mElapsedTime = 0.f;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
};


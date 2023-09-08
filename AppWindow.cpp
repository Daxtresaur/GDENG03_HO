#include "AppWindow.h"


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//WINDOW::onCreate();
	GRAPHICS_ENGINE::get()->init();
}

void AppWindow::onUpdate()
{
	//WINDOW::onUpdate();
}

void AppWindow::onDestroy()
{
	//WINDOW::onDestroy();
	GRAPHICS_ENGINE::get()->release();
}

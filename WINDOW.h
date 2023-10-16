#pragma once
#include <Windows.h>
#include "ENGINETIME.h"


class Window
{
public:
	Window();
	// Initializes the window
	bool init();
	bool broadcast();
	// Releases the window
	bool release();
	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate() =0;
	virtual void onUpdate() =0;
	virtual void onDestroy();

	virtual ~Window();

protected:
	HWND m_hwnd;
	bool m_is_running;
};



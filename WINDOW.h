#pragma once
#include <Windows.h>


class WINDOW
{
public:
	WINDOW();
	// Initializes the window
	bool init();
	bool broadcast();
	// Releases the window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate() =0;
	virtual void onUpdate() =0;
	virtual void onDestroy();

	virtual ~WINDOW();

protected:
	HWND m_hwnd;
	bool m_is_run;
};



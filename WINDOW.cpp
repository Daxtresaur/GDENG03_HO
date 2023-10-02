#include "WINDOW.h"

#include <cstdio>
#include <iostream>
#include <ostream>

WINDOW::WINDOW()
{
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_CREATE:
		{
		// Event fired when the window is created
		// collected here..
		WINDOW* window = (WINDOW*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		
		break;
		}
	case WM_DESTROY:
		{
		// Event fired when the window is destroyed
		WINDOW* window = (WINDOW*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
		}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}


bool WINDOW::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) // if Class Registration fails the function returns false
		return false;

	//Window Creation
	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"My Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	if (!m_hwnd)
		return false;

	//Shows the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	// Flag is set to indicate that the window is initialized and running
	m_is_run = true;

	ENGINETIME::initialize();

	return true;
}

bool WINDOW::broadcast()
{
	MSG msg;

	ENGINETIME::LogFrameStart();

	this->onUpdate();

	ENGINETIME::LogFrameEnd();

	while (::PeekMessage(&msg, NULL,0,0,PM_REMOVE)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);


	return true;
}

bool WINDOW::release()
{
	//Destroys the window
		if(!::DestroyWindow(m_hwnd))
			return false;

	return true;
}

bool WINDOW::isRun()
{
	return m_is_run;
}


RECT WINDOW::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void WINDOW::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void WINDOW::onCreate()
{
}

void WINDOW::onUpdate()
{
}


void WINDOW::onDestroy()
{
	m_is_run = false;
}

WINDOW::~WINDOW()
{
	
}

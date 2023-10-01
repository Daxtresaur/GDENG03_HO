#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class WINDOW;

class ENGINETIME
{
public:
	static void initialize();
	static double getDeltaTime();

private:
	ENGINETIME();
	~ENGINETIME();

	ENGINETIME(ENGINETIME const&) {}
	ENGINETIME& operator=(ENGINETIME const&) {}

	static ENGINETIME* sharedInstance;
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;
	static void LogFrameStart();
	static void LogFrameEnd();

	friend class WINDOW;
};


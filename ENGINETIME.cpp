#include "ENGINETIME.h"

ENGINETIME* ENGINETIME::sharedInstance = nullptr;

void ENGINETIME::initialize()
{
	sharedInstance = new ENGINETIME();
}

double ENGINETIME::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

ENGINETIME::ENGINETIME()
{
}

ENGINETIME::~ENGINETIME()
{
}

void ENGINETIME::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void ENGINETIME::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();

}
#include "ENGINETIME.h"

ENGINETIME* ENGINETIME::sharedInstance = nullptr;

void ENGINETIME::initialize()
{

	if (!sharedInstance)
	{
		sharedInstance = new ENGINETIME();
	}
	
}

double ENGINETIME::getDeltaTime()
{
	std::chrono::duration<double> deltaTime = sharedInstance->start - sharedInstance->end;
	return deltaTime.count();
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
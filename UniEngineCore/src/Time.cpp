#include "Time.h"
using namespace UniEngine;
void UniEngine::Time::AddWorldTime(double value)
{
	_WorldTime += value;
}

void UniEngine::Time::AddFixedDeltaTime(double value)
{
	_FixedDeltaTime += value;
}

float UniEngine::Time::TimeStep()
{
	return _TimeStep;
}

double UniEngine::Time::WorldTime()
{
	return _WorldTime;
}

float UniEngine::Time::FixedDeltaTime()
{
	return (float)_FixedDeltaTime;
}

float UniEngine::Time::DeltaTime()
{
	return (float)_DeltaTime;
}

float UniEngine::Time::LastFrameTime()
{
	return (float)_LastFrameTime;
}

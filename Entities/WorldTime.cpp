#include "pch.h"
#include "WorldTime.h"

void UniEngine::WorldTime::AddFixedDeltaTime(double value)
{
	_FixedDeltaTime += value;
}

float UniEngine::WorldTime::TimeStep()
{
	return _TimeStep;
}

double UniEngine::WorldTime::Time()
{
	return _WorldTime;
}

float UniEngine::WorldTime::FixedDeltaTime()
{
	return (float)_FixedDeltaTime;
}

float UniEngine::WorldTime::DeltaTime()
{
	return (float)_DeltaTime;
}

float UniEngine::WorldTime::LastFrameTime()
{
	return (float)_LastFrameTime;
}

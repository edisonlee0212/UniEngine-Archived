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

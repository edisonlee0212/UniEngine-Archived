#include "pch.h"
#include "WorldTime.h"

void UniEngine::Entities::WorldTime::AddFixedDeltaTime(double value)
{
	_FixedDeltaTime += value;
}

float UniEngine::Entities::WorldTime::TimeStep()
{
	return _TimeStep;
}

double UniEngine::Entities::WorldTime::Time()
{
	return _WorldTime;
}

float UniEngine::Entities::WorldTime::FixedDeltaTime()
{
	return (float)_FixedDeltaTime;
}

float UniEngine::Entities::WorldTime::DeltaTime()
{
	return (float)_DeltaTime;
}

float UniEngine::Entities::WorldTime::LastFrameTime()
{
	return (float)_LastFrameTime;
}

#include "pch.h"
#include "EngineTime.h"
using namespace UniEngine;
void UniEngine::EngineTime::AddWorldTime(double value)
{
	_WorldTime += value;
}

void UniEngine::EngineTime::AddFixedDeltaTime(double value)
{
	_FixedDeltaTime += value;
}

float UniEngine::EngineTime::TimeStep()
{
	return _TimeStep;
}

double UniEngine::EngineTime::WorldTime()
{
	return _WorldTime;
}

float UniEngine::EngineTime::FixedDeltaTime()
{
	return (float)_FixedDeltaTime;
}

float UniEngine::EngineTime::DeltaTime()
{
	return (float)_DeltaTime;
}

float UniEngine::EngineTime::LastFrameTime()
{
	return (float)_LastFrameTime;
}

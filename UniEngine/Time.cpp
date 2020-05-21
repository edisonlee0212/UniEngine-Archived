#include "Time.h"
using namespace UniEngine;
double Time::_WorldTime;
double Time::_DeltaTime;
double Time::_LastFrameTime;
double Time::_FixedDeltaTime;

void UniEngine::Time::AddWorldTime(double value)
{
	_WorldTime += value;
}

void UniEngine::Time::AddFixedDeltaTime(double value)
{
	_FixedDeltaTime += value;
}

void UniEngine::Time::SetWorldTime(double value)
{
	_WorldTime = value;
}

void UniEngine::Time::SetFixedDeltaTime(double value)
{
	_FixedDeltaTime = value;
}

void UniEngine::Time::SetDeltaTime(double value)
{
	_DeltaTime = value;
}

void UniEngine::Time::SetLastFrameTime(double value)
{
	_LastFrameTime = value;
}

double UniEngine::Time::WorldTime()
{
	return _WorldTime;
}

double UniEngine::Time::FixedDeltaTime()
{
	return _FixedDeltaTime;
}

double UniEngine::Time::DeltaTime()
{
	return _DeltaTime;
}


double UniEngine::Time::LastFrameTime()
{
	return _LastFrameTime;
}

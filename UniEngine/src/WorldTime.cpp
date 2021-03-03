#include "pch.h"
#include "WorldTime.h"

void UniEngine::WorldTime::AddFixedDeltaTime(double value)
{
	m_fixedDeltaTime += value;
}

float UniEngine::WorldTime::TimeStep()
{
	return m_timeStep;
}

float UniEngine::WorldTime::FixedDeltaTime()
{
	return (float)m_fixedDeltaTime;
}

float UniEngine::WorldTime::DeltaTime()
{
	return (float)m_deltaTime;
}

float UniEngine::WorldTime::LastFrameTime()
{
	return (float)m_lastFrameTime;
}

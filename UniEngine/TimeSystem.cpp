#include "TimeSystem.h"
#include "Time.h"
UniEngine::TimeSystem::TimeSystem()
{
	Time::SetWorldTime(0);
	Time::SetDeltaTime(0);
	Time::SetLastFrameTime(0);
	Time::SetFixedDeltaTime(0);
}
void UniEngine::TimeSystem::OnCreate()
{
	Enable();
}

void UniEngine::TimeSystem::OnDestroy()
{
	Disable();
}

void UniEngine::TimeSystem::Update()
{
	double currentFrame = glfwGetTime();
	Time::SetDeltaTime(currentFrame - Time::LastFrameTime());
	Time::AddWorldTime(Time::DeltaTime());
	Time::SetLastFrameTime(currentFrame);
	Time::AddFixedDeltaTime(Time::DeltaTime());
}

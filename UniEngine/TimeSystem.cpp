#include "pch.h"
#include "TimeSystem.h"
#include "EngineTime.h"
UniEngine::TimeSystem::TimeSystem()
{
	
}
void UniEngine::TimeSystem::OnCreate()
{
	_Time->_WorldTime = 0;
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = 0;
	_Time->_FixedDeltaTime = 0;
	Enable();
}

void UniEngine::TimeSystem::OnDestroy()
{
	Disable();
}

void UniEngine::TimeSystem::Update()
{
	double currentFrame = glfwGetTime();
	_Time->_DeltaTime = currentFrame - _Time->_LastFrameTime;
	_Time->AddWorldTime(_Time->_DeltaTime);
	_Time->_LastFrameTime = currentFrame;
	_Time->AddFixedDeltaTime(_Time->_DeltaTime);
	ImGui::Begin("Time Info");
	ImGui::SliderFloat("sec/step", &(_Time->_TimeStep), 0.05f, 1.0f);
	ImGui::End();
}

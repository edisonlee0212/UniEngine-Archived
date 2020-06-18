#include "pch.h"
#include "World.h"
using namespace UniEngine;
using namespace UniEngine::Entities;

void UniEngine::Entities::WorldTime::AddWorldTime(double value)
{
	_WorldTime += value;
}

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

size_t UniEngine::Entities::World::GetIndex() {
	return _Index;
}

UniEngine::Entities::World::World(size_t index) {
	_Index = index;
	_Time = new WorldTime();
	_Time->_TimeStep = 0.2f;
}

void UniEngine::Entities::World::Init()
{
	_Time->_WorldTime = 0;
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = 0;
	_Time->_FixedDeltaTime = 0;
	/*
	//Initialization System Group
	CreateSystem<TimeSystem>();

	//Simulation System Group
	CreateSystem<PhysicsSystem>();
	CreateSystem<TransformSystem>();

	//Presentation System Group
	CreateSystem<RenderSystem>();
	*/
}



UniEngine::Entities::World::~World() {
	for (auto i : _Systems) {
		i->OnDestroy();
		delete i;
	}
	delete _Time;
}
void UniEngine::Entities::World::Update() {
	double currentFrame = glfwGetTime();
	_Time->_DeltaTime = currentFrame - _Time->_LastFrameTime;
	_Time->AddWorldTime(_Time->_DeltaTime);
	_Time->_LastFrameTime = currentFrame;
	_Time->AddFixedDeltaTime(_Time->_DeltaTime);
	ImGui::Begin("Time Info");
	ImGui::SliderFloat("sec/step", &(_Time->_TimeStep), 0.05f, 1.0f);
	ImGui::End();
	if (_Time->_FixedDeltaTime >= _Time->_TimeStep) {
		_Time->_FixedDeltaTime = 0;
		for (auto i : _Systems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}

	for (auto i : _Systems) {
		if (i->Enabled()) i->Update();
	}
}

WorldTime* UniEngine::Entities::World::Time()
{
	return _Time;
}

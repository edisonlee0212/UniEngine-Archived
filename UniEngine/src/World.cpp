#include "pch.h"
#include "World.h"
#include "UniEngine.h"
using namespace UniEngine;


void World::RegisterFixedUpdateFunction(const std::function<void()>& func)
{
	_ExternalFixedUpdateFunctions.push_back(func);
}

Bound UniEngine::World::GetBound() const
{
	return _WorldBound;
}

void UniEngine::World::SetBound(Bound value)
{
	_WorldBound = value;
}

UniEngine::Bound::Bound()
{
	Min = glm::vec3(FLT_MIN);
	Max = glm::vec3(FLT_MAX);
}


void UniEngine::World::SetFrameStartTime(double time) const
{
	_Time->_FrameStartTime = time;
}

void UniEngine::World::SetTimeStep(float timeStep) const
{
	_Time->_TimeStep = timeStep;
}

size_t UniEngine::World::GetIndex() const
{
	return _Index;
}

UniEngine::World::World(size_t index) {
	_Index = index;
	_Time = new WorldTime();
}

void World::ResetTime() const
{
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = 0;
	_Time->_FixedDeltaTime = 0;
}


UniEngine::World::~World() {
	for (auto i : _PreparationSystems) {
		i->OnDestroy();
		delete i;
	}
	for (auto i : _SimulationSystems) {
		i->OnDestroy();
		delete i;
	}
	for (auto i : _PresentationSystems) {
		i->OnDestroy();
		delete i;
	}
	delete _Time;
}

void World::PreUpdate()
{
	_NeedFixedUpdate = false;
	if (_Time->_FixedDeltaTime >= _Time->_TimeStep) {
		_NeedFixedUpdate = true;
	}
	
	if (_NeedFixedUpdate) {
		for (const auto& i : _ExternalFixedUpdateFunctions) i();
		for (auto i : _PreparationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		for (auto i : _SimulationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		if (PhysicsSimulationManager::Enabled) PhysicsSimulationManager::Simulate(_Time->_FixedDeltaTime);
		for (auto i : _PresentationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
	
	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
	
	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
}

void UniEngine::World::Update() {
	
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->Update();
	}
	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->Update();
	}
	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->Update();
	}
}

void World::LateUpdate()
{
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}

	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}

	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}
	if (_NeedFixedUpdate)
	{
		_Time->_FixedDeltaTime = 0;
	}
}

WorldTime* UniEngine::World::Time() const
{
	return _Time;
}

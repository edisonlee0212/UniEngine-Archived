#include "pch.h"
#include "World.h"
#include "ManagerBase.h"
#include "PhysicsSimulationManager.h"
using namespace UniEngine;


ThreadPool* World::GetThreadPool()
{
	return _ThreadPool;
}

Bound UniEngine::World::GetBound()
{
	return _WorldBound;
}

void UniEngine::World::SetBound(Bound value)
{
	_WorldBound = value;
}

UniEngine::Bound::Bound()
{
	Center = glm::vec3(0.0f);
	Radius = 0;
}


void UniEngine::World::SetWorldTime(double time)
{
	_Time->_WorldTime = time;
}

void UniEngine::World::SetTimeStep(float timeStep)
{
	_Time->_TimeStep = timeStep;
}

size_t UniEngine::World::GetIndex() {
	return _Index;
}

UniEngine::World::World(size_t index, ThreadPool* threadPool) {
	_Index = index;
	_ThreadPool = threadPool;
	_Time = new WorldTime();
}

void World::ResetTime()
{
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = _Time->_WorldTime;
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
void UniEngine::World::Update() {
	_Time->_DeltaTime = _Time->_WorldTime - _Time->_LastFrameTime;
	_Time->_LastFrameTime = _Time->_WorldTime;
	_Time->_FixedDeltaTime += _Time->_DeltaTime;
	bool fixedUpdate = false;
	if (_Time->_FixedDeltaTime >= _Time->_TimeStep) {
		fixedUpdate = true;
	}
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->Update();
	}
	if (fixedUpdate) {
		for (auto i : _PreparationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->Update();
	}
	if (fixedUpdate) {
		for (auto i : _SimulationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		if(PhysicsSimulationManager::Enabled) PhysicsSimulationManager::Simulate(_Time->_FixedDeltaTime);
	}
	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->Update();
	}
	if (fixedUpdate) {
		for (auto i : _PresentationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	if(fixedUpdate)
	{
		_Time->_FixedDeltaTime = 0;
	}
}

WorldTime* UniEngine::World::Time()
{
	return _Time;
}

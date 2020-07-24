#include "pch.h"
#include "World.h"
#include "ManagerBase.h"
using namespace UniEngine;
using namespace UniEngine::Entities;


Bound UniEngine::Entities::World::GetBound()
{
	return _WorldBound;
}

void UniEngine::Entities::World::SetBound(Bound value)
{
	_WorldBound = value;
}

UniEngine::Bound::Bound()
{
	Radius = 0;
}


void UniEngine::Entities::World::SetWorldTime(double time)
{
	_Time->_WorldTime = time;
}

void UniEngine::Entities::World::SetTimeStep(float timeStep)
{
	_Time->_TimeStep = timeStep;
}

size_t UniEngine::Entities::World::GetIndex() {
	return _Index;
}

UniEngine::Entities::World::World(size_t index) {
	_Index = index;
	_Time = new WorldTime();
}

void UniEngine::Entities::World::Init()
{
	_Time->_WorldTime = 0;
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = 0;
	_Time->_FixedDeltaTime = 0;
	ManagerBase::_World = this;
}



UniEngine::Entities::World::~World() {
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
void UniEngine::Entities::World::Update() {
	_Time->_DeltaTime = _Time->_WorldTime - _Time->_LastFrameTime;
	_Time->_LastFrameTime = _Time->_WorldTime;
	_Time->AddFixedDeltaTime(_Time->_DeltaTime);
	
	if (_Time->_FixedDeltaTime >= _Time->_TimeStep) {
		_Time->_FixedDeltaTime = 0;
		for (auto i : _PreparationSystems) {
			if (i->Enabled()) i->FixedUpdate();

		}
		for (auto i : _SimulationSystems) {
			if (i->Enabled()) i->FixedUpdate();

		}
		for (auto i : _PresentationSystems) {
			if (i->Enabled()) i->FixedUpdate();

		}
	}
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

WorldTime* UniEngine::Entities::World::Time()
{
	return _Time;
}

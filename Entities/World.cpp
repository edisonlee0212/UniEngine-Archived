#include "pch.h"
#include "World.h"
#include "ManagerBase.h"
using namespace UniEngine;


Bound World::GetBound()
{
	return _WorldBound;
}

void World::SetBound(Bound value)
{
	_WorldBound = value;
}

Bound::Bound()
{
	Radius = 0;
}


void World::SetWorldTime(double time)
{
	_Time->_WorldTime = time;
}

void World::SetTimeStep(float timeStep)
{
	_Time->_TimeStep = timeStep;
}

size_t World::GetIndex()
{
	return _Index;
}

World::World(size_t index, ThreadPool* threadPool)
{
	_Index = index;
	_ThreadPool = threadPool;
	_Time = new WorldTime();
}

void World::Init()
{
	_Time->_WorldTime = 0;
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = 0;
	_Time->_FixedDeltaTime = 0;
	ManagerBase::_World = this;
}


World::~World()
{
	for (auto i : _PreparationSystems)
	{
		i->OnDestroy();
		delete i;
	}
	for (auto i : _SimulationSystems)
	{
		i->OnDestroy();
		delete i;
	}
	for (auto i : _PresentationSystems)
	{
		i->OnDestroy();
		delete i;
	}
	delete _Time;
}

void World::Update()
{
	_Time->_DeltaTime = _Time->_WorldTime - _Time->_LastFrameTime;
	_Time->_LastFrameTime = _Time->_WorldTime;
	_Time->AddFixedDeltaTime(_Time->_DeltaTime);
	bool fixedUpdate = false;
	if (_Time->_FixedDeltaTime >= _Time->_TimeStep)
	{
		_Time->_FixedDeltaTime = 0;
		fixedUpdate = true;
	}
	for (auto i : _PreparationSystems)
	{
		if (i->Enabled()) i->Update();
	}
	if (fixedUpdate)
	{
		for (auto i : _PreparationSystems)
		{
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	for (auto i : _SimulationSystems)
	{
		if (i->Enabled()) i->Update();
	}
	if (fixedUpdate)
	{
		for (auto i : _SimulationSystems)
		{
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	for (auto i : _PresentationSystems)
	{
		if (i->Enabled()) i->Update();
	}
	if (fixedUpdate)
	{
		for (auto i : _PresentationSystems)
		{
			if (i->Enabled()) i->FixedUpdate();
		}
	}
}

WorldTime* World::Time()
{
	return _Time;
}

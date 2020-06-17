#include "pch.h"
#include "World.h"
#include "Core.h"
#include "ManagerBase.h"
#include "EntityCollection.h"
#include "TimeSystem.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "SharedComponentSystem.h"
#include "WindowManager.h"


using namespace UniEngine;

size_t UniEngine::World::GetIndex() {
	return _Index;
}

World::World(size_t index) {
	_Index = index;
	_Time = new EngineTime();
	_EntityCollection = new EntityCollection();
	ManagerBase::_EntityCollection = _EntityCollection;
	ManagerBase::_World = this;
	_Time->_TimeStep = 0.2f;
}

void UniEngine::World::Init()
{
	//Initialization System Group
	CreateSystem<TimeSystem>();

	//Simulation System Group
	CreateSystem<PhysicsSystem>();
	CreateSystem<TransformSystem>();

	//Presentation System Group
	CreateSystem<RenderSystem>();
}



World::~World() {
	for (auto i : _Systems) {
		i->OnDestroy();
		delete i;
	}
	delete _Time;
}
void World::Update() {
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

EntityCollection* UniEngine::World::GetEntityCollection()
{
	return _EntityCollection;
}

EngineTime* UniEngine::World::GetTime()
{
	return _Time;
}

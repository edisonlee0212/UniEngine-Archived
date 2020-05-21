#include "SystemBase.h"
#include "EntityManager.h"
using namespace UniEngine;
SystemBase::SystemBase()
{
	_Enabled = false;
}

void SystemBase::SetEntityManager(UniEngine::EntityManager* entityManager)
{
	_Entities = entityManager;
}

void SystemBase::Enable()
{
	if (!_Enabled) {
		_Enabled = true;
		OnStartRunning();
	}
}

void SystemBase::Disable()
{
	if (_Enabled) {
		_Enabled = false;
		OnStopRuning();
	}
}

bool SystemBase::Enabled()
{
	return _Enabled;
}

EntityManager* UniEngine::SystemBase::Entities()
{
	return _Entities;
}

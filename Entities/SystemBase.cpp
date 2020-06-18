#include "pch.h"
#include "SystemBase.h"
using namespace UniEngine::Entities;
UniEngine::Entities::SystemBase::SystemBase()
{
	_Enabled = false;
}

void UniEngine::Entities::SystemBase::Enable()
{
	if (!_Enabled) {
		_Enabled = true;
		OnStartRunning();
	}
}

void UniEngine::Entities::SystemBase::Disable()
{
	if (_Enabled) {
		_Enabled = false;
		OnStopRuning();
	}
}

bool UniEngine::Entities::SystemBase::Enabled()
{
	return _Enabled;
}

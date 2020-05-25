#include "SystemBase.h"
#include "EntityCollection.h"
using namespace UniEngine;
SystemBase::SystemBase()
{
	_Enabled = false;
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


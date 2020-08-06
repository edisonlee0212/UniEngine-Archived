#include "pch.h"
#include "SystemBase.h"
using namespace UniEngine;
UniEngine::SystemBase::SystemBase()
{
	_Enabled = false;
}

void UniEngine::SystemBase::Enable()
{
	if (!_Enabled) {
		_Enabled = true;
		OnStartRunning();
	}
}

void UniEngine::SystemBase::Disable()
{
	if (_Enabled) {
		_Enabled = false;
		OnStopRuning();
	}
}

bool UniEngine::SystemBase::Enabled()
{
	return _Enabled;
}

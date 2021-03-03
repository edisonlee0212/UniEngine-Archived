#include "pch.h"
#include "SystemBase.h"
using namespace UniEngine;
UniEngine::SystemBase::SystemBase()
{
	m_enabled = false;
}

void UniEngine::SystemBase::Enable()
{
	if (!m_enabled) {
		m_enabled = true;
		OnStartRunning();
	}
}

void UniEngine::SystemBase::Disable()
{
	if (m_enabled) {
		m_enabled = false;
		OnStopRunning();
	}
}

bool UniEngine::SystemBase::Enabled() const
{
	return m_enabled;
}

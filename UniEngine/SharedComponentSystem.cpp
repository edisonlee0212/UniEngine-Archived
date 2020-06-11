#include "pch.h"
#include "SharedComponentSystem.h"

UniEngine::SharedComponentSystem::SharedComponentSystem()
{
}

void UniEngine::SharedComponentSystem::OnCreate()
{
	Enable();
}

void UniEngine::SharedComponentSystem::OnDestroy()
{
	Disable();
}

void UniEngine::SharedComponentSystem::Update()
{
}

void UniEngine::SharedComponentSystem::FixedUpdate()
{
}

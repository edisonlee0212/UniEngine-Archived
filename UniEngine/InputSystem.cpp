#include "InputSystem.h"
using namespace UniEngine;
UniEngine::InputSystem::InputSystem()
{
}

void UniEngine::InputSystem::OnCreate()
{
	Enable();
}

void UniEngine::InputSystem::OnDestroy()
{
	Disable();
}

void UniEngine::InputSystem::Update()
{
}

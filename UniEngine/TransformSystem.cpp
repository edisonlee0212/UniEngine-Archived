#include "TransformSystem.h"

UniEngine::TransformSystem::TransformSystem()
{
}

void UniEngine::TransformSystem::OnCreate()
{
	Enable();
}

void UniEngine::TransformSystem::OnDestroy()
{
	Disable();
}

void UniEngine::TransformSystem::Update()
{
}

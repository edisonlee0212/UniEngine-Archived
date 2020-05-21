#include "RenderSystem.h"
using namespace UniEngine;
UniEngine::RenderSystem::RenderSystem()
{
}

void UniEngine::RenderSystem::OnCreate()
{
	Enable();
}

void UniEngine::RenderSystem::OnDestroy()
{
	Disable();
}

void UniEngine::RenderSystem::Update()
{
}

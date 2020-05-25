#include "RenderSystem.h"
using namespace UniEngine;

void UniEngine::RenderSystem::DrawEntity(Entity* entity)
{
	
}
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
	for (auto i : *(_EntityCollection->Entities())) {
		if (i->GetSharedComponent<Mesh>() && i->GetSharedComponent<Material>()) {
			Rendering::DrawMesh(i->GetSharedComponent<Mesh>(),
				_EntityCollection->GetFixedData<LocalToWorld>(i).value,
				i->GetSharedComponent<Material>()
			);
		}
	}
}

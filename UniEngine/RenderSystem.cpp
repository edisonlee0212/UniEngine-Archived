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


	for (auto i : *(Entities()->Entities())) {
		Rendering::DrawMesh(i->GetSharedComponent<Mesh>(),
			Entities()->GetFixedData<LocalToWorld>(i).value,
			i->GetSharedComponent<Material>()
		);
	}
}

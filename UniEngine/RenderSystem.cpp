#include "RenderSystem.h"
#include "World.h"
using namespace UniEngine;

void UniEngine::RenderSystem::DrawEntity(Entity* entity, Camera* camera)
{
	RenderManager::DrawMesh(entity->GetSharedComponent<Mesh>(),
		_EntityCollection->GetFixedData<LocalToWorld>(entity).value,
		entity->GetSharedComponent<Material>(), camera);
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
	_World->MainCamera()->UpdateCameraVectors();
	_World->MainCamera()->UpdateViewProj();
	_World->MainCamera()->GetRenderTarget()->Bind();
	_World->MainCamera()->UpdateMatrices();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	for (auto i : *(_EntityCollection->Entities())) {
		if (i->GetSharedComponent<Mesh>() && i->GetSharedComponent<Material>()) {
			DrawEntity(i, _World->MainCamera());
		}
	}
}

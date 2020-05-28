#include "RenderSystem.h"
#include "World.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
using namespace UniEngine;

void UniEngine::RenderSystem::RenderToCamera(Camera* camera)
{
	camera->UpdateCameraVectors();
	camera->UpdateViewProj();
	camera->GetRenderTarget()->Bind();
	camera->UpdateMatrices();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	for (auto i : *(_EntityCollection->Entities())) {
		if (_EntityCollection->GetSharedComponent<MeshComponent>(i) && _EntityCollection->GetSharedComponent<MaterialComponent>(i)) {
			DrawEntity(i, camera);
		}
	}
}

void UniEngine::RenderSystem::DrawEntity(Entity* entity, Camera* camera)
{
	RenderManager::DrawMesh(_EntityCollection->GetSharedComponent<MeshComponent>(entity)->Value,
		_EntityCollection->GetFixedData<LocalToWorld>(entity).value,
		_EntityCollection->GetSharedComponent<MaterialComponent>(entity)->Value, camera);
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

	RenderToCamera(_World->MainCamera());
}

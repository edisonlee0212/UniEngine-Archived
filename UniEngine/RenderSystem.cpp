#include "RenderSystem.h"
#include "CameraComponent.h"
#include "World.h"
#include "Default.h"
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


	auto meshMaterials = _EntityCollection->QuerySharedComponents<MeshMaterialComponent>();
	for (auto i : *meshMaterials) {
		auto entities = _EntityCollection->QueryEntities<MeshMaterialComponent>(dynamic_cast<MeshMaterialComponent*>(i->first));
		for (auto j : *entities) {
			DrawEntity(j, camera, dynamic_cast<MeshMaterialComponent*>(i->first));
		}
	}

}

void UniEngine::RenderSystem::DrawEntity(Entity* entity, Camera* camera)
{
	auto meshMaterial = _EntityCollection->GetSharedComponent<MeshMaterialComponent>(entity);
	RenderManager::DrawMesh(meshMaterial->_Mesh,
		_EntityCollection->GetFixedData<LocalToWorld>(entity).value,
		meshMaterial->_Material, camera);
}
void UniEngine::RenderSystem::DrawEntity(Entity* entity, Camera* camera, MeshMaterialComponent* meshMaterialComponent)
{
	RenderManager::DrawMesh(meshMaterialComponent->_Mesh,
		_EntityCollection->GetFixedData<LocalToWorld>(entity).value,
		meshMaterialComponent->_Material, camera);
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
	auto cameras = _EntityCollection->QuerySharedComponents<CameraComponent>();
	for (auto i : *cameras) {
		RenderToCamera(dynamic_cast<CameraComponent*>(i->first)->Value);
	}
}

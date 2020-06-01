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

	auto MMMap = _EntityCollection->QuerySharedComponentMap<MeshMaterialComponent>();
	for (std::pair<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*> i : *MMMap) {
		if (!i.second->second->empty()) {
			auto entity = i.second->second->begin()->second;
			DrawEntity(entity, camera, dynamic_cast<MeshMaterialComponent*>(i.second->first));
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


	auto CMap = _EntityCollection->QuerySharedComponentMap<CameraComponent>();
	for (std::pair<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*> i : *CMap) {
		RenderToCamera(dynamic_cast<CameraComponent*>(i.second->first)->Value);
	}
}

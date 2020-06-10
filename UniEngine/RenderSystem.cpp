#include "RenderSystem.h"
#include "CameraComponent.h"
#include "World.h"
#include "Default.h"
using namespace UniEngine;

void UniEngine::RenderSystem::RenderToCamera(CameraComponent* cameraComponent, Entity* cameraEntity)
{

	Camera* camera = cameraComponent->Value;
	camera->GetRenderTarget()->Bind();
	camera->UpdateMatrices(_EntityCollection->GetFixedData<Position>(cameraEntity).value);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);


	auto meshMaterials = _EntityCollection->QuerySharedComponents<MeshMaterialComponent>();
	if (meshMaterials != nullptr) {
		for (auto i : *meshMaterials) {
			MeshMaterialComponent* mmc = dynamic_cast<MeshMaterialComponent*>(i->first);
			auto entities = _EntityCollection->QueryEntities<MeshMaterialComponent>(mmc);
			for (auto j : *entities) {
				RenderManager::DrawMesh(
					mmc->_Mesh, mmc->_Material,
					_EntityCollection->GetFixedData<LocalToWorld>(j).value,
					camera);
			}
		}
	}
	auto instancedMeshMaterials = _EntityCollection->QuerySharedComponents<InstancedMeshMaterialComponent>();
	if (instancedMeshMaterials != nullptr) {
		for (auto i : *instancedMeshMaterials) {
			InstancedMeshMaterialComponent* immc = dynamic_cast<InstancedMeshMaterialComponent*>(i->first);
			auto entities = _EntityCollection->QueryEntities<InstancedMeshMaterialComponent>(immc);
			for (auto j : *entities) {
				RenderManager::DrawMeshInstanced(
					immc->_Mesh, immc->_Material,
					_EntityCollection->GetFixedData<LocalToWorld>(j).value,
					&immc->_Matrices->at(0), immc->_Matrices->size(),
					camera);
			}
		}
	}
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
		CameraComponent* cc = dynamic_cast<CameraComponent*>(i->first);
		std::vector<Entity*>* entities = _EntityCollection->QueryEntities<CameraComponent>(cc);
		RenderToCamera(cc, entities->at(0));
	}

	
}

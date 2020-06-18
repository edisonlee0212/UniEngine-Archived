#include "pch.h"
#include "RenderSystem.h"
#include "CameraComponent.h"
#include "World.h"
using namespace UniEngine;

bool RenderSystem::_EnableWireFrame;

void UniEngine::RenderSystem::RenderToCamera(CameraComponent* cameraComponent, Entity cameraEntity)
{

	Camera* camera = cameraComponent->Value;
	camera->GetRenderTarget()->Bind();
	camera->UpdateMatrices(EntityManager::GetComponentData<Position>(cameraEntity).value);

	if (_EnableWireFrame) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);


	auto meshMaterials = EntityManager::QuerySharedComponents<MeshMaterialComponent>();
	if (meshMaterials != nullptr) {
		for (auto i : *meshMaterials) {
			MeshMaterialComponent* mmc = dynamic_cast<MeshMaterialComponent*>(i->first);
			auto entities = EntityManager::QueryEntities<MeshMaterialComponent>(mmc);
			for (auto j : *entities) {
				RenderManager::DrawMesh(
					mmc->_Mesh, mmc->_Material,
					EntityManager::GetComponentData<LocalToWorld>(j).value,
					camera);
			}
		}
	}
	auto instancedMeshMaterials = EntityManager::QuerySharedComponents<InstancedMeshMaterialComponent>();
	if (instancedMeshMaterials != nullptr) {
		for (auto i : *instancedMeshMaterials) {
			InstancedMeshMaterialComponent* immc = dynamic_cast<InstancedMeshMaterialComponent*>(i->first);
			auto entities = EntityManager::QueryEntities<InstancedMeshMaterialComponent>(immc);
			for (auto j : *entities) {
				RenderManager::DrawMeshInstanced(
					immc->_Mesh, immc->_Material,
					EntityManager::GetComponentData<LocalToWorld>(j).value,
					&immc->_Matrices->at(0), immc->_Matrices->size(),
					camera);
			}
		}
	}
}


void UniEngine::RenderSystem::SetWireFrameMode(bool value)
{
	_EnableWireFrame = value;
}

UniEngine::RenderSystem::RenderSystem()
{	
}

void UniEngine::RenderSystem::OnCreate()
{
	_EnableWireFrame = false;
	Enable();
}

void UniEngine::RenderSystem::OnDestroy()
{
	Disable();
}

void UniEngine::RenderSystem::Update()
{
	auto cameras = EntityManager::QuerySharedComponents<CameraComponent>();
	for (auto i : *cameras) {
		CameraComponent* cc = dynamic_cast<CameraComponent*>(i->first);
		std::vector<Entity>* entities = EntityManager::QueryEntities<CameraComponent>(cc);
		RenderToCamera(cc, entities->at(0));
	}

	
}

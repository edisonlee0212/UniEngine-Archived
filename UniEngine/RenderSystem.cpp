#include "pch.h"
#include "RenderSystem.h"
#include "CameraComponent.h"
#include "World.h"
using namespace UniEngine;

bool RenderSystem::_EnableWireFrame;

void UniEngine::RenderSystem::RenderToCamera(CameraComponent* cameraComponent, Entity cameraEntity)
{

	Camera* camera = cameraComponent->Value;
	camera->Bind();
	Camera::_MainCameraInfoBlock.UpdateMatrices(camera,
		EntityManager::GetComponentData<Translation>(cameraEntity).value,
		EntityManager::GetComponentData<Rotation>(cameraEntity).value
		);
	Camera::_MainCameraInfoBlock.UploadMatrices(camera->_CameraData);
	
	

	auto worldBound = _World->GetBound();
	glm::vec3 minBound = glm::vec3(INT_MAX);
	glm::vec3 maxBound = glm::vec3(INT_MIN);
	auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshMaterialComponent>();
	if (meshMaterials != nullptr) {
		for (auto mmc : *meshMaterials) {
			auto entities = EntityManager::GetSharedComponentEntities<MeshMaterialComponent>(mmc);
			for (auto j : *entities) {
				auto ltw = EntityManager::GetComponentData<LocalToWorld>(j).value;
				auto scale = EntityManager::GetComponentData<Scale>(j).value;
				auto meshBound = mmc->_Mesh->GetBound();
				glm::vec3 center = ltw * glm::vec4(meshBound.Center, 1.0f);
				glm::vec3 size = glm::vec4(meshBound.Size, 0) * ltw / 2.0f;
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));

				RenderManager::DrawMesh(
					mmc->_Mesh,
					mmc->_Material,
					ltw,
					camera);
			}
		}
	}
	auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshMaterialComponent>();
	if (instancedMeshMaterials != nullptr) {
		for (auto immc : *instancedMeshMaterials) {
			auto entities = EntityManager::GetSharedComponentEntities<InstancedMeshMaterialComponent>(immc);
			for (auto j : *entities) {
				RenderManager::DrawMeshInstanced(
					immc->_Mesh,
					immc->_Material,
					EntityManager::GetComponentData<LocalToWorld>(j).value,
					immc->_Matrices->data(),
					immc->_Matrices->size(),
					camera);
			}
		}
	}
	worldBound.Size = (maxBound - minBound) / 2.0f;
	worldBound.Center = (maxBound + minBound) / 2.0f;
	worldBound.Radius = glm::length(worldBound.Size);
	_World->SetBound(worldBound);
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
	auto cameras = EntityManager::GetSharedComponentDataArray<CameraComponent>();
	for (auto cc : *cameras) {
		std::vector<Entity>* entities = EntityManager::GetSharedComponentEntities<CameraComponent>(cc);
		RenderToCamera(cc, entities->at(0));
	}

	
}

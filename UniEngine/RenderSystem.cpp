#include "pch.h"
#include "TransformSystem.h"
#include "RenderSystem.h"
#include "CameraComponent.h"
#include "World.h"
#include "UniEngine.h"
using namespace UniEngine;

bool RenderSystem::_EnableWireFrame;

void UniEngine::RenderSystem::RenderToMainCamera(CameraComponent* cameraComponent, Entity cameraEntity)
{

	Camera* camera = cameraComponent->Value;
	camera->Bind();
	Camera::_MainCameraInfoBlock.UpdateMatrices(camera,
		EntityManager::GetComponentData<Translation>(cameraEntity).Value,
		EntityManager::GetComponentData<Rotation>(cameraEntity).Value
		);
	Camera::_MainCameraInfoBlock.UploadMatrices(camera->_CameraData);
	
	

	auto worldBound = _World->GetBound();
	glm::vec3 minBound = glm::vec3((int)INT_MAX);
	glm::vec3 maxBound = glm::vec3((int)INT_MIN);
	auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshMaterialComponent>();
	if (meshMaterials != nullptr) {
		for (const auto& mmc : *meshMaterials) {
			auto entities = EntityManager::GetSharedComponentEntities<MeshMaterialComponent>(mmc);
			if (mmc->_Material == nullptr || mmc->_Mesh == nullptr) continue;
			for (const auto& j : *entities) {
				if (EntityManager::HasComponentData<CameraLayerMask>(j) && !(EntityManager::GetComponentData<CameraLayerMask>(j).Value & CameraLayer_MainCamera)) continue;
				auto ltw = EntityManager::GetComponentData<LocalToWorld>(j).Value;
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
		for (const auto& immc : *instancedMeshMaterials) {
			if (immc->_Material == nullptr || immc->_Mesh == nullptr) continue;
			auto entities = EntityManager::GetSharedComponentEntities<InstancedMeshMaterialComponent>(immc);
			for (const auto& j : *entities) {
				if (EntityManager::HasComponentData<CameraLayerMask>(j) && !(EntityManager::GetComponentData<CameraLayerMask>(j).Value & CameraLayer_MainCamera)) continue;
				RenderManager::DrawMeshInstanced(
					immc->_Mesh,
					immc->_Material,
					EntityManager::GetComponentData<LocalToWorld>(j).Value,
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
	/*
	auto cameras = EntityManager::GetSharedComponentDataArray<CameraComponent>();
	for (const auto& cc : *cameras) {
		std::vector<Entity>* entities = EntityManager::GetSharedComponentEntities<CameraComponent>(cc);
		RenderToCamera(cc, entities->at(0));
	}
	*/
	RenderToMainCamera(Application::GetMainCameraComponent(), Application::GetMainCameraEntity());
}

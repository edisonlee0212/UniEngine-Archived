#include "pch.h"
#include "TransformSystem.h"
#include "RenderSystem.h"
#include "CameraComponent.h"
#include "UniEngine.h"
using namespace UniEngine;

bool RenderSystem::_EnableWireFrame;


void UniEngine::RenderSystem::OnCreate()
{
	_EnableWireFrame = false;
	EntityEditorSystem::AddComponentInspector<DirectionalLightComponent>([](ComponentBase* data)
		{
			std::stringstream stream;
			stream << std::hex << "0x" << (size_t)data;
			auto* dl = static_cast<DirectionalLightComponent*>((void*)data);
			ImGui::ColorEdit3("Diffuse", &dl->diffuse[0]);
			ImGui::DragFloat("Diffuse Brightness", &dl->diffuseBrightness, 0.1f);
			ImGui::ColorEdit3("Specular", &dl->specular[0]);
			ImGui::DragFloat("Specular Brightness", &dl->specularBrightness, 0.1f);
			ImGui::DragFloat("Bias", &dl->depthBias, 0.001f);
			ImGui::InputFloat("Normal Offset", &dl->normalOffset, 0.01f);
			ImGui::DragFloat("Light Size", &dl->lightSize, 0.1f);
		});

	EntityEditorSystem::AddComponentInspector<PointLightComponent>([](ComponentBase* data)
		{
			std::stringstream stream;
			stream << std::hex << "0x" << (size_t)data;
			auto* dl = static_cast<PointLightComponent*>((void*)data);
			ImGui::ColorEdit3("Diffuse", &dl->diffuse[0]);
			ImGui::DragFloat("Diffuse Brightness", &dl->diffuseBrightness, 0.1f);
			ImGui::ColorEdit3("Specular", &dl->specular[0]);
			ImGui::DragFloat("Specular Brightness", &dl->specularBrightness, 0.1f);
			ImGui::DragFloat("Bias", &dl->bias, 0.001f);

			ImGui::DragFloat("Constant", &dl->constant, 0.1f);
			ImGui::DragFloat("Linear", &dl->quadratic, 0.1f);
			
			//ImGui::InputFloat("Normal Offset", &dl->normalOffset, 0.01f);
			//ImGui::DragFloat("Light Size", &dl->lightSize, 0.1f);
		});
	Enable();
}


void UniEngine::RenderSystem::RenderToMainCamera(CameraComponent* cameraComponent, Entity cameraEntity)
{
	auto camera = cameraComponent->Value;


	camera->Bind();
	Camera::_MainCameraInfoBlock.UpdateMatrices(camera.get(),
		EntityManager::GetComponentData<Translation>(cameraEntity).Value,
		EntityManager::GetComponentData<Rotation>(cameraEntity).Value
	);
	Camera::_MainCameraInfoBlock.UploadMatrices(camera->_CameraData);
	auto worldBound = _World->GetBound();
	glm::vec3 minBound = glm::vec3((int)INT_MAX);
	glm::vec3 maxBound = glm::vec3((int)INT_MIN);


	auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
	if (meshMaterials != nullptr) {
		for (const auto& mmc : *meshMaterials) {
			auto entities = EntityManager::GetSharedComponentEntities<MeshRenderer>(mmc);
			if (mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
			if (mmc->BackCulling)glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
			for (auto& j : *entities) {
				if (!j.Enabled()) continue;
				if (EntityManager::HasComponentData<CameraLayerMask>(j) && !(EntityManager::GetComponentData<CameraLayerMask>(j).Value & CameraLayer_MainCamera)) continue;
				auto ltw = EntityManager::GetComponentData<LocalToWorld>(j).Value;
				auto meshBound = mmc->Mesh->GetBound();
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
					mmc->Mesh.get(),
					mmc->Material.get(),
					ltw,
					camera.get(),
					mmc->ReceiveShadow);

			}
		}
	}
	auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshRenderer>();
	if (instancedMeshMaterials != nullptr) {
		for (const auto& immc : *instancedMeshMaterials) {
			if (immc->Material == nullptr || immc->Mesh == nullptr) continue;
			if (immc->BackCulling)glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
			auto entities = EntityManager::GetSharedComponentEntities<InstancedMeshRenderer>(immc);
			for (auto& j : *entities) {
				if (!j.Enabled()) continue;
				if (EntityManager::HasComponentData<CameraLayerMask>(j) && !(EntityManager::GetComponentData<CameraLayerMask>(j).Value & CameraLayer_MainCamera)) continue;
				auto ltw = EntityManager::GetComponentData<LocalToWorld>(j).Value;
				glm::vec3 center = ltw * glm::vec4(immc->BoundingBox.Center, 1.0f);
				glm::vec3 size = glm::vec4(immc->BoundingBox.Size, 0) * ltw / 2.0f;
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
				RenderManager::DrawMeshInstanced(
					immc->Mesh.get(),
					immc->Material.get(),
					ltw,
					immc->Matrices.data(),
					immc->Matrices.size(),
					camera.get(),
					immc->ReceiveShadow);
			}
		}
	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0);


	
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
	//RenderToMainCamera(Application::GetMainCameraComponent(), Application::GetMainCameraEntity());
}

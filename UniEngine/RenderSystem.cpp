#include "pch.h"
#include "TransformSystem.h"
#include "RenderSystem.h"
#include "CameraComponent.h"
#include "UniEngine.h"
using namespace UniEngine;

bool RenderSystem::_EnableWireFrame;
#ifdef DEFERRED_RENDERING

void RenderSystem::ResizeGBuffer(int x, int y)
{
	const auto originalResolution = _GBuffer->GetResolution();
	if(static_cast<int>(originalResolution.x) == x && static_cast<int>(originalResolution.y) == y) return;
	_GBuffer->SetResolution(x, y);
	_GPositionBuffer->Texture()->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GNormalBuffer->Texture()->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GColorSpecularBuffer->Texture()->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GDepthBuffer->AllocateStorage(GL_DEPTH_COMPONENT32F, x, y);
	
	_GBuffer->AttachRenderBuffer(_GDepthBuffer.get(), GL_DEPTH_ATTACHMENT);
	_GBuffer->AttachTexture(_GPositionBuffer->Texture(), GL_COLOR_ATTACHMENT0);
	_GBuffer->AttachTexture(_GNormalBuffer->Texture(), GL_COLOR_ATTACHMENT1);
	_GBuffer->AttachTexture(_GColorSpecularBuffer->Texture(), GL_COLOR_ATTACHMENT2);
}
#endif

void UniEngine::RenderSystem::OnCreate()
{
	_EnableWireFrame = false;

#ifdef DEFERRED_RENDERING
	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/DeferredLighting.frag");
	
	_GBufferLightingPass = std::make_shared<GLProgram> (
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
	);
	
	_GBuffer = std::make_shared<RenderTarget>(0, 0);

	_GDepthBuffer = std::make_shared<GLRenderBuffer>();
	
	_GPositionBuffer = std::make_shared<Texture2D>(TextureType::NONE);
	auto gPositionTex = new GLTexture2D(1, GL_RGBA32F, 0, 0, false);
	gPositionTex->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gPositionTex->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GPositionBuffer->SetTexture(gPositionTex);
	
	_GNormalBuffer = std::make_shared<Texture2D>(TextureType::NONE);
	auto gNormalTex = new GLTexture2D(1, GL_RGBA32F, 0, 0, false);
	gNormalTex->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gNormalTex->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GNormalBuffer->SetTexture(gNormalTex);
	
	_GColorSpecularBuffer = std::make_shared<Texture2D>(TextureType::NONE);
	auto gColSpecTex = new GLTexture2D(1, GL_RGBA32F, 0, 0, false);
	gColSpecTex->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gColSpecTex->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GColorSpecularBuffer->SetTexture(gColSpecTex);
	
	auto camera = Application::GetMainCameraComponent()->Value;
	ResizeGBuffer(camera->GetResolution().x, camera->GetResolution().y);
#endif

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
#ifndef DEFERRED_RENDERING
				RenderManager::DrawMesh(
					mmc->Mesh.get(),
					mmc->Material.get(),
					ltw,
					camera.get(),
					mmc->ReceiveShadow);
#endif
#ifdef DEFERRED_RENDERING
				RenderManager::DrawMesh(
					mmc->Mesh.get(),
					mmc->Material.get(),
					ltw,
					_GBuffer.get(),
					mmc->ReceiveShadow);
#endif
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
#ifndef DEFERRED_RENDERING
				RenderManager::DrawMeshInstanced(
					immc->Mesh.get(),
					immc->Material.get(),
					ltw,
					immc->Matrices.data(),
					immc->Matrices.size(),
					camera.get(),
					immc->ReceiveShadow);
#endif
#ifdef DEFERRED_RENDERING
				RenderManager::DrawMeshInstanced(
					immc->Mesh.get(),
					immc->Material.get(),
					ltw,
					immc->Matrices.data(),
					immc->Matrices.size(),
					_GBuffer.get(),
					immc->ReceiveShadow);
#endif	
			}
		}
	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
#ifdef DEFERRED_RENDERING
	camera->Bind();
	_GBufferLightingPass->Bind();
	_GPositionBuffer->Texture()->Bind(2);
	_GNormalBuffer->Texture()->Bind(3);
	_GColorSpecularBuffer->Texture()->Bind(4);
	_GBufferLightingPass->SetBool("receiveShadow", true);
	_GBufferLightingPass->SetInt("directionalShadowMap", 0);
	_GBufferLightingPass->SetInt("pointShadowMap", 1);
	_GBufferLightingPass->SetBool("enableShadow", RenderManager::_EnableShadow);
	_GBufferLightingPass->SetInt("gPosition", 2);
	_GBufferLightingPass->SetInt("gNormal", 3);
	_GBufferLightingPass->SetInt("gAlbedoSpec", 4);
	
	Default::GLPrograms::ScreenVAO->Bind();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
#endif

	
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
	RenderToMainCamera(Application::GetMainCameraComponent(), Application::GetMainCameraEntity());
}

#include "pch.h"
#include "RenderManager.h"
#include "TransformManager.h"
#include <gtx/matrix_decompose.hpp>
#include "PostProcessing.h"
#include "imgui_internal.h"
#include "UniEngine.h"
#include "Ray.h"
using namespace UniEngine;
#pragma region Global Var
bool RenderManager::m_enableRenderMenu = false;
bool RenderManager::m_enableInfoWindow = false;
#pragma region Shadow
#pragma region DirectionalMap
GLUBO* RenderManager::m_shadowCascadeInfoBlock;
LightSettingsBlock RenderManager::m_lightSettings;
float RenderManager::m_shadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = { 0.15f, 0.3f, 0.5f, 1.0f };
float RenderManager::m_maxShadowDistance = 500;
bool RenderManager::m_stableFit = true;
#pragma endregion
size_t RenderManager::m_shadowMapResolution = 4096;
bool RenderManager::m_enableLightMenu = true;
GLUBO* RenderManager::m_pointLightBlock;
GLUBO* RenderManager::m_spotLightBlock;
GLUBO* RenderManager::m_directionalLightBlock;
DirectionalLightInfo RenderManager::m_directionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
PointLightInfo RenderManager::m_pointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLightInfo RenderManager::m_spotLights[Default::ShaderIncludes::MaxSpotLightAmount];

std::unique_ptr<DirectionalLightShadowMap> RenderManager::m_directionalLightShadowMap;
std::unique_ptr<PointLightShadowMap> RenderManager::m_pointLightShadowMap;
std::unique_ptr<SpotLightShadowMap> RenderManager::m_spotLightShadowMap;
std::unique_ptr<GLProgram> RenderManager::m_directionalLightProgram;
std::unique_ptr<GLProgram> RenderManager::m_directionalLightInstancedProgram;
std::unique_ptr<GLProgram> RenderManager::m_pointLightProgram;
std::unique_ptr<GLProgram> RenderManager::m_pointLightInstancedProgram;
std::unique_ptr<GLProgram> RenderManager::m_spotLightProgram;
std::unique_ptr<GLProgram> RenderManager::m_spotLightInstancedProgram;

#pragma endregion
#pragma region Render
MaterialSettingsBlock RenderManager::m_materialSettings;
std::unique_ptr<GLUBO> RenderManager::m_materialSettingsBuffer;
CameraComponent* RenderManager::_MainCameraComponent;
int RenderManager::m_mainCameraResolutionX = 1;
int RenderManager::m_mainCameraResolutionY = 1;
size_t RenderManager::m_drawCall;
size_t RenderManager::m_triangles;
std::unique_ptr<GLUBO> RenderManager::m_kernelBlock;
std::unique_ptr<GLProgram> RenderManager::m_gBufferInstancedPrepass;
std::unique_ptr<GLProgram> RenderManager::m_gBufferPrepass;
std::unique_ptr<GLProgram> RenderManager::m_gBufferLightingPass;

#pragma endregion
#pragma endregion

void RenderManager::RenderToCameraDeferred(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds)
{
	cameraComponent->m_gBuffer->Bind();
	unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 , GL_COLOR_ATTACHMENT3 };
	cameraComponent->m_gBuffer->GetFrameBuffer()->DrawBuffers(4, attachments);
	cameraComponent->m_gBuffer->Clear();
	const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
	if (owners) {
		auto& program = m_gBufferPrepass;
		program->Bind();
		for (auto owner : *owners) {
			if (!owner.IsEnabled()) continue;
			auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
			if (!mmc->IsEnabled() || mmc->m_material == nullptr || mmc->m_mesh == nullptr || mmc->m_forwardRendering) continue;
			if (mmc->m_material->BlendingMode != MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).m_value & static_cast<size_t>(CameraLayer::MainCamera))) continue;
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
			if (calculateBounds) {
				auto meshBound = mmc->m_mesh->GetBound();
				meshBound.ApplyTransform(ltw);
				glm::vec3 center = meshBound.Center();
				glm::vec3 size = meshBound.Size();
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			m_materialSettings.m_receiveShadow = mmc->m_receiveShadow;
			DeferredPrepass(
				mmc->m_mesh.get(),
				mmc->m_material.get(),
				ltw
			);
		}
	}

	owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
	if (owners) {
		auto& program = m_gBufferInstancedPrepass;
		program->Bind();
		for (auto owner : *owners) {
			if (!owner.IsEnabled()) continue;
			auto& immc = owner.GetPrivateComponent<Particles>();
			if (!immc->IsEnabled() || immc->Material == nullptr || immc->Mesh == nullptr || immc->ForwardRendering) continue;
			if (immc->Material->BlendingMode != MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).m_value & static_cast<size_t>(CameraLayer::MainCamera))) continue;
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
			if (calculateBounds) {
				auto meshBound = immc->Mesh->GetBound();
				meshBound.ApplyTransform(ltw);
				glm::vec3 center = meshBound.Center();
				glm::vec3 size = meshBound.Size();
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			m_materialSettings.m_receiveShadow = immc->ReceiveShadow;
			DeferredPrepassInstanced(
				immc->Mesh.get(),
				immc->Material.get(),
				ltw,
				immc->Matrices.data(),
				immc->Matrices.size()
			);
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	Default::GLPrograms::ScreenVAO->Bind();
	

	cameraComponent->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	m_gBufferLightingPass->Bind();
	
	cameraComponent->m_gPositionBuffer->Bind(3);
	cameraComponent->m_gNormalBuffer->Bind(4);
	cameraComponent->m_gColorSpecularBuffer->Bind(5);
	cameraComponent->m_gMetallicRoughnessAo->Bind(6);
	m_gBufferLightingPass->SetInt("gPositionShadow", 3);
	m_gBufferLightingPass->SetInt("gNormalShininess", 4);
	m_gBufferLightingPass->SetInt("gAlbedoSpecular", 5);
	m_gBufferLightingPass->SetInt("gMetallicRoughnessAO", 6);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	auto res = cameraComponent->GetResolution();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, cameraComponent->m_gBuffer->GetFrameBuffer()->Id());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, cameraComponent->GetFrameBuffer()->Id()); // write to default framebuffer
	glBlitFramebuffer(
		0, 0, res.x, res.y, 0, 0, res.x, res.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST
	);
	RenderTarget::BindDefault();
}

void RenderManager::RenderBackGround(const std::unique_ptr<CameraComponent>& cameraComponent)
{
	cameraComponent->Bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	if (cameraComponent->m_drawSkyBox && cameraComponent->m_skyBox.get()) {
		Default::GLPrograms::SkyboxProgram->Bind();
		Default::GLPrograms::SkyboxVAO->Bind();
		cameraComponent->m_skyBox->Texture()->Bind(3);
		Default::GLPrograms::SkyboxProgram->SetInt("skybox", 3);
	}
	else
	{
		Default::GLPrograms::BackGroundProgram->Bind();
		Default::GLPrograms::SkyboxVAO->Bind();
		Default::GLPrograms::BackGroundProgram->SetFloat3("clearColor", cameraComponent->m_clearColor);
	}
	glDrawArrays(GL_TRIANGLES, 0, 36);
	GLVAO::BindDefault();
	glDepthFunc(GL_LESS); // set depth function back to default
}

void RenderManager::RenderToCameraForward(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds)
{
	bool debug = cameraComponent.get() == EditorManager::GetInstance().m_sceneCamera.get();
	cameraComponent->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	std::map<float, std::pair<std::pair<Entity, MeshRenderer*>, glm::mat4>> transparentEntities;
	std::map<float, std::pair<std::pair<Entity, Particles*>, glm::mat4>> transparentInstancedEntities;
	const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
	if (owners) {
		for (auto owner : *owners) {
			if (!owner.IsEnabled()) continue;
			auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
			if (!mmc->IsEnabled() || mmc->m_material == nullptr || mmc->m_mesh == nullptr || !mmc->m_forwardRendering && mmc->m_material->BlendingMode == MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).m_value & static_cast<size_t>(CameraLayer::MainCamera))) continue;
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
			auto meshBound = mmc->m_mesh->GetBound();
			meshBound.ApplyTransform(ltw);
			glm::vec3 center = meshBound.Center();
			glm::vec3 size = meshBound.Size();
			if (calculateBounds) {
				
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			if (mmc->m_material->BlendingMode == MaterialBlendingMode::OFF) {
				transparentEntities.insert({ glm::distance(cameraTransform.GetPosition(), center), std::make_pair(std::make_pair(owner, mmc.get()), ltw) });
				continue;
			}
			DrawMesh(
				mmc->m_mesh.get(),
				mmc->m_material.get(),
				ltw,
				mmc->m_receiveShadow);
		}
	}
	owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
	if (owners) {
		for (auto owner : *owners) {
			if (!owner.IsEnabled()) continue;
			auto& immc = owner.GetPrivateComponent<Particles>();
			if (!immc->IsEnabled() || immc->Material == nullptr || immc->Mesh == nullptr || !immc->ForwardRendering && immc->Material->BlendingMode == MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).m_value & static_cast<size_t>(CameraLayer::MainCamera))) continue;
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
			if (calculateBounds) {
				auto meshBound = immc->Mesh->GetBound();
				meshBound.ApplyTransform(ltw);
				glm::vec3 center = meshBound.Center();
				glm::vec3 size = meshBound.Size();
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			if (immc->Material->BlendingMode == MaterialBlendingMode::OFF) {
				transparentInstancedEntities.insert({ glm::distance(cameraTransform.GetPosition(), glm::vec3(ltw[3])), std::make_pair(std::make_pair(owner, immc.get()), ltw) });
				continue;
			}
			DrawMeshInstanced(
				immc->Mesh.get(),
				immc->Material.get(),
				ltw,
				immc->Matrices.data(),
				immc->Matrices.size(),
				immc->ReceiveShadow);
		}
	}

	//Draw all transparent objects here:
	for (auto pair = transparentEntities.rbegin(); pair != transparentEntities.rend(); ++pair)
	{
		const auto* mmc = pair->second.first.second;
		DrawMesh(
			mmc->m_mesh.get(),
			mmc->m_material.get(),
			pair->second.second,
			mmc->m_receiveShadow
		);
	}
	for (auto pair = transparentInstancedEntities.rbegin(); pair != transparentInstancedEntities.rend(); ++pair)
	{
		const auto* immc = pair->second.first.second;
		glm::mat4 ltw = pair->second.second;
		Mesh* mesh = immc->Mesh.get();
		Material* material = immc->Material.get();
		const glm::mat4* matrices = immc->Matrices.data();
		DrawMeshInstanced(mesh, material, ltw, matrices, immc->Matrices.size(), immc->ReceiveShadow);
	}
}

void RenderManager::Init()
{
	
	m_materialSettingsBuffer = std::make_unique<GLUBO>();
	m_materialSettingsBuffer->SetData(sizeof(MaterialSettingsBlock), nullptr, GL_STREAM_DRAW);
	m_materialSettingsBuffer->SetBase(6);
#pragma region Kernel Setup
	std::vector<glm::vec4> uniformKernel;
	std::vector<glm::vec4> gaussianKernel;
	for (unsigned int i = 0; i < Default::ShaderIncludes::MaxKernelAmount; i++)
	{
		uniformKernel.emplace_back(glm::vec4(glm::ballRand(1.0f), 1.0f));
		gaussianKernel.emplace_back(glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f));
	}
	m_kernelBlock = std::make_unique<GLUBO>();
	m_kernelBlock->SetBase(5);
	m_kernelBlock->SetData(sizeof(glm::vec4) * uniformKernel.size() + sizeof(glm::vec4) * gaussianKernel.size(), NULL, GL_STATIC_DRAW);
	m_kernelBlock->SubData(0, sizeof(glm::vec4) * uniformKernel.size(), uniformKernel.data());
	m_kernelBlock->SubData(sizeof(glm::vec4) * uniformKernel.size(), sizeof(glm::vec4) * gaussianKernel.size(), gaussianKernel.data());

#pragma endregion
#pragma region Shadow
	m_shadowCascadeInfoBlock = new GLUBO();
	m_shadowCascadeInfoBlock->SetData(sizeof(LightSettingsBlock), nullptr, GL_DYNAMIC_DRAW);
	m_shadowCascadeInfoBlock->SetBase(4);

#pragma region LightInfoBlocks
	m_directionalLightBlock = new GLUBO();
	m_pointLightBlock = new GLUBO();
	m_spotLightBlock = new GLUBO();
	size_t size = 16 + Default::ShaderIncludes::MaxDirectionalLightAmount * sizeof(DirectionalLightInfo);
	m_directionalLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	m_directionalLightBlock->SetBase(1);
	size = 16 + Default::ShaderIncludes::MaxPointLightAmount * sizeof(PointLightInfo);
	m_pointLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	m_pointLightBlock->SetBase(2);
	size = 16 + Default::ShaderIncludes::MaxSpotLightAmount * sizeof(SpotLightInfo);
	m_spotLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	m_spotLightBlock->SetBase(3);
#pragma endregion
#pragma region DirectionalLight
	m_directionalLightShadowMap = std::make_unique<DirectionalLightShadowMap>(m_shadowMapResolution);

	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/DirectionalLightShadowMap.vert"));
	std::string fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/DirectionalLightShadowMap.frag"));
	std::string geomShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Geometry/DirectionalLightShadowMap.geom"));

	auto vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	auto fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);
	auto geomShader = std::make_shared<GLShader>(ShaderType::Geometry);
	geomShader->Compile(geomShaderCode);


	m_directionalLightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/DirectionalLightShadowMapInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	m_directionalLightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);

#pragma region PointLight
	m_pointLightShadowMap = std::make_unique<PointLightShadowMap>(m_shadowMapResolution);
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/PointLightShadowMap.vert"));
	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/PointLightShadowMap.frag"));
	geomShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Geometry/PointLightShadowMap.geom"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);
	geomShader = std::make_shared<GLShader>(ShaderType::Geometry);
	geomShader->Compile(geomShaderCode);

	m_pointLightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/PointLightShadowMapInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	m_pointLightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);
#pragma endregion
#pragma region SpotLight
	m_spotLightShadowMap = std::make_unique<SpotLightShadowMap>(m_shadowMapResolution);
	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/SpotLightShadowMap.vert"));
	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SpotLightShadowMap.frag"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);


	m_spotLightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/SpotLightShadowMapInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	m_spotLightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);
#pragma endregion
#pragma endregion
	
#pragma region GBuffer
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));
	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/StandardDeferredLighting.frag"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);

	m_gBufferLightingPass = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Standard.vert"));

	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform
		+ "\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/StandardDeferred.frag"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);

	m_gBufferPrepass = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/StandardInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	m_gBufferInstancedPrepass = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

#pragma endregion
#pragma region SSAO
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));
	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOGeometry.frag"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);

	
#pragma endregion
}

void UniEngine::RenderManager::PreUpdate()
{
	m_triangles = 0;
	m_drawCall = 0;
	if (_MainCameraComponent != nullptr) {
		if(_MainCameraComponent->m_allowAutoResize) _MainCameraComponent->ResizeResolution(m_mainCameraResolutionX, m_mainCameraResolutionY);
	}
	const std::vector<Entity>* cameraEntities = EntityManager::GetPrivateComponentOwnersList<CameraComponent>();
	if (cameraEntities != nullptr)
	{
		for (auto cameraEntity : *cameraEntities) {
			if (!cameraEntity.IsEnabled()) continue;
			auto& cameraComponent = cameraEntity.GetPrivateComponent<CameraComponent>();
			if(cameraComponent->IsEnabled()) cameraComponent->Clear();
		}
	}
	auto worldBound = Application::GetCurrentWorld()->GetBound();
	glm::vec3 maxBound = worldBound.m_max;
	glm::vec3 minBound = worldBound.m_min;
	if (_MainCameraComponent != nullptr) {
		auto mainCameraEntity = _MainCameraComponent->GetOwner();
		if (mainCameraEntity.IsEnabled()) {
			auto& mainCamera = _MainCameraComponent;
#pragma region Shadow
			if (_MainCameraComponent->IsEnabled()) {
				auto ltw = mainCameraEntity.GetComponentData<GlobalTransform>();
				glm::vec3 mainCameraPos = ltw.GetPosition();
				glm::quat mainCameraRot = ltw.GetRotation();
				m_shadowCascadeInfoBlock->SubData(0, sizeof(LightSettingsBlock), &m_lightSettings);
				const std::vector<Entity>* directionalLightEntities = EntityManager::GetPrivateComponentOwnersList<DirectionalLight>();
				size_t size = 0;
				//1.	利用EntityManager找到场景内所有Light instance。
				if (directionalLightEntities && !directionalLightEntities->empty()) {
					size = directionalLightEntities->size();
					size_t enabledSize = 0;
					for (int i = 0; i < size; i++) {
						Entity lightEntity = directionalLightEntities->at(i);
						if (!lightEntity.IsEnabled()) continue;
						const auto& dlc = lightEntity.GetPrivateComponent<DirectionalLight>();
						if (!dlc->IsEnabled()) continue;
						glm::quat rotation = lightEntity.GetComponentData<GlobalTransform>().GetRotation();
						glm::vec3 lightDir = glm::normalize(rotation * glm::vec3(0, 0, 1));
						float planeDistance = 0;
						glm::vec3 center;
						m_directionalLights[enabledSize].m_direction = glm::vec4(lightDir, 0.0f);
						m_directionalLights[enabledSize].m_diffuse = glm::vec4(dlc->m_diffuse * dlc->m_diffuseBrightness, dlc->m_castShadow);
						m_directionalLights[enabledSize].m_specular = glm::vec4(0.0f);
						for (int split = 0; split < Default::ShaderIncludes::ShadowCascadeAmount; split++) {
							//2.	计算Cascade Split所需信息
							float splitStart = 0;
							float splitEnd = m_maxShadowDistance;
							if (split != 0) splitStart = m_maxShadowDistance * m_shadowCascadeSplit[split - 1];
							if (split != Default::ShaderIncludes::ShadowCascadeAmount - 1) splitEnd = m_maxShadowDistance * m_shadowCascadeSplit[split];
							m_lightSettings.m_splitDistance[split] = splitEnd;
							glm::mat4 lightProjection, lightView;
							float max = 0;
							glm::vec3 lightPos;
							glm::vec3 cornerPoints[8];
							mainCamera->CalculateFrustumPoints(splitStart, splitEnd, mainCameraPos, mainCameraRot, cornerPoints);
							glm::vec3 cameraFrustumCenter = (mainCameraRot * glm::vec3(0, 0, -1)) * ((splitEnd - splitStart) / 2.0f + splitStart) + mainCameraPos;
							if (m_stableFit) {
								//Less detail but no shimmering when rotating the camera.
								//max = glm::distance(cornerPoints[4], cameraFrustumCenter);
								max = splitEnd;
							}
							else {
								//More detail but cause shimmering when rotating camera. 
								max = glm::max(max, glm::distance(cornerPoints[0], ClosestPointOnLine(cornerPoints[0], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[1], ClosestPointOnLine(cornerPoints[1], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[2], ClosestPointOnLine(cornerPoints[2], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[3], ClosestPointOnLine(cornerPoints[3], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[4], ClosestPointOnLine(cornerPoints[4], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[5], ClosestPointOnLine(cornerPoints[5], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[6], ClosestPointOnLine(cornerPoints[6], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
								max = glm::max(max, glm::distance(cornerPoints[7], ClosestPointOnLine(cornerPoints[7], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
							}


							glm::vec3 p0 = ClosestPointOnLine(glm::vec3(maxBound.x, maxBound.y, maxBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);
							glm::vec3 p7 = ClosestPointOnLine(glm::vec3(minBound.x, minBound.y, minBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);

							float d0 = glm::distance(p0, p7);

							glm::vec3 p1 = ClosestPointOnLine(glm::vec3(maxBound.x, maxBound.y, minBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);
							glm::vec3 p6 = ClosestPointOnLine(glm::vec3(minBound.x, minBound.y, maxBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);

							float d1 = glm::distance(p1, p6);

							glm::vec3 p2 = ClosestPointOnLine(glm::vec3(maxBound.x, minBound.y, maxBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);
							glm::vec3 p5 = ClosestPointOnLine(glm::vec3(minBound.x, maxBound.y, minBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);

							float d2 = glm::distance(p2, p5);

							glm::vec3 p3 = ClosestPointOnLine(glm::vec3(maxBound.x, minBound.y, minBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);
							glm::vec3 p4 = ClosestPointOnLine(glm::vec3(minBound.x, maxBound.y, maxBound.z), cameraFrustumCenter, cameraFrustumCenter + lightDir);

							float d3 = glm::distance(p3, p4);

							center = ClosestPointOnLine(worldBound.Center(), cameraFrustumCenter, cameraFrustumCenter + lightDir);
							planeDistance = glm::max(glm::max(d0, d1), glm::max(d2, d3));
							lightPos = center - lightDir * planeDistance;
							lightView = glm::lookAt(lightPos, lightPos + lightDir, glm::normalize(rotation * glm::vec3(0, 1, 0)));
							lightProjection = glm::ortho(-max, max, -max, max, 0.0f, planeDistance * 2.0f);
							switch (enabledSize)
							{
							case 0:
								m_directionalLights[enabledSize].m_viewPort = glm::ivec4(0, 0, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
								break;
							case 1:
								m_directionalLights[enabledSize].m_viewPort = glm::ivec4(m_shadowMapResolution / 2, 0, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
								break;
							case 2:
								m_directionalLights[enabledSize].m_viewPort = glm::ivec4(0, m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
								break;
							case 3:
								m_directionalLights[enabledSize].m_viewPort = glm::ivec4(m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
								break;
							}

#pragma region Fix Shimmering due to the movement of the camera

							glm::mat4 shadowMatrix = lightProjection * lightView;
							glm::vec4 shadowOrigin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
							shadowOrigin = shadowMatrix * shadowOrigin;
							GLfloat storedW = shadowOrigin.w;
							shadowOrigin = shadowOrigin * (float)m_directionalLights[enabledSize].m_viewPort.z / 2.0f;
							glm::vec4 roundedOrigin = glm::round(shadowOrigin);
							glm::vec4 roundOffset = roundedOrigin - shadowOrigin;
							roundOffset = roundOffset * 2.0f / (float)m_directionalLights[enabledSize].m_viewPort.z;
							roundOffset.z = 0.0f;
							roundOffset.w = 0.0f;
							glm::mat4 shadowProj = lightProjection;
							shadowProj[3] += roundOffset;
							lightProjection = shadowProj;
#pragma endregion
							m_directionalLights[enabledSize].m_lightSpaceMatrix[split] = lightProjection * lightView;
							m_directionalLights[enabledSize].m_lightFrustumWidth[split] = max;
							m_directionalLights[enabledSize].m_lightFrustumDistance[split] = planeDistance;
							if (split == Default::ShaderIncludes::ShadowCascadeAmount - 1) m_directionalLights[enabledSize].m_reservedParameters = glm::vec4(dlc->m_lightSize, 0, dlc->m_bias, dlc->m_normalOffset);

						}
						enabledSize++;
					}
					m_directionalLightBlock->SubData(0, 4, &enabledSize);
					if (enabledSize != 0) {
						m_directionalLightBlock->SubData(16, enabledSize * sizeof(DirectionalLightInfo), &m_directionalLights[0]);
					}
					if (m_materialSettings.m_enableShadow) {
						m_directionalLightShadowMap->Bind();
						m_directionalLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
						glClear(GL_DEPTH_BUFFER_BIT);
						enabledSize = 0;
						m_directionalLightProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = directionalLightEntities->at(i);
							if (!lightEntity.IsEnabled()) continue;
							/*
							glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(),
								0, _DirectionalLights[enabledSize].viewPort.x, _DirectionalLights[enabledSize].viewPort.y,
								0, (GLsizei)_DirectionalLights[enabledSize].viewPort.z, (GLsizei)_DirectionalLights[enabledSize].viewPort.w, (GLsizei)4, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
							*/
							glViewport(m_directionalLights[enabledSize].m_viewPort.x, m_directionalLights[enabledSize].m_viewPort.y, m_directionalLights[enabledSize].m_viewPort.z, m_directionalLights[enabledSize].m_viewPort.w);
							m_directionalLightProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.IsEnabled()) continue;
									auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
									if (!mmc->IsEnabled() || !mmc->m_castShadow || mmc->m_material == nullptr || mmc->m_mesh == nullptr) continue;
									MaterialPropertySetter(mmc.get()->m_material.get(), true);
									auto mesh = mmc->m_mesh;
									auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
									m_directionalLightProgram->SetFloat4x4("model", ltw);
									mesh->Enable();
									mesh->VAO()->DisableAttributeArray(12);
									mesh->VAO()->DisableAttributeArray(13);
									mesh->VAO()->DisableAttributeArray(14);
									mesh->VAO()->DisableAttributeArray(15);
									glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);

								}
							}
							enabledSize++;
						}
						enabledSize = 0;
						m_directionalLightInstancedProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = directionalLightEntities->at(i);
							if (!lightEntity.IsEnabled()) continue;
							glViewport(m_directionalLights[enabledSize].m_viewPort.x, m_directionalLights[enabledSize].m_viewPort.y, m_directionalLights[enabledSize].m_viewPort.z, m_directionalLights[enabledSize].m_viewPort.w);
							m_directionalLightInstancedProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.IsEnabled()) continue;
									auto& immc = owner.GetPrivateComponent<Particles>();
									if (!immc->IsEnabled() || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
									MaterialPropertySetter(immc.get()->Material.get(), true);
									size_t count = immc->Matrices.size();
									std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
									matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
									auto mesh = immc->Mesh;
									m_directionalLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
									mesh->Enable();
									mesh->VAO()->EnableAttributeArray(12);
									mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
									mesh->VAO()->EnableAttributeArray(13);
									mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
									mesh->VAO()->EnableAttributeArray(14);
									mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
									mesh->VAO()->EnableAttributeArray(15);
									mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
									mesh->VAO()->SetAttributeDivisor(12, 1);
									mesh->VAO()->SetAttributeDivisor(13, 1);
									mesh->VAO()->SetAttributeDivisor(14, 1);
									mesh->VAO()->SetAttributeDivisor(15, 1);
									glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
									GLVAO::BindDefault();
								}
							}
							enabledSize++;
						}
					}
				}
				else
				{
					m_directionalLightBlock->SubData(0, 4, &size);
				}
				const std::vector<Entity>* pointLightEntities = EntityManager::GetPrivateComponentOwnersList<PointLight>();
				size = 0;
				if (pointLightEntities && !pointLightEntities->empty()) {
					size = pointLightEntities->size();
					size_t enabledSize = 0;
					for (int i = 0; i < size; i++) {
						Entity lightEntity = pointLightEntities->at(i);
						if (!lightEntity.IsEnabled()) continue;
						const auto& plc = lightEntity.GetPrivateComponent<PointLight>();
						if (!plc->IsEnabled()) continue;
						glm::vec3 position = EntityManager::GetComponentData<GlobalTransform>(lightEntity).Value[3];
						m_pointLights[enabledSize].position = glm::vec4(position, 0);
						m_pointLights[enabledSize].constantLinearQuadFarPlane.x = plc->constant;
						m_pointLights[enabledSize].constantLinearQuadFarPlane.y = plc->linear;
						m_pointLights[enabledSize].constantLinearQuadFarPlane.z = plc->quadratic;
						m_pointLights[enabledSize].diffuse = glm::vec4(plc->diffuse * plc->diffuseBrightness, plc->CastShadow);
						m_pointLights[enabledSize].specular = glm::vec4(0);
						m_pointLights[enabledSize].constantLinearQuadFarPlane.w = plc->farPlane;

						glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), m_pointLightShadowMap->GetResolutionRatio(), 1.0f, m_pointLights[enabledSize].constantLinearQuadFarPlane.w);
						m_pointLights[enabledSize].lightSpaceMatrix[0] = shadowProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						m_pointLights[enabledSize].lightSpaceMatrix[1] = shadowProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						m_pointLights[enabledSize].lightSpaceMatrix[2] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
						m_pointLights[enabledSize].lightSpaceMatrix[3] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
						m_pointLights[enabledSize].lightSpaceMatrix[4] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						m_pointLights[enabledSize].lightSpaceMatrix[5] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						m_pointLights[enabledSize].ReservedParameters = glm::vec4(plc->bias, plc->lightSize, 0, 0);

						switch (enabledSize)
						{
						case 0:
							m_pointLights[enabledSize].viewPort = glm::ivec4(0, 0, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						case 1:
							m_pointLights[enabledSize].viewPort = glm::ivec4(m_shadowMapResolution / 2, 0, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						case 2:
							m_pointLights[enabledSize].viewPort = glm::ivec4(0, m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						case 3:
							m_pointLights[enabledSize].viewPort = glm::ivec4(m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						}
						enabledSize++;
					}
					m_pointLightBlock->SubData(0, 4, &enabledSize);
					if (enabledSize != 0)m_pointLightBlock->SubData(16, enabledSize * sizeof(PointLightInfo), &m_pointLights[0]);
					if (m_materialSettings.m_enableShadow) {
#pragma region PointLight Shadowmap Pass
						m_pointLightShadowMap->Bind();
						m_pointLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
						glClear(GL_DEPTH_BUFFER_BIT);
						m_pointLightProgram->Bind();
						enabledSize = 0;
						for (int i = 0; i < size; i++) {
							Entity lightEntity = pointLightEntities->at(i);
							if (!lightEntity.IsEnabled()) continue;
							glViewport(m_pointLights[enabledSize].viewPort.x, m_pointLights[enabledSize].viewPort.y, m_pointLights[enabledSize].viewPort.z, m_pointLights[enabledSize].viewPort.w);
							m_pointLightProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.IsEnabled()) continue;
									auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
									if (!mmc->IsEnabled() || !mmc->m_castShadow || mmc->m_material == nullptr || mmc->m_mesh == nullptr) continue;
									MaterialPropertySetter(mmc.get()->m_material.get(), true);
									auto mesh = mmc->m_mesh;
									m_pointLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
									mesh->Enable();
									mesh->VAO()->DisableAttributeArray(12);
									mesh->VAO()->DisableAttributeArray(13);
									mesh->VAO()->DisableAttributeArray(14);
									mesh->VAO()->DisableAttributeArray(15);
									glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
								}
							}
							enabledSize++;
						}
						enabledSize = 0;
						m_pointLightInstancedProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = pointLightEntities->at(i);
							if (!lightEntity.IsEnabled()) continue;
							glViewport(m_pointLights[enabledSize].viewPort.x, m_pointLights[enabledSize].viewPort.y, m_pointLights[enabledSize].viewPort.z, m_pointLights[enabledSize].viewPort.w);
							m_pointLightInstancedProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.IsEnabled()) continue;
									auto& immc = owner.GetPrivateComponent<Particles>();
									if (!immc->IsEnabled() || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
									MaterialPropertySetter(immc.get()->Material.get(), true);
									size_t count = immc->Matrices.size();
									std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
									auto mesh = immc->Mesh;
									m_pointLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
									mesh->Enable();
									mesh->VAO()->EnableAttributeArray(12);
									mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
									mesh->VAO()->EnableAttributeArray(13);
									mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
									mesh->VAO()->EnableAttributeArray(14);
									mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
									mesh->VAO()->EnableAttributeArray(15);
									mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
									mesh->VAO()->SetAttributeDivisor(12, 1);
									mesh->VAO()->SetAttributeDivisor(13, 1);
									mesh->VAO()->SetAttributeDivisor(14, 1);
									mesh->VAO()->SetAttributeDivisor(15, 1);
									glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
									GLVAO::BindDefault();
								}
							}
							enabledSize++;
						}
#pragma endregion
					}
				}
				else
				{
					m_pointLightBlock->SubData(0, 4, &size);
				}
				const std::vector<Entity>* spotLightEntities = EntityManager::GetPrivateComponentOwnersList<SpotLight>();
				size = 0;
				if (spotLightEntities && !spotLightEntities->empty())
				{
					size = spotLightEntities->size();
					size_t enabledSize = 0;
					for (int i = 0; i < size; i++) {
						Entity lightEntity = spotLightEntities->at(i);
						if (!lightEntity.IsEnabled()) continue;
						const auto& slc = lightEntity.GetPrivateComponent<SpotLight>();
						if (!slc->IsEnabled()) continue;
						auto ltw = EntityManager::GetComponentData<GlobalTransform>(lightEntity);
						glm::vec3 position = ltw.Value[3];
						glm::vec3 front = ltw.GetRotation() * glm::vec3(0, 0, -1);
						glm::vec3 up = ltw.GetRotation() * glm::vec3(0, 1, 0);
						m_spotLights[enabledSize].position = glm::vec4(position, 0);
						m_spotLights[enabledSize].direction = glm::vec4(front, 0);
						m_spotLights[enabledSize].constantLinearQuadFarPlane.x = slc->constant;
						m_spotLights[enabledSize].constantLinearQuadFarPlane.y = slc->linear;
						m_spotLights[enabledSize].constantLinearQuadFarPlane.z = slc->quadratic;
						m_spotLights[enabledSize].constantLinearQuadFarPlane.w = slc->farPlane;
						m_spotLights[enabledSize].diffuse = glm::vec4(slc->diffuse * slc->diffuseBrightness, slc->CastShadow);
						m_spotLights[enabledSize].specular = glm::vec4(0);

						glm::mat4 shadowProj = glm::perspective(glm::radians(slc->outerDegrees * 2.0f), m_spotLightShadowMap->GetResolutionRatio(), 1.0f, m_spotLights[enabledSize].constantLinearQuadFarPlane.w);
						m_spotLights[enabledSize].lightSpaceMatrix = shadowProj * glm::lookAt(position, position + front, up);
						m_spotLights[enabledSize].cutOffOuterCutOffLightSizeBias = glm::vec4(glm::cos(glm::radians(slc->innerDegrees)), glm::cos(glm::radians(slc->outerDegrees)), slc->lightSize, slc->bias);

						switch (enabledSize)
						{
						case 0:
							m_spotLights[enabledSize].viewPort = glm::ivec4(0, 0, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						case 1:
							m_spotLights[enabledSize].viewPort = glm::ivec4(m_shadowMapResolution / 2, 0, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						case 2:
							m_spotLights[enabledSize].viewPort = glm::ivec4(0, m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						case 3:
							m_spotLights[enabledSize].viewPort = glm::ivec4(m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2, m_shadowMapResolution / 2);
							break;
						}
						enabledSize++;
					}
					m_spotLightBlock->SubData(0, 4, &enabledSize);
					if (enabledSize != 0)m_spotLightBlock->SubData(16, enabledSize * sizeof(SpotLightInfo), &m_spotLights[0]);
					if (m_materialSettings.m_enableShadow) {
#pragma region SpotLight Shadowmap Pass
						m_spotLightShadowMap->Bind();
						m_spotLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
						glClear(GL_DEPTH_BUFFER_BIT);
						m_spotLightProgram->Bind();
						enabledSize = 0;
						for (int i = 0; i < size; i++) {
							Entity lightEntity = spotLightEntities->at(i);
							if (!lightEntity.IsEnabled()) continue;
							glViewport(m_spotLights[enabledSize].viewPort.x, m_spotLights[enabledSize].viewPort.y, m_spotLights[enabledSize].viewPort.z, m_spotLights[enabledSize].viewPort.w);
							m_spotLightProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.IsEnabled()) continue;
									auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
									if (!mmc->IsEnabled() || !mmc->m_castShadow || mmc->m_material == nullptr || mmc->m_mesh == nullptr) continue;
									MaterialPropertySetter(mmc.get()->m_material.get(), true);
									auto mesh = mmc->m_mesh;
									m_spotLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
									mesh->Enable();
									mesh->VAO()->DisableAttributeArray(12);
									mesh->VAO()->DisableAttributeArray(13);
									mesh->VAO()->DisableAttributeArray(14);
									mesh->VAO()->DisableAttributeArray(15);
									glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
								}
							}
							enabledSize++;
						}
						enabledSize = 0;
						m_spotLightInstancedProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = spotLightEntities->at(i);
							if (!lightEntity.IsEnabled()) continue;
							glViewport(m_spotLights[enabledSize].viewPort.x, m_spotLights[enabledSize].viewPort.y, m_spotLights[enabledSize].viewPort.z, m_spotLights[enabledSize].viewPort.w);
							m_spotLightInstancedProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.IsEnabled()) continue;
									auto& immc = owner.GetPrivateComponent<Particles>();
									if (!immc->IsEnabled() || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
									MaterialPropertySetter(immc.get()->Material.get(), true);
									size_t count = immc->Matrices.size();
									std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
									auto mesh = immc->Mesh;
									m_spotLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
									mesh->Enable();
									mesh->VAO()->EnableAttributeArray(12);
									mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
									mesh->VAO()->EnableAttributeArray(13);
									mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
									mesh->VAO()->EnableAttributeArray(14);
									mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
									mesh->VAO()->EnableAttributeArray(15);
									mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
									mesh->VAO()->SetAttributeDivisor(12, 1);
									mesh->VAO()->SetAttributeDivisor(13, 1);
									mesh->VAO()->SetAttributeDivisor(14, 1);
									mesh->VAO()->SetAttributeDivisor(15, 1);
									glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
									GLVAO::BindDefault();
								}
							}
							enabledSize++;
						}
#pragma endregion
					}
				}
				else
				{
					m_spotLightBlock->SubData(0, 4, &size);
				}
			}
#pragma endregion
		}
	}
#pragma region Render to other cameras
	if (cameraEntities != nullptr)
	{
		for (auto cameraEntity : *cameraEntities) {
			if (!cameraEntity.IsEnabled()) continue;
			auto& cameraComponent = cameraEntity.GetPrivateComponent<CameraComponent>();
			if (_MainCameraComponent && cameraComponent.get() == _MainCameraComponent) continue;
			if (cameraComponent->IsEnabled())
			{
				auto ltw = cameraEntity.GetComponentData<GlobalTransform>();
				CameraComponent::m_cameraInfoBlock.UpdateMatrices(cameraComponent.get(),
					ltw.GetPosition(),
					ltw.GetRotation()
				);
				CameraComponent::m_cameraInfoBlock.UploadMatrices(cameraComponent.get());
				const auto cameraTransform = cameraEntity.GetComponentData<GlobalTransform>();				
				RenderToCameraDeferred(cameraComponent, cameraTransform, minBound, maxBound, false);
				RenderBackGround(cameraComponent);
				RenderToCameraForward(cameraComponent, cameraTransform, minBound, maxBound, false);
			}
		}
	}
#pragma endregion
#pragma region Render to scene camera
	if (EditorManager::GetInstance().m_enabled && EditorManager::GetInstance().m_sceneCamera->IsEnabled()) {
		CameraComponent::m_cameraInfoBlock.UpdateMatrices(EditorManager::GetInstance().m_sceneCamera.get(),
			EditorManager::GetInstance().m_sceneCameraPosition,
			EditorManager::GetInstance().m_sceneCameraRotation
		);
		CameraComponent::m_cameraInfoBlock.UploadMatrices(EditorManager::GetInstance().m_sceneCamera.get());
		GlobalTransform cameraTransform;
		cameraTransform.Value = glm::translate(EditorManager::GetInstance().m_sceneCameraPosition) * glm::mat4_cast(EditorManager::GetInstance().m_sceneCameraRotation);

#pragma region For entity selection
		EditorManager::GetInstance().m_sceneCameraEntityRecorder->Bind();
		const std::vector<Entity>* mmcowners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
		const std::vector<Entity>* immcowners = EntityManager::GetPrivateComponentOwnersList<Particles>();
		if (mmcowners) {
			
			EditorManager::GetInstance().m_sceneCameraEntityRecorderProgram->Bind();
			for (auto owner : *mmcowners) {
				if (!owner.IsEnabled()) continue;
				auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
				if (!mmc->IsEnabled() || mmc->m_material == nullptr || mmc->m_mesh == nullptr) continue;
				if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).m_value & static_cast<size_t>(CameraLayer::MainCamera))) continue;
				auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
				auto* mesh = mmc->m_mesh.get();
				mesh->Enable();
				mesh->VAO()->DisableAttributeArray(12);
				mesh->VAO()->DisableAttributeArray(13);
				mesh->VAO()->DisableAttributeArray(14);
				mesh->VAO()->DisableAttributeArray(15);
				EditorManager::GetInstance().m_sceneCameraEntityRecorderProgram->SetInt("EntityIndex", owner.m_index);
				EditorManager::GetInstance().m_sceneCameraEntityRecorderProgram->SetFloat4x4("model", ltw);
				glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
			}
			GLVAO::BindDefault();
		}
		if (immcowners) {
			EditorManager::GetInstance().m_sceneCameraEntityInstancedRecorderProgram->Bind();
			for (auto owner : *immcowners) {
				if (!owner.IsEnabled()) continue;
				auto& immc = owner.GetPrivateComponent<Particles>();
				if (!immc->IsEnabled() || immc->Material == nullptr || immc->Mesh == nullptr) continue;
				if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).m_value & static_cast<size_t>(CameraLayer::MainCamera))) continue;
				auto count = immc->Matrices.size();
				std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
				matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
				auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
				auto* mesh = immc->Mesh.get();
				mesh->Enable();
				mesh->VAO()->EnableAttributeArray(12);
				mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
				mesh->VAO()->EnableAttributeArray(13);
				mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
				mesh->VAO()->EnableAttributeArray(14);
				mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
				mesh->VAO()->EnableAttributeArray(15);
				mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
				mesh->VAO()->SetAttributeDivisor(12, 1);
				mesh->VAO()->SetAttributeDivisor(13, 1);
				mesh->VAO()->SetAttributeDivisor(14, 1);
				mesh->VAO()->SetAttributeDivisor(15, 1);
				EditorManager::GetInstance().m_sceneCameraEntityInstancedRecorderProgram->SetInt("EntityIndex", owner.m_index);
				EditorManager::GetInstance().m_sceneCameraEntityInstancedRecorderProgram->SetFloat4x4("model", ltw);
				glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
			}
		}
#pragma endregion
		RenderToCameraDeferred(EditorManager::GetInstance().m_sceneCamera, cameraTransform, minBound, maxBound, false);
		RenderBackGround(EditorManager::GetInstance().m_sceneCamera);
		RenderToCameraForward(EditorManager::GetInstance().m_sceneCamera, cameraTransform, minBound, maxBound, false);
	}
#pragma endregion

#pragma region Render to main Camera and calculate bounds.
	if (_MainCameraComponent != nullptr) {
		auto mainCameraEntity = _MainCameraComponent->GetOwner();
		if (mainCameraEntity.IsEnabled()) {
			auto& mainCamera = _MainCameraComponent;
			if (_MainCameraComponent->IsEnabled()) {
				auto minBound = glm::vec3((int)INT_MAX);
				auto maxBound = glm::vec3((int)INT_MIN);
				auto ltw = mainCameraEntity.GetComponentData<GlobalTransform>();
				CameraComponent::m_cameraInfoBlock.UpdateMatrices(mainCamera,
					ltw.GetPosition(),
					ltw.GetRotation()
				);
				CameraComponent::m_cameraInfoBlock.UploadMatrices(mainCamera);
				GlobalTransform cameraTransform = mainCameraEntity.GetComponentData<GlobalTransform>();
				auto& mainCameraComponent = mainCameraEntity.GetPrivateComponent<CameraComponent>();
				RenderToCameraDeferred(mainCameraComponent, cameraTransform, minBound, maxBound, true);
				RenderBackGround(mainCameraComponent);
				RenderToCameraForward(mainCameraComponent, cameraTransform, minBound, maxBound, true);
				worldBound.m_max = maxBound;
				worldBound.m_min = minBound;
				Application::GetCurrentWorld()->SetBound(worldBound);
			}
		}
	}
#pragma endregion
}

inline float RenderManager::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
#pragma region Settings

#pragma endregion
#pragma region Shadow

void UniEngine::RenderManager::SetSplitRatio(float r1, float r2, float r3, float r4)
{
	m_shadowCascadeSplit[0] = r1;
	m_shadowCascadeSplit[1] = r2;
	m_shadowCascadeSplit[2] = r3;
	m_shadowCascadeSplit[3] = r4;
}

void UniEngine::RenderManager::SetShadowMapResolution(size_t value)
{
	m_shadowMapResolution = value;
	if (m_directionalLightShadowMap != nullptr)m_directionalLightShadowMap->SetResolution(value);
}

void UniEngine::RenderManager::SetPcfSampleAmount(int value)
{
	m_lightSettings.m_pcfSampleAmount = glm::clamp(value, 0, 16);
}


void UniEngine::RenderManager::SetBlockerSearchAmount(int value)
{
	m_lightSettings.m_blockerSearchAmount = glm::clamp(value, 0, 16);
}
void UniEngine::RenderManager::SetSeamFixRatio(float value)
{
	m_lightSettings.m_seamFixRatio = value;
}

void UniEngine::RenderManager::SetMaxShadowDistance(float value)
{
	m_maxShadowDistance = value;
}

void UniEngine::RenderManager::SetVsmMaxVariance(float value)
{
	m_lightSettings.m_vsmMaxVariance = value;
}

void UniEngine::RenderManager::SetLightBleedControlFactor(float value)
{
	m_lightSettings.m_lightBleedFactor = value;
}

void UniEngine::RenderManager::SetScaleFactor(float value)
{
	m_lightSettings.m_scaleFactor = value;
}

void UniEngine::RenderManager::SetEvsmExponent(float value)
{
	m_lightSettings.m_evsmExponent = value;
}

void UniEngine::RenderManager::SetAmbientLight(float value)
{
	m_lightSettings.m_ambientLight = value;
}

void RenderManager::SetEnableShadow(bool value)
{
	m_materialSettings.m_enableShadow = value;
}

glm::vec3 UniEngine::RenderManager::ClosestPointOnLine(glm::vec3 point, glm::vec3 a, glm::vec3 b)
{
	float LineLength = distance(a, b);
	glm::vec3 Vector = point - a;
	glm::vec3 LineDirection = (b - a) / LineLength;

	// Project Vector to LineDirection to get the distance of point from a
	float Distance = dot(Vector, LineDirection);
	return a + LineDirection * Distance;
}

void RenderManager::LateUpdate()
{
	const std::vector<Entity>* postProcessingEntities = EntityManager::GetPrivateComponentOwnersList<PostProcessing>();
	if (postProcessingEntities != nullptr)
	{
		for (auto postProcessingEntity : *postProcessingEntities) {
			if (!postProcessingEntity.IsEnabled()) continue;
			auto& postProcessing = postProcessingEntity.GetPrivateComponent<PostProcessing>();
			if(postProcessing->IsEnabled()) postProcessing->Process();
		}
	}
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::BeginMenu("Rendering"))
			{
				ImGui::Checkbox("Lighting Manager", &m_enableLightMenu);
				ImGui::Checkbox("Render Manager", &m_enableRenderMenu);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (m_enableLightMenu)
	{
		ImGui::Begin("Light Manager");
		if (ImGui::TreeNode("Environment Lighting")) {
			ImGui::DragFloat("Brightness", &m_lightSettings.m_ambientLight, 0.01f, 0.0f, 2.0f);
			ImGui::TreePop();
		}
		bool enableShadow = m_materialSettings.m_enableShadow;
		if(ImGui::Checkbox("Enable shadow", &enableShadow))
		{
			m_materialSettings.m_enableShadow = enableShadow;
		}
		if (m_materialSettings.m_enableShadow && ImGui::TreeNode("Shadow")) {
			if (ImGui::TreeNode("Distance"))
			{
				ImGui::DragFloat("Max shadow distance", &m_maxShadowDistance, 1.0f, 0.1f);
				ImGui::DragFloat("Split 1", &m_shadowCascadeSplit[0], 0.01f, 0.0f, m_shadowCascadeSplit[1]);
				ImGui::DragFloat("Split 2", &m_shadowCascadeSplit[1], 0.01f, m_shadowCascadeSplit[0], m_shadowCascadeSplit[2]);
				ImGui::DragFloat("Split 3", &m_shadowCascadeSplit[2], 0.01f, m_shadowCascadeSplit[1], m_shadowCascadeSplit[3]);
				ImGui::DragFloat("Split 4", &m_shadowCascadeSplit[3], 0.01f, m_shadowCascadeSplit[2], 1.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("PCSS")) {
				ImGui::DragFloat("PCSS Factor", &m_lightSettings.m_scaleFactor, 0.01f, 0.0f);
				ImGui::DragInt("Blocker search side amount", &m_lightSettings.m_blockerSearchAmount, 1, 1, 8);
				ImGui::DragInt("PCF Sample Size", &m_lightSettings.m_pcfSampleAmount, 1, 1, 64);
				ImGui::TreePop();
			}
			ImGui::DragFloat("Seam fix ratio", &m_lightSettings.m_seamFixRatio, 0.001f, 0.0f, 0.1f);
			ImGui::Checkbox("Stable fit", &m_stableFit);
			ImGui::TreePop();
		}
		ImGui::End();
	}
	if (m_enableRenderMenu)
	{
		ImGui::Begin("Render Manager");
		ImGui::Checkbox("Display info", &m_enableInfoWindow);
		ImGui::End();
	}

	ImVec2 viewPortSize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

	ImGui::Begin("Camera");
	{
		static int corner = 1;
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			viewPortSize = ImGui::GetWindowSize();
			// Get the size of the child (i.e. the whole draw size of the windows).
			ImVec2 overlayPos = ImGui::GetWindowPos();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			bool cameraActive = false;
			if (_MainCameraComponent != nullptr) {
				auto entity = _MainCameraComponent->GetOwner();
				if (entity.IsEnabled() && _MainCameraComponent->IsEnabled())
				{
					auto id = _MainCameraComponent->GetTexture()->Texture()->Id();
					ImGui::Image((ImTextureID)id, viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
					cameraActive = true;
				}
			}
			if(!cameraActive){
				ImGui::Text("No active main camera!");
			}

			ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
			if (m_enableInfoWindow)
			{
				ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
				ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
				ImGui::SetNextWindowBgAlpha(0.35f);
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

				ImGui::BeginChild("Render Info", ImVec2(200, 100), false, window_flags);
				ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
				std::string trisstr = "";
				if (m_triangles < 999) trisstr += std::to_string(m_triangles);
				else if (m_triangles < 999999) trisstr += std::to_string((int)(m_triangles / 1000)) + "K";
				else trisstr += std::to_string((int)(m_triangles / 1000000)) + "M";
				trisstr += " tris";
				ImGui::Text(trisstr.c_str());
				ImGui::Text("%d drawcall", m_drawCall);
				ImGui::Separator();
				if (ImGui::IsMousePosValid()) {
					glm::vec2 pos;
					InputManager::GetMousePositionInternal(ImGui::GetCurrentWindowRead(), pos);
					ImGui::Text("Mouse Position: (%.1f,%.1f)", pos.x, pos.y);
				}
				else {
					ImGui::Text("Mouse Position: <invalid>");
				}
				ImGui::EndChild();
			}

		}
		ImGui::EndChild();

	}
	ImGui::End();
	ImGui::PopStyleVar();
	m_mainCameraResolutionX = viewPortSize.x;
	m_mainCameraResolutionY = viewPortSize.y;
}

#pragma endregion
#pragma region RenderAPI
#pragma region Internal


void RenderManager::MaterialPropertySetter(Material* material, bool disableBlending)
{
	switch (material->PolygonMode)
	{
	case MaterialPolygonMode::FILL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case MaterialPolygonMode::LINE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case MaterialPolygonMode::POINT:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}

	switch (material->CullingMode)
	{
	case MaterialCullingMode::OFF:
		glDisable(GL_CULL_FACE);
		break;
	case MaterialCullingMode::FRONT:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case MaterialCullingMode::BACK:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	}
	if (disableBlending) glDisable(GL_BLEND);
	else {
		switch (material->BlendingMode)
		{
		case MaterialBlendingMode::OFF:
			break;
		case MaterialBlendingMode::ONE_MINUS_SRC_ALPHA:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		}
	}
	glEnable(GL_DEPTH_TEST);
}

void RenderManager::ApplyMaterialSettings(Material* material, GLProgram* program)
{
	m_materialSettings = MaterialSettingsBlock();
	
	m_materialSettings.m_alphaDiscardEnabled = material->AlphaDiscardEnabled;
	m_materialSettings.m_alphaDiscardOffset = material->AlphaDiscardOffset;
	m_materialSettings.m_displacementScale = material->DisplacementMapScale;
	m_materialSettings.m_albedoColorVal = glm::vec4(material->AlbedoColor, 1.0f);
	m_materialSettings.m_shininessVal = material->Shininess;
	m_materialSettings.m_metallicVal = material->Metallic;
	m_materialSettings.m_roughnessVal = material->Roughness;
	m_materialSettings.m_aoVal = material->AmbientOcclusion;
	
	m_materialSettings.m_directionalShadowMap = m_directionalLightShadowMap->DepthMapArray()->GetHandle();
	m_materialSettings.m_pointShadowMap = m_pointLightShadowMap->DepthMapArray()->GetHandle();
	m_materialSettings.m_spotShadowMap = m_spotLightShadowMap->DepthMap()->GetHandle();
	
	for(const auto& i : material->_Textures)
	{
		if (!i.second || !i.second->Texture()) continue;
		switch (i.second->_Type)
		{
		case TextureType::ALBEDO:
			m_materialSettings.m_albedoMap = i.second->Texture()->GetHandle();
			m_materialSettings.m_albedoEnabled = static_cast<int>(true);
			break;
		case TextureType::NORMAL:
			m_materialSettings.m_normalMap = i.second->Texture()->GetHandle();
			m_materialSettings.m_normalEnabled = static_cast<int>(true);
			break;
		case TextureType::METALLIC:
			m_materialSettings.m_metallicMap = i.second->Texture()->GetHandle();
			m_materialSettings.m_metallicEnabled = static_cast<int>(true);
			break;
		case TextureType::ROUGHNESS:
			m_materialSettings.m_roughnessMap = i.second->Texture()->GetHandle();
			m_materialSettings.m_roughnessEnabled = static_cast<int>(true);
			break;
		case TextureType::AO:
			m_materialSettings.m_aoMap = i.second->Texture()->GetHandle();
			m_materialSettings.m_aoEnabled = static_cast<int>(true);
			break;
		case TextureType::AMBIENT:
			m_materialSettings.m_ambient = i.second->Texture()->GetHandle();
			m_materialSettings.m_ambientEnabled = static_cast<int>(true);
			break;
		case TextureType::DIFFUSE:
			m_materialSettings.m_diffuse = i.second->Texture()->GetHandle();
			m_materialSettings.m_diffuseEnabled = static_cast<int>(true);
			break;
		case TextureType::SPECULAR:
			m_materialSettings.m_specular = i.second->Texture()->GetHandle();
			m_materialSettings.m_specularEnabled = static_cast<int>(true);
			break;
		case TextureType::EMISSIVE:
			m_materialSettings.m_emissive = i.second->Texture()->GetHandle();
			m_materialSettings.m_emissiveEnabled = static_cast<int>(true);
			break;
		case TextureType::DISPLACEMENT:
			m_materialSettings.m_displacement = i.second->Texture()->GetHandle();
			m_materialSettings.m_displacementEnabled = static_cast<int>(true);
			break;
		}
	}
	m_materialSettingsBuffer->SubData(0, sizeof(MaterialSettingsBlock), &m_materialSettings);
}

void RenderManager::DeferredPrepass(Mesh* mesh, Material* material, glm::mat4 model)
{
	if (mesh == nullptr || material == nullptr) return;
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	m_drawCall++;
	m_triangles += mesh->Size() / 3;
	auto& program = m_gBufferPrepass;
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	MaterialPropertySetter(material, true);
	ApplyMaterialSettings(material, program.get());
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	GLVAO::BindDefault();
}

void RenderManager::DeferredPrepassInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices,
	size_t count)
{
	if (mesh == nullptr || material == nullptr || matrices == nullptr || count == 0) return;
	std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
	matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->Enable();
	mesh->VAO()->EnableAttributeArray(12);
	mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	mesh->VAO()->EnableAttributeArray(13);
	mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(14);
	mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(15);
	mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	mesh->VAO()->SetAttributeDivisor(12, 1);
	mesh->VAO()->SetAttributeDivisor(13, 1);
	mesh->VAO()->SetAttributeDivisor(14, 1);
	mesh->VAO()->SetAttributeDivisor(15, 1);

	m_drawCall++;
	m_triangles += mesh->Size() * count / 3;
	auto& program = m_gBufferInstancedPrepass;
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	MaterialPropertySetter(material, true);
	ApplyMaterialSettings(material, program.get());
	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 model, const glm::mat4* matrices, size_t count, bool receiveShadow)
{
	if (mesh == nullptr || material == nullptr || matrices == nullptr || count == 0) return;
	std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
	matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->Enable();
	mesh->VAO()->EnableAttributeArray(12);
	mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	mesh->VAO()->EnableAttributeArray(13);
	mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(14);
	mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(15);
	mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	mesh->VAO()->SetAttributeDivisor(12, 1);
	mesh->VAO()->SetAttributeDivisor(13, 1);
	mesh->VAO()->SetAttributeDivisor(14, 1);
	mesh->VAO()->SetAttributeDivisor(15, 1);
	m_drawCall++;
	m_triangles += mesh->Size() * count / 3;
	auto program = material->_Program.get();
	if (program == nullptr) program = Default::GLPrograms::StandardInstancedProgram.get();
	program->Bind();
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	m_materialSettings.m_receiveShadow = receiveShadow;
	MaterialPropertySetter(material);
	ApplyMaterialSettings(material, program);
	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 model, bool receiveShadow)
{
	if (mesh == nullptr || material == nullptr) return;
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);
	m_drawCall++;
	m_triangles += mesh->Size() / 3;
	auto program = material->_Program.get();
	if (program == nullptr) program = Default::GLPrograms::StandardProgram.get();
	program->Bind();
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	m_materialSettings.m_receiveShadow = receiveShadow;
	MaterialPropertySetter(material);
	ApplyMaterialSettings(material, program);
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size)
{
	auto program = Default::GLPrograms::ScreenProgram;
	program->Bind();
	Default::GLPrograms::ScreenVAO->Bind();
	texture->Bind(0);
	program->SetInt("screenTexture", 0);
	program->SetFloat("depth", depth);
	program->SetFloat2("center", center);
	program->SetFloat2("size", size);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UniEngine::RenderManager::DrawGizmoInstanced(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4* matrices, size_t count, glm::mat4 scaleMatrix)
{
	if (mesh == nullptr || matrices == nullptr || count == 0) return;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
	matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->Enable();
	mesh->VAO()->EnableAttributeArray(12);
	mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	mesh->VAO()->EnableAttributeArray(13);
	mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(14);
	mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(15);
	mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	mesh->VAO()->SetAttributeDivisor(12, 1);
	mesh->VAO()->SetAttributeDivisor(13, 1);
	mesh->VAO()->SetAttributeDivisor(14, 1);
	mesh->VAO()->SetAttributeDivisor(15, 1);

	Default::GLPrograms::GizmoInstancedProgram->Bind();
	Default::GLPrograms::GizmoInstancedProgram->SetFloat4("surfaceColor", color);
	Default::GLPrograms::GizmoInstancedProgram->SetFloat4x4("model", model);
	Default::GLPrograms::GizmoInstancedProgram->SetFloat4x4("scaleMatrix", scaleMatrix);
	m_drawCall++;
	m_triangles += mesh->Size() * count / 3;
	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4 scaleMatrix)
{
	if (mesh == nullptr) return;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	Default::GLPrograms::GizmoProgram->Bind();
	Default::GLPrograms::GizmoProgram->SetFloat4("surfaceColor", color);
	Default::GLPrograms::GizmoProgram->SetFloat4x4("model", model);
	Default::GLPrograms::GizmoProgram->SetFloat4x4("scaleMatrix", scaleMatrix);

	m_drawCall++;
	m_triangles += mesh->Size() / 3;
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	GLVAO::BindDefault();
}
#pragma endregion

#pragma region External
void UniEngine::RenderManager::DrawGizmoMeshInstanced(Mesh* mesh, glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmoInstanced(mesh, color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void RenderManager::DrawGizmoRay(glm::vec4 color, glm::vec3 start, glm::vec3 end, float width)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	glm::quat rotation = glm::quatLookAt(end - start, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	glm::mat4 rotationMat = glm::mat4_cast(rotation);
	auto model = glm::translate((start + end) / 2.0f) * rotationMat * glm::scale(glm::vec3(width, glm::distance(end, start) / 2.0f, width));
	DrawGizmoMesh(Default::Primitives::Cylinder.get(), color, model);
}

void RenderManager::DrawGizmoRays(glm::vec4 color, std::vector<std::pair<glm::vec3, glm::vec3>> connections,
	float width)
{
	if (connections.empty()) return;
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	std::vector<glm::mat4> models;
	models.resize(connections.size());
	for(int i = 0; i < connections.size(); i++)
	{
		auto start = connections[i].first;
		auto& end = connections[i].second;
		glm::quat rotation = glm::quatLookAt(end - start, glm::vec3(0.0f, 1.0f, 0.0f));
		rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
		glm::mat4 rotationMat = glm::mat4_cast(rotation);
		auto model = glm::translate((start + end) / 2.0f) * rotationMat * glm::scale(glm::vec3(width, glm::distance(end, start) / 2.0f, width));
		models[i] = model;
	}
	
	DrawGizmoMeshInstanced(Default::Primitives::Cylinder.get(), color, models.data(), connections.size()); 
}

void RenderManager::DrawGizmoRays(glm::vec4 color, std::vector<Ray>& rays, float width)
{
	if(rays.empty()) return;
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	std::vector<glm::mat4> models;
	models.resize(rays.size());
	for (int i = 0; i < rays.size(); i++)
	{
		auto& ray = rays[i];
		glm::quat rotation = glm::quatLookAt(ray.Direction, glm::vec3(0.0f, 1.0f, 0.0f));
		rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
		const glm::mat4 rotationMat = glm::mat4_cast(rotation);
		auto model = glm::translate((ray.Start + ray.Direction * ray.Length / 2.0f)) * rotationMat * glm::scale(glm::vec3(width, ray.Length / 2.0f, width));
		models[i] = model;
	}
	DrawGizmoMeshInstanced(Default::Primitives::Cylinder.get(), color, models.data(), rays.size());
}

void RenderManager::DrawGizmoRay(glm::vec4 color, Ray& ray, float width)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	glm::quat rotation = glm::quatLookAt(ray.Direction, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	const glm::mat4 rotationMat = glm::mat4_cast(rotation);
	auto model = glm::translate((ray.Start + ray.Direction * ray.Length / 2.0f)) * rotationMat * glm::scale(glm::vec3(width, ray.Length / 2.0f, width));
	DrawGizmoMesh(Default::Primitives::Cylinder.get(), color, model);
}

void RenderManager::DrawMesh(Mesh* mesh, Material* material, glm::mat4 model,
	CameraComponent* cameraComponent, bool receiveShadow)
{
	{
		auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
		if (cameraComponent == sceneCamera.get()) return;
		if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
		CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
			EditorManager::GetInstance().m_sceneCameraPosition,
			EditorManager::GetInstance().m_sceneCameraRotation
		);
		CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
		sceneCamera->Bind();
		DrawMesh(mesh, material, model, receiveShadow);
	}
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	const auto entity = cameraComponent->GetOwner();
	if (!entity.IsEnabled()) return;
	const auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
	glm::vec3 scale;
	glm::vec3 trans;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ltw.Value, scale, rotation, trans, skew, perspective);
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(cameraComponent,
		trans,
		rotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(cameraComponent);
	cameraComponent->Bind();
	DrawMesh(mesh, material, model, receiveShadow);
}

void RenderManager::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices,
	size_t count, CameraComponent* cameraComponent, bool receiveShadow)
{
	{
		auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
		if (cameraComponent == sceneCamera.get()) return;
		if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
		CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
			EditorManager::GetInstance().m_sceneCameraPosition,
			EditorManager::GetInstance().m_sceneCameraRotation
		);
		DrawMeshInstanced(mesh, material, model, matrices, count, receiveShadow);
	}
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	const auto entity = cameraComponent->GetOwner();
	if (!entity.IsEnabled()) return;
	const auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
	glm::vec3 scale;
	glm::vec3 trans;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ltw.Value, scale, rotation, trans, skew, perspective);
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(cameraComponent,
		trans,
		rotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(cameraComponent);
	cameraComponent->Bind();
	DrawMeshInstanced(mesh, material, model, matrices, count, receiveShadow);
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 model, RenderTarget* target, bool receiveShadow)
{
	target->Bind();
	DrawMesh(mesh, material, model, receiveShadow);
}

#pragma region DrawTexture
void UniEngine::RenderManager::DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target)
{
	target->Bind();
	DrawTexture2D(texture, depth, center, size);
}

void RenderManager::DrawTexture2D(Texture2D* texture, float depth, glm::vec2 center, glm::vec2 size, CameraComponent* cameraComponent)
{
	{
		auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
		if (cameraComponent == sceneCamera.get()) return;
		if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
		CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
			EditorManager::GetInstance().m_sceneCameraPosition,
			EditorManager::GetInstance().m_sceneCameraRotation
		);
		DrawTexture2D(texture->Texture().get(), depth, center, size);
	}
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	const auto entity = cameraComponent->GetOwner();
	if (!entity.IsEnabled()) return;
	cameraComponent->Bind();
	DrawTexture2D(texture->Texture().get(), depth, center, size);
}
void RenderManager::SetMainCamera(CameraComponent* value)
{
	if (_MainCameraComponent)
	{
		_MainCameraComponent->m_isMainCamera = false;
	}
	_MainCameraComponent = value;
	if (_MainCameraComponent) _MainCameraComponent->m_isMainCamera = true;
}

CameraComponent* RenderManager::GetMainCamera()
{
	return _MainCameraComponent;
}

void UniEngine::RenderManager::DrawTexture2D(Texture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target)
{
	target->Bind();
	DrawTexture2D(texture->Texture().get(), depth, center, size);
}
#pragma endregion
#pragma region Gizmo
void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, RenderTarget* target, bool receiveShadow)
{
	target->Bind();
	DrawMeshInstanced(mesh, material, model, matrices, count, receiveShadow);
}

void UniEngine::RenderManager::DrawGizmoPoint(glm::vec4 color, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmo(Default::Primitives::Sphere.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmoInstanced(Default::Primitives::Sphere.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCube(glm::vec4 color, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmo(Default::Primitives::Cube.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmoInstanced(Default::Primitives::Cube.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuad(glm::vec4 color, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmo(Default::Primitives::Quad.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmoInstanced(Default::Primitives::Quad.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoMesh(Mesh* mesh, glm::vec4 color, glm::mat4 model, float size)
{
	auto& sceneCamera = EditorManager::GetInstance().m_sceneCamera;
	if (!EditorManager::GetInstance().m_enabled || !sceneCamera->IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(sceneCamera.get(),
		EditorManager::GetInstance().m_sceneCameraPosition,
		EditorManager::GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(sceneCamera.get());
	sceneCamera->Bind();
	DrawGizmo(mesh, color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}
#pragma endregion
#pragma endregion

#pragma region Status


size_t UniEngine::RenderManager::Triangles()
{
	return m_triangles;
}

size_t UniEngine::RenderManager::DrawCall()
{
	return m_drawCall;
}

#pragma endregion
#pragma endregion





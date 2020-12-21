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
bool RenderManager::_EnableRenderMenu = false;
bool RenderManager::_EnableInfoWindow = true;
#pragma region Shadow
#pragma region DirectionalMap
GLUBO* RenderManager::_ShadowCascadeInfoBlock;
LightSettingsBlock RenderManager::_LightSettings;
float RenderManager::_ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = { 0.15f, 0.3f, 0.5f, 1.0f };
float RenderManager::_MaxShadowDistance = 500;
bool RenderManager::_StableFit = true;
#pragma endregion
size_t RenderManager::_ShadowMapResolution = 4096;
bool RenderManager::_EnableLightMenu = true;
GLUBO* RenderManager::_PointLightBlock;
GLUBO* RenderManager::_SpotLightBlock;
GLUBO* RenderManager::_DirectionalLightBlock;
DirectionalLightInfo RenderManager::_DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
PointLightInfo RenderManager::_PointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLightInfo RenderManager::_SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

std::unique_ptr<DirectionalLightShadowMap> RenderManager::_DirectionalLightShadowMap;
std::unique_ptr<PointLightShadowMap> RenderManager::_PointLightShadowMap;
std::unique_ptr<SpotLightShadowMap> RenderManager::_SpotLightShadowMap;
std::unique_ptr<GLProgram> RenderManager::_DirectionalLightProgram;
std::unique_ptr<GLProgram> RenderManager::_DirectionalLightInstancedProgram;
std::unique_ptr<GLProgram> RenderManager::_PointLightProgram;
std::unique_ptr<GLProgram> RenderManager::_PointLightInstancedProgram;
std::unique_ptr<GLProgram> RenderManager::_SpotLightProgram;
std::unique_ptr<GLProgram> RenderManager::_SpotLightInstancedProgram;

#pragma endregion
#pragma region Render
MaterialSettingsBlock RenderManager::_MaterialSettingsBlock;
std::unique_ptr<GLUBO> RenderManager::_MaterialSettingsBuffer;
CameraComponent* RenderManager::_MainCameraComponent;
int RenderManager::_MainCameraResolutionX = 1;
int RenderManager::_MainCameraResolutionY = 1;
EntityQuery RenderManager::_DirectionalLightQuery;
EntityQuery RenderManager::_PointLightQuery;
EntityQuery RenderManager::_SpotLightQuery;
size_t RenderManager::_DrawCall;
size_t RenderManager::_Triangles;
std::unique_ptr<GLUBO> RenderManager::_KernelBlock;
std::unique_ptr<GLProgram> RenderManager::_GBufferInstancedPrepass;
std::unique_ptr<GLProgram> RenderManager::_GBufferPrepass;
std::unique_ptr<GLProgram> RenderManager::_GBufferLightingPass;

#pragma endregion
#pragma endregion

void RenderManager::RenderToCameraDeferred(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds)
{
	cameraComponent->_GBuffer->Bind();
	unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 , GL_COLOR_ATTACHMENT3 };
	cameraComponent->_GBuffer->GetFrameBuffer()->DrawBuffers(4, attachments);
	cameraComponent->_GBuffer->Clear();
	const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
	if (owners) {
		auto& program = _GBufferPrepass;
		program->Bind();
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
			if (!mmc->IsEnabled() || mmc->Material == nullptr || mmc->Mesh == nullptr || mmc->ForwardRendering) continue;
			if (mmc->Material->BlendingMode != MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
			if (calculateBounds) {
				auto meshBound = mmc->Mesh->GetBound();
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
			_MaterialSettingsBlock.receiveShadow = mmc->ReceiveShadow;
			DeferredPrepass(
				mmc->Mesh.get(),
				mmc->Material.get(),
				ltw
			);
		}
	}

	owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
	if (owners) {
		auto& program = _GBufferInstancedPrepass;
		program->Bind();
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto& immc = owner.GetPrivateComponent<Particles>();
			if (!immc->IsEnabled() || immc->Material == nullptr || immc->Mesh == nullptr || immc->ForwardRendering) continue;
			if (immc->Material->BlendingMode != MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
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
			_MaterialSettingsBlock.receiveShadow = immc->ReceiveShadow;
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
	_GBufferLightingPass->Bind();
	
	cameraComponent->_GPositionBuffer->Bind(3);
	cameraComponent->_GNormalBuffer->Bind(4);
	cameraComponent->_GColorSpecularBuffer->Bind(5);
	cameraComponent->_GMetallicRoughnessAO->Bind(6);
	_GBufferLightingPass->SetInt("gPositionShadow", 3);
	_GBufferLightingPass->SetInt("gNormalShininess", 4);
	_GBufferLightingPass->SetInt("gAlbedoSpecular", 5);
	_GBufferLightingPass->SetInt("gMetallicRoughnessAO", 6);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	auto res = cameraComponent->GetResolution();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, cameraComponent->_GBuffer->GetFrameBuffer()->ID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, cameraComponent->GetFrameBuffer()->ID()); // write to default framebuffer
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
	if (cameraComponent->DrawSkyBox && cameraComponent->SkyBox.get()) {
		Default::GLPrograms::SkyboxProgram->Bind();
		Default::GLPrograms::SkyboxVAO->Bind();
		cameraComponent->SkyBox->Texture()->Bind(3);
		Default::GLPrograms::SkyboxProgram->SetInt("skybox", 3);
	}
	else
	{
		Default::GLPrograms::BackGroundProgram->Bind();
		Default::GLPrograms::SkyboxVAO->Bind();
		Default::GLPrograms::BackGroundProgram->SetFloat3("clearColor", cameraComponent->ClearColor);
	}
	glDrawArrays(GL_TRIANGLES, 0, 36);
	GLVAO::BindDefault();
	glDepthFunc(GL_LESS); // set depth function back to default
}

void RenderManager::RenderToCameraForward(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds)
{
	bool debug = cameraComponent.get() == EditorManager::_SceneCamera.get();
	cameraComponent->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	std::map<float, std::pair<std::pair<Entity, MeshRenderer*>, glm::mat4>> transparentEntities;
	std::map<float, std::pair<std::pair<Entity, Particles*>, glm::mat4>> transparentInstancedEntities;
	const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
	if (owners) {
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
			if (!mmc->IsEnabled() || mmc->Material == nullptr || mmc->Mesh == nullptr || !mmc->ForwardRendering && mmc->Material->BlendingMode == MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
			auto meshBound = mmc->Mesh->GetBound();
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
			if (mmc->Material->BlendingMode == MaterialBlendingMode::OFF) {
				transparentEntities.insert({ glm::distance(cameraTransform.GetPosition(), center), std::make_pair(std::make_pair(owner, mmc.get()), ltw) });
				continue;
			}
			DrawMesh(
				mmc->Mesh.get(),
				mmc->Material.get(),
				ltw,
				mmc->ReceiveShadow);
		}
	}
	owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
	if (owners) {
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto& immc = owner.GetPrivateComponent<Particles>();
			if (!immc->IsEnabled() || immc->Material == nullptr || immc->Mesh == nullptr || !immc->ForwardRendering && immc->Material->BlendingMode == MaterialBlendingMode::OFF) continue;
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
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
			mmc->Mesh.get(),
			mmc->Material.get(),
			pair->second.second,
			mmc->ReceiveShadow
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
	_DirectionalLightQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_DirectionalLightQuery, DirectionalLight());
	_PointLightQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PointLightQuery, PointLight());
	_SpotLightQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_SpotLightQuery, SpotLight());

	_MaterialSettingsBuffer = std::make_unique<GLUBO>();
	_MaterialSettingsBuffer->SetData(sizeof(MaterialSettingsBlock), nullptr, GL_STREAM_DRAW);
	_MaterialSettingsBuffer->SetBase(6);
#pragma region Kernel Setup
	std::vector<glm::vec4> uniformKernel;
	std::vector<glm::vec4> gaussianKernel;
	for (unsigned int i = 0; i < Default::ShaderIncludes::MaxKernelAmount; i++)
	{
		uniformKernel.emplace_back(glm::vec4(glm::ballRand(1.0f), 1.0f));
		gaussianKernel.emplace_back(glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f));
	}
	_KernelBlock = std::make_unique<GLUBO>();
	_KernelBlock->SetBase(5);
	_KernelBlock->SetData(sizeof(glm::vec4) * uniformKernel.size() + sizeof(glm::vec4) * gaussianKernel.size(), NULL, GL_STATIC_DRAW);
	_KernelBlock->SubData(0, sizeof(glm::vec4) * uniformKernel.size(), uniformKernel.data());
	_KernelBlock->SubData(sizeof(glm::vec4) * uniformKernel.size(), sizeof(glm::vec4) * gaussianKernel.size(), gaussianKernel.data());

#pragma endregion
#pragma region Shadow
	_ShadowCascadeInfoBlock = new GLUBO();
	_ShadowCascadeInfoBlock->SetData(sizeof(LightSettingsBlock), nullptr, GL_DYNAMIC_DRAW);
	_ShadowCascadeInfoBlock->SetBase(4);

#pragma region LightInfoBlocks
	_DirectionalLightBlock = new GLUBO();
	_PointLightBlock = new GLUBO();
	_SpotLightBlock = new GLUBO();
	size_t size = 16 + Default::ShaderIncludes::MaxDirectionalLightAmount * sizeof(DirectionalLightInfo);
	_DirectionalLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	_DirectionalLightBlock->SetBase(1);
	size = 16 + Default::ShaderIncludes::MaxPointLightAmount * sizeof(PointLightInfo);
	_PointLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	_PointLightBlock->SetBase(2);
	size = 16 + Default::ShaderIncludes::MaxSpotLightAmount * sizeof(SpotLightInfo);
	_SpotLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	_SpotLightBlock->SetBase(3);
#pragma endregion
#pragma region DirectionalLight
	_DirectionalLightShadowMap = std::make_unique<DirectionalLightShadowMap>(_ShadowMapResolution);

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


	_DirectionalLightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/DirectionalLightShadowMapInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	_DirectionalLightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);

#pragma region PointLight
	_PointLightShadowMap = std::make_unique<PointLightShadowMap>(_ShadowMapResolution);
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

	_PointLightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/PointLightShadowMapInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	_PointLightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader,
		geomShader
		);
#pragma endregion
#pragma region SpotLight
	_SpotLightShadowMap = std::make_unique<SpotLightShadowMap>(_ShadowMapResolution);
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


	_SpotLightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/SpotLightShadowMapInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	_SpotLightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);
#pragma endregion
#pragma endregion
	_MaterialSettingsBlock.directionalShadowMap = _DirectionalLightShadowMap->DepthMapArray()->GetHandle();
	_MaterialSettingsBlock.pointShadowMap = _PointLightShadowMap->DepthMapArray()->GetHandle();
	_MaterialSettingsBlock.spotShadowMap = _SpotLightShadowMap->DepthMap()->GetHandle();
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

	_GBufferLightingPass = std::make_unique<GLProgram>(
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

	_GBufferPrepass = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/StandardInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	_GBufferInstancedPrepass = std::make_unique<GLProgram>(
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
	_Triangles = 0;
	_DrawCall = 0;
	if (_MainCameraComponent != nullptr) {
		_MainCameraComponent->ResizeResolution(_MainCameraResolutionX, _MainCameraResolutionY);
	}
	const std::vector<Entity>* cameraEntities = EntityManager::GetPrivateComponentOwnersList<CameraComponent>();
	if (cameraEntities != nullptr)
	{
		for (auto cameraEntity : *cameraEntities) {
			if (!cameraEntity.Enabled()) continue;
			auto& cameraComponent = cameraEntity.GetPrivateComponent<CameraComponent>();
			if(cameraComponent->IsEnabled()) cameraComponent->Clear();
		}
	}
	auto worldBound = Application::GetCurrentWorld()->GetBound();
	glm::vec3 maxBound = worldBound.Max;
	glm::vec3 minBound = worldBound.Min;
	if (_MainCameraComponent != nullptr) {
		auto mainCameraEntity = _MainCameraComponent->GetOwner();
		if (mainCameraEntity.Enabled()) {
			auto& mainCamera = _MainCameraComponent;
#pragma region Shadow
			if (_MainCameraComponent->IsEnabled()) {
				auto ltw = mainCameraEntity.GetComponentData<GlobalTransform>();
				glm::vec3 mainCameraPos = ltw.GetPosition();
				glm::quat mainCameraRot = ltw.GetRotation();

				_ShadowCascadeInfoBlock->SubData(0, sizeof(LightSettingsBlock), &_LightSettings);

				std::vector<DirectionalLight> directionLightsList;
				std::vector<Entity> directionalLightEntities;
				_DirectionalLightQuery.ToComponentDataArray(directionLightsList);
				_DirectionalLightQuery.ToEntityArray(directionalLightEntities);
				size_t size = directionLightsList.size();
				//1.	利用EntityManager找到场景内所有Light instance。
				if (!directionLightsList.empty()) {
					size_t enabledSize = 0;
					for (int i = 0; i < size; i++) {
						const auto& dlc = directionLightsList[i];
						Entity lightEntity = directionalLightEntities[i];
						if (!lightEntity.Enabled()) continue;
						glm::quat rotation = lightEntity.GetComponentData<GlobalTransform>().GetRotation();
						glm::vec3 lightDir = glm::normalize(rotation * glm::vec3(0, 0, 1));
						float planeDistance = 0;
						glm::vec3 center;
						_DirectionalLights[enabledSize].direction = glm::vec4(lightDir, 0.0f);
						_DirectionalLights[enabledSize].diffuse = glm::vec4(dlc.diffuse * dlc.diffuseBrightness, 1);
						_DirectionalLights[enabledSize].specular = glm::vec4(dlc.specular * dlc.specularBrightness, 1);
						for (int split = 0; split < Default::ShaderIncludes::ShadowCascadeAmount; split++) {
							//2.	计算Cascade Split所需信息
							float splitStart = 0;
							float splitEnd = _MaxShadowDistance;
							if (split != 0) splitStart = _MaxShadowDistance * _ShadowCascadeSplit[split - 1];
							if (split != Default::ShaderIncludes::ShadowCascadeAmount - 1) splitEnd = _MaxShadowDistance * _ShadowCascadeSplit[split];
							_LightSettings.SplitDistance[split] = splitEnd;
							glm::mat4 lightProjection, lightView;
							float max = 0;
							glm::vec3 lightPos;
							glm::vec3 cornerPoints[8];
							mainCamera->CalculateFrustumPoints(splitStart, splitEnd, mainCameraPos, mainCameraRot, cornerPoints);
							glm::vec3 cameraFrustumCenter = (mainCameraRot * glm::vec3(0, 0, -1)) * ((splitEnd - splitStart) / 2.0f + splitStart) + mainCameraPos;
							if (_StableFit) {
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
								_DirectionalLights[enabledSize].viewPort = glm::ivec4(0, 0, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
								break;
							case 1:
								_DirectionalLights[enabledSize].viewPort = glm::ivec4(_ShadowMapResolution / 2, 0, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
								break;
							case 2:
								_DirectionalLights[enabledSize].viewPort = glm::ivec4(0, _ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
								break;
							case 3:
								_DirectionalLights[enabledSize].viewPort = glm::ivec4(_ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
								break;
							}

#pragma region Fix Shimmering due to the movement of the camera

							glm::mat4 shadowMatrix = lightProjection * lightView;
							glm::vec4 shadowOrigin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
							shadowOrigin = shadowMatrix * shadowOrigin;
							GLfloat storedW = shadowOrigin.w;
							shadowOrigin = shadowOrigin * (float)_DirectionalLights[enabledSize].viewPort.z / 2.0f;
							glm::vec4 roundedOrigin = glm::round(shadowOrigin);
							glm::vec4 roundOffset = roundedOrigin - shadowOrigin;
							roundOffset = roundOffset * 2.0f / (float)_DirectionalLights[enabledSize].viewPort.z;
							roundOffset.z = 0.0f;
							roundOffset.w = 0.0f;
							glm::mat4 shadowProj = lightProjection;
							shadowProj[3] += roundOffset;
							lightProjection = shadowProj;
#pragma endregion
							_DirectionalLights[enabledSize].lightSpaceMatrix[split] = lightProjection * lightView;
							_DirectionalLights[enabledSize].lightFrustumWidth[split] = max;
							_DirectionalLights[enabledSize].lightFrustumDistance[split] = planeDistance;
							if (split == Default::ShaderIncludes::ShadowCascadeAmount - 1) _DirectionalLights[enabledSize].ReservedParameters = glm::vec4(dlc.lightSize, 0, dlc.bias, dlc.normalOffset);

						}
						enabledSize++;
					}
					_DirectionalLightBlock->SubData(0, 4, &enabledSize);
					if (enabledSize != 0) {
						_DirectionalLightBlock->SubData(16, enabledSize * sizeof(DirectionalLightInfo), &_DirectionalLights[0]);
					}
					if (_MaterialSettingsBlock.enableShadow) {
						_DirectionalLightShadowMap->Bind();
						_DirectionalLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
						glClear(GL_DEPTH_BUFFER_BIT);
						enabledSize = 0;
						_DirectionalLightProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = directionalLightEntities[i];
							if (!lightEntity.Enabled()) continue;
							/*
							glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(),
								0, _DirectionalLights[enabledSize].viewPort.x, _DirectionalLights[enabledSize].viewPort.y,
								0, (GLsizei)_DirectionalLights[enabledSize].viewPort.z, (GLsizei)_DirectionalLights[enabledSize].viewPort.w, (GLsizei)4, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
							*/
							glViewport(_DirectionalLights[enabledSize].viewPort.x, _DirectionalLights[enabledSize].viewPort.y, _DirectionalLights[enabledSize].viewPort.z, _DirectionalLights[enabledSize].viewPort.w);
							_DirectionalLightProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.Enabled()) continue;
									auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
									if (!mmc->IsEnabled() || !mmc->CastShadow || mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
									MaterialPropertySetter(mmc.get()->Material.get(), true);
									auto mesh = mmc->Mesh;
									auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
									_DirectionalLightProgram->SetFloat4x4("model", ltw);
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
						_DirectionalLightInstancedProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = directionalLightEntities[i];
							if (!lightEntity.Enabled()) continue;
							glViewport(_DirectionalLights[enabledSize].viewPort.x, _DirectionalLights[enabledSize].viewPort.y, _DirectionalLights[enabledSize].viewPort.z, _DirectionalLights[enabledSize].viewPort.w);
							_DirectionalLightInstancedProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.Enabled()) continue;
									auto& immc = owner.GetPrivateComponent<Particles>();
									if (!immc->IsEnabled() || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
									MaterialPropertySetter(immc.get()->Material.get(), true);
									size_t count = immc->Matrices.size();
									std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
									auto mesh = immc->Mesh;
									_DirectionalLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
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
					_DirectionalLightBlock->SubData(0, 4, &size);
				}
				std::vector<Entity> pointLightEntities;
				std::vector<PointLight> pointLightsList;
				_PointLightQuery.ToEntityArray(pointLightEntities);
				_PointLightQuery.ToComponentDataArray(pointLightsList);
				size = pointLightsList.size();
				if (!pointLightsList.empty()) {
					size_t enabledSize = 0;
					for (int i = 0; i < size; i++) {
						const auto& plc = pointLightsList[i];
						Entity lightEntity = pointLightEntities[i];
						if (!lightEntity.Enabled()) continue;
						glm::vec3 position = EntityManager::GetComponentData<GlobalTransform>(lightEntity).Value[3];
						_PointLights[enabledSize].position = glm::vec4(position, 0);

						_PointLights[enabledSize].constantLinearQuadFarPlane.x = plc.constant;
						_PointLights[enabledSize].constantLinearQuadFarPlane.y = plc.linear;
						_PointLights[enabledSize].constantLinearQuadFarPlane.z = plc.quadratic;
						_PointLights[enabledSize].diffuse = glm::vec4(plc.diffuse * plc.diffuseBrightness, 0);
						_PointLights[enabledSize].specular = glm::vec4(plc.specular * plc.specularBrightness, 0);
						_PointLights[enabledSize].constantLinearQuadFarPlane.w = plc.farPlane;

						glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), _PointLightShadowMap->GetResolutionRatio(), 1.0f, _PointLights[enabledSize].constantLinearQuadFarPlane.w);
						_PointLights[enabledSize].lightSpaceMatrix[0] = shadowProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						_PointLights[enabledSize].lightSpaceMatrix[1] = shadowProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						_PointLights[enabledSize].lightSpaceMatrix[2] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
						_PointLights[enabledSize].lightSpaceMatrix[3] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
						_PointLights[enabledSize].lightSpaceMatrix[4] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						_PointLights[enabledSize].lightSpaceMatrix[5] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
						_PointLights[enabledSize].ReservedParameters = glm::vec4(plc.bias, plc.lightSize, 0, 0);

						switch (enabledSize)
						{
						case 0:
							_PointLights[enabledSize].viewPort = glm::ivec4(0, 0, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						case 1:
							_PointLights[enabledSize].viewPort = glm::ivec4(_ShadowMapResolution / 2, 0, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						case 2:
							_PointLights[enabledSize].viewPort = glm::ivec4(0, _ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						case 3:
							_PointLights[enabledSize].viewPort = glm::ivec4(_ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						}
						enabledSize++;
					}
					_PointLightBlock->SubData(0, 4, &enabledSize);
					if (enabledSize != 0)_PointLightBlock->SubData(16, enabledSize * sizeof(PointLightInfo), &_PointLights[0]);
					if (_MaterialSettingsBlock.enableShadow) {
#pragma region PointLight Shadowmap Pass
						_PointLightShadowMap->Bind();
						_PointLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
						glClear(GL_DEPTH_BUFFER_BIT);
						_PointLightProgram->Bind();
						enabledSize = 0;
						for (int i = 0; i < size; i++) {
							Entity lightEntity = pointLightEntities[i];
							if (!lightEntity.Enabled()) continue;
							glViewport(_PointLights[enabledSize].viewPort.x, _PointLights[enabledSize].viewPort.y, _PointLights[enabledSize].viewPort.z, _PointLights[enabledSize].viewPort.w);
							_PointLightProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.Enabled()) continue;
									auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
									if (!mmc->IsEnabled() || !mmc->CastShadow || mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
									MaterialPropertySetter(mmc.get()->Material.get(), true);
									auto mesh = mmc->Mesh;
									_PointLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
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
						_PointLightInstancedProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = pointLightEntities[i];
							if (!lightEntity.Enabled()) continue;
							glViewport(_PointLights[enabledSize].viewPort.x, _PointLights[enabledSize].viewPort.y, _PointLights[enabledSize].viewPort.z, _PointLights[enabledSize].viewPort.w);
							_PointLightInstancedProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.Enabled()) continue;
									auto& immc = owner.GetPrivateComponent<Particles>();
									if (!immc->IsEnabled() || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
									MaterialPropertySetter(immc.get()->Material.get(), true);
									size_t count = immc->Matrices.size();
									std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
									auto mesh = immc->Mesh;
									_PointLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
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
					_PointLightBlock->SubData(0, 4, &size);
				}
				std::vector<Entity> spotLightEntities;
				std::vector<SpotLight> spotLightsList;
				_SpotLightQuery.ToEntityArray(spotLightEntities);
				_SpotLightQuery.ToComponentDataArray(spotLightsList);
				size = spotLightsList.size();
				if (!spotLightsList.empty())
				{
					size_t enabledSize = 0;
					for (int i = 0; i < size; i++) {
						const auto& slc = spotLightsList[i];
						Entity lightEntity = spotLightEntities[i];
						if (!lightEntity.Enabled()) continue;
						auto ltw = EntityManager::GetComponentData<GlobalTransform>(lightEntity);
						glm::vec3 position = ltw.Value[3];
						glm::vec3 front = ltw.GetRotation() * glm::vec3(0, 0, -1);
						glm::vec3 up = ltw.GetRotation() * glm::vec3(0, 1, 0);
						_SpotLights[enabledSize].position = glm::vec4(position, 0);
						_SpotLights[enabledSize].direction = glm::vec4(front, 0);
						_SpotLights[enabledSize].constantLinearQuadFarPlane.x = slc.constant;
						_SpotLights[enabledSize].constantLinearQuadFarPlane.y = slc.linear;
						_SpotLights[enabledSize].constantLinearQuadFarPlane.z = slc.quadratic;
						_SpotLights[enabledSize].constantLinearQuadFarPlane.w = slc.farPlane;
						_SpotLights[enabledSize].diffuse = glm::vec4(slc.diffuse * slc.diffuseBrightness, 0);
						_SpotLights[enabledSize].specular = glm::vec4(slc.specular * slc.specularBrightness, 0);

						glm::mat4 shadowProj = glm::perspective(glm::radians(slc.outerDegrees * 2.0f), _SpotLightShadowMap->GetResolutionRatio(), 1.0f, _SpotLights[enabledSize].constantLinearQuadFarPlane.w);
						_SpotLights[enabledSize].lightSpaceMatrix = shadowProj * glm::lookAt(position, position + front, up);
						_SpotLights[enabledSize].cutOffOuterCutOffLightSizeBias = glm::vec4(glm::cos(glm::radians(slc.innerDegrees)), glm::cos(glm::radians(slc.outerDegrees)), slc.lightSize, slc.bias);

						switch (enabledSize)
						{
						case 0:
							_SpotLights[enabledSize].viewPort = glm::ivec4(0, 0, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						case 1:
							_SpotLights[enabledSize].viewPort = glm::ivec4(_ShadowMapResolution / 2, 0, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						case 2:
							_SpotLights[enabledSize].viewPort = glm::ivec4(0, _ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						case 3:
							_SpotLights[enabledSize].viewPort = glm::ivec4(_ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2, _ShadowMapResolution / 2);
							break;
						}
						enabledSize++;
					}
					_SpotLightBlock->SubData(0, 4, &enabledSize);
					if (enabledSize != 0)_SpotLightBlock->SubData(16, enabledSize * sizeof(SpotLightInfo), &_SpotLights[0]);
					if (_MaterialSettingsBlock.enableShadow) {
#pragma region SpotLight Shadowmap Pass
						_SpotLightShadowMap->Bind();
						_SpotLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
						glClear(GL_DEPTH_BUFFER_BIT);
						_SpotLightProgram->Bind();
						enabledSize = 0;
						for (int i = 0; i < size; i++) {
							Entity lightEntity = spotLightEntities[i];
							if (!lightEntity.Enabled()) continue;
							glViewport(_SpotLights[enabledSize].viewPort.x, _SpotLights[enabledSize].viewPort.y, _SpotLights[enabledSize].viewPort.z, _SpotLights[enabledSize].viewPort.w);
							_SpotLightProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.Enabled()) continue;
									auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
									if (!mmc->IsEnabled() || !mmc->CastShadow || mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
									MaterialPropertySetter(mmc.get()->Material.get(), true);
									auto mesh = mmc->Mesh;
									_SpotLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
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
						_SpotLightInstancedProgram->Bind();
						for (int i = 0; i < size; i++) {
							Entity lightEntity = spotLightEntities[i];
							if (!lightEntity.Enabled()) continue;
							glViewport(_SpotLights[enabledSize].viewPort.x, _SpotLights[enabledSize].viewPort.y, _SpotLights[enabledSize].viewPort.z, _SpotLights[enabledSize].viewPort.w);
							_SpotLightInstancedProgram->SetInt("index", enabledSize);
							const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
							if (owners) {
								for (auto owner : *owners) {
									if (!owner.Enabled()) continue;
									auto& immc = owner.GetPrivateComponent<Particles>();
									if (!immc->IsEnabled() || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
									MaterialPropertySetter(immc.get()->Material.get(), true);
									size_t count = immc->Matrices.size();
									std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
									auto mesh = immc->Mesh;
									_SpotLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<GlobalTransform>(owner).Value);
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
					_SpotLightBlock->SubData(0, 4, &size);
				}
			}
#pragma endregion
		}
	}
#pragma region Render to other cameras
	if (cameraEntities != nullptr)
	{
		for (auto cameraEntity : *cameraEntities) {
			if (!cameraEntity.Enabled()) continue;
			auto& cameraComponent = cameraEntity.GetPrivateComponent<CameraComponent>();
			if (_MainCameraComponent && cameraComponent.get() == _MainCameraComponent) continue;
			if (cameraComponent->IsEnabled())
			{
				auto ltw = cameraEntity.GetComponentData<GlobalTransform>();
				CameraComponent::_CameraInfoBlock.UpdateMatrices(cameraComponent.get(),
					ltw.GetPosition(),
					ltw.GetRotation()
				);
				CameraComponent::_CameraInfoBlock.UploadMatrices(cameraComponent.get());
				const auto cameraTransform = cameraEntity.GetComponentData<GlobalTransform>();				
				RenderToCameraDeferred(cameraComponent, cameraTransform, minBound, maxBound, false);
				RenderBackGround(cameraComponent);
				RenderToCameraForward(cameraComponent, cameraTransform, minBound, maxBound, false);
			}
		}
	}
#pragma endregion
#pragma region Render to scene camera
	if (EditorManager::_Enabled && EditorManager::_SceneCamera->IsEnabled()) {
		CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
			EditorManager::_SceneCameraPosition,
			EditorManager::_SceneCameraRotation
		);
		CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
		GlobalTransform cameraTransform;
		cameraTransform.Value = glm::translate(EditorManager::_SceneCameraPosition) * glm::mat4_cast(EditorManager::_SceneCameraRotation);

#pragma region For entity selection
		const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
		if (owners) {
			EditorManager::_SceneCameraEntityRecorder->Bind();
			EditorManager::_SceneCameraEntityRecorderProgram->Bind();
			for (auto owner : *owners) {
				if (!owner.Enabled()) continue;
				auto& mmc = owner.GetPrivateComponent<MeshRenderer>();
				if (!mmc->IsEnabled() || mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
				if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
				auto ltw = EntityManager::GetComponentData<GlobalTransform>(owner).Value;
				auto* mesh = mmc->Mesh.get();
				mesh->Enable();
				mesh->VAO()->DisableAttributeArray(12);
				mesh->VAO()->DisableAttributeArray(13);
				mesh->VAO()->DisableAttributeArray(14);
				mesh->VAO()->DisableAttributeArray(15);
				EditorManager::_SceneCameraEntityRecorderProgram->SetInt("EntityIndex", owner.Index);
				EditorManager::_SceneCameraEntityRecorderProgram->SetFloat4x4("model", ltw);
				glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
			}
			GLVAO::BindDefault();
		}
#pragma endregion
		RenderToCameraDeferred(EditorManager::_SceneCamera, cameraTransform, minBound, maxBound, false);
		RenderBackGround(EditorManager::_SceneCamera);
		RenderToCameraForward(EditorManager::_SceneCamera, cameraTransform, minBound, maxBound, false);
	}
#pragma endregion

#pragma region Render to main Camera and calculate bounds.
	if (_MainCameraComponent != nullptr) {
		auto mainCameraEntity = _MainCameraComponent->GetOwner();
		if (mainCameraEntity.Enabled()) {
			auto& mainCamera = _MainCameraComponent;
			if (_MainCameraComponent->IsEnabled()) {
				auto minBound = glm::vec3((int)INT_MAX);
				auto maxBound = glm::vec3((int)INT_MIN);
				auto ltw = mainCameraEntity.GetComponentData<GlobalTransform>();
				CameraComponent::_CameraInfoBlock.UpdateMatrices(mainCamera,
					ltw.GetPosition(),
					ltw.GetRotation()
				);
				CameraComponent::_CameraInfoBlock.UploadMatrices(mainCamera);
				GlobalTransform cameraTransform = mainCameraEntity.GetComponentData<GlobalTransform>();
				auto& mainCameraComponent = mainCameraEntity.GetPrivateComponent<CameraComponent>();
				RenderToCameraDeferred(mainCameraComponent, cameraTransform, minBound, maxBound, true);
				RenderBackGround(mainCameraComponent);
				RenderToCameraForward(mainCameraComponent, cameraTransform, minBound, maxBound, true);
				worldBound.Max = maxBound;
				worldBound.Min = minBound;
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
	_ShadowCascadeSplit[0] = r1;
	_ShadowCascadeSplit[1] = r2;
	_ShadowCascadeSplit[2] = r3;
	_ShadowCascadeSplit[3] = r4;
}

void UniEngine::RenderManager::SetShadowMapResolution(size_t value)
{
	_ShadowMapResolution = value;
	if (_DirectionalLightShadowMap != nullptr)_DirectionalLightShadowMap->SetResolution(value);
}

void UniEngine::RenderManager::SetPCSSPCFSampleAmount(int value)
{
	_LightSettings.PCSSPCFSampleAmount = glm::clamp(value, 0, 16);
}


void UniEngine::RenderManager::SetPCSSBSAmount(int value)
{
	_LightSettings.PCSSBSAmount = glm::clamp(value, 0, 16);
}

void UniEngine::RenderManager::SetStableFit(bool value)
{
	_StableFit = true;
}

void UniEngine::RenderManager::SetSeamFixRatio(float value)
{
	_LightSettings.SeamFixRatio = value;
}

void UniEngine::RenderManager::SetMaxShadowDistance(float value)
{
	_MaxShadowDistance = value;
}

void UniEngine::RenderManager::SetVSMMaxVariance(float value)
{
	_LightSettings.VSMMaxVariance = value;
}

void UniEngine::RenderManager::SetLightBleedControlFactor(float value)
{
	_LightSettings.LightBleedFactor = value;
}

void UniEngine::RenderManager::SetPCSSScaleFactor(float value)
{
	_LightSettings.PCSSScaleFactor = value;
}

void UniEngine::RenderManager::SetEVSMExponent(float value)
{
	_LightSettings.EVSMExponent = value;
}

void UniEngine::RenderManager::SetAmbientLight(float value)
{
	_LightSettings.AmbientLight = value;
}

void RenderManager::SetEnableShadow(bool value)
{
	_MaterialSettingsBlock.enableShadow = value;
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
			if (!postProcessingEntity.Enabled()) continue;
			auto& postProcessing = postProcessingEntity.GetPrivateComponent<PostProcessing>();
			if(postProcessing->IsEnabled()) postProcessing->Process();
		}
	}
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::BeginMenu("Rendering"))
			{
				ImGui::Checkbox("Lighting Manager", &_EnableLightMenu);
				ImGui::Checkbox("Render Manager", &_EnableRenderMenu);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (_EnableLightMenu)
	{
		ImGui::Begin("Light Manager");
		if (ImGui::TreeNode("Environment Lighting")) {
			ImGui::DragFloat("Brightness", &_LightSettings.AmbientLight, 0.01f, 0.0f, 2.0f);
			ImGui::TreePop();
		}
		bool enableShadow = _MaterialSettingsBlock.enableShadow;
		if(ImGui::Checkbox("Enable shadow", &enableShadow))
		{
			_MaterialSettingsBlock.enableShadow = enableShadow;
		}
		if (_MaterialSettingsBlock.enableShadow && ImGui::TreeNode("Shadow")) {
			if (ImGui::TreeNode("Distance"))
			{
				ImGui::DragFloat("Max shadow distance", &_MaxShadowDistance, 1.0f, 0.1f);
				ImGui::DragFloat("Split 1", &_ShadowCascadeSplit[0], 0.01f, 0.0f, _ShadowCascadeSplit[1]);
				ImGui::DragFloat("Split 2", &_ShadowCascadeSplit[1], 0.01f, _ShadowCascadeSplit[0], _ShadowCascadeSplit[2]);
				ImGui::DragFloat("Split 3", &_ShadowCascadeSplit[2], 0.01f, _ShadowCascadeSplit[1], _ShadowCascadeSplit[3]);
				ImGui::DragFloat("Split 4", &_ShadowCascadeSplit[3], 0.01f, _ShadowCascadeSplit[2], 1.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("PCSS")) {
				ImGui::DragFloat("PCSS Factor", &_LightSettings.PCSSScaleFactor, 0.01f, 0.0f);
				ImGui::DragInt("Blocker search side amount", &_LightSettings.PCSSBSAmount, 1, 1, 8);
				ImGui::DragInt("PCF Sample Size", &_LightSettings.PCSSPCFSampleAmount, 1, 1, 64);
				ImGui::TreePop();
			}
			ImGui::DragFloat("Seam fix ratio", &_LightSettings.SeamFixRatio, 0.001f, 0.0f, 0.1f);
			ImGui::Checkbox("Stable fit", &_StableFit);
			ImGui::TreePop();
		}
		ImGui::End();
	}
	if (_EnableRenderMenu)
	{
		ImGui::Begin("Render Manager");
		ImGui::Checkbox("Display info", &_EnableInfoWindow);
		ImGui::End();
	}

	ImVec2 viewPortSize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

	ImGui::Begin("Camera");
	{
		viewPortSize = ImGui::GetWindowSize();
		ImVec2 overlayPos;
		static int corner = 1;
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			viewPortSize = ImGui::GetWindowSize();
			// Get the size of the child (i.e. the whole draw size of the windows).
			overlayPos = ImGui::GetWindowPos();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			bool cameraActive = false;
			if (_MainCameraComponent != nullptr) {
				auto entity = _MainCameraComponent->GetOwner();
				if (entity.Enabled() && _MainCameraComponent->IsEnabled())
				{
					auto id = _MainCameraComponent->GetTexture()->Texture()->ID();
					ImGui::Image((ImTextureID)id, viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
					cameraActive = true;
				}
			}
			if(!cameraActive){
				ImGui::Text("No active main camera!");
			}

			ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
			if (_EnableInfoWindow)
			{
				ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
				ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
				ImGui::SetNextWindowBgAlpha(0.35f);
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

				ImGui::BeginChild("Render Info", ImVec2(200, 100), false, window_flags);
				ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
				std::string trisstr = "";
				if (_Triangles < 999) trisstr += std::to_string(_Triangles);
				else if (_Triangles < 999999) trisstr += std::to_string((int)(_Triangles / 1000)) + "K";
				else trisstr += std::to_string((int)(_Triangles / 1000000)) + "M";
				trisstr += " tris";
				ImGui::Text(trisstr.c_str());
				ImGui::Text("%d drawcall", _DrawCall);
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
	_MainCameraResolutionX = viewPortSize.x;
	_MainCameraResolutionY = viewPortSize.y;
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
	_MaterialSettingsBlock.alphaDiscardEnabled = material->AlphaDiscardEnabled;
	_MaterialSettingsBlock.alphaDiscardOffset = material->AlphaDiscardOffset;
	_MaterialSettingsBlock.dispScale = material->DisplacementMapScale;
	_MaterialSettingsBlock.albedoColorVal = glm::vec4(material->AlbedoColor, 1.0f);
	_MaterialSettingsBlock.shininessVal = material->Shininess;
	_MaterialSettingsBlock.metallicVal = material->Metallic;
	_MaterialSettingsBlock.roughnessVal = material->Roughness;
	_MaterialSettingsBlock.aoVal = material->AmbientOcclusion;
	
	_MaterialSettingsBlock.albedoEnabled = false;
	_MaterialSettingsBlock.normalEnabled = false;
	_MaterialSettingsBlock.metallicEnabled = false;
	_MaterialSettingsBlock.roughnessEnabled = false;
	_MaterialSettingsBlock.aoEnabled = false;
	
	_MaterialSettingsBlock.ambientEnabled = false;
	_MaterialSettingsBlock.diffuseEnabled = false;
	_MaterialSettingsBlock.specularEnabled = false;
	_MaterialSettingsBlock.emissiveEnabled = false;
	_MaterialSettingsBlock.displacementEnabled = false;

	for(const auto& i : material->_Textures)
	{
		if (!i.second || !i.second->Texture()) continue;
		switch (i.second->_Type)
		{
		case TextureType::ALBEDO:
			_MaterialSettingsBlock.albedoMap = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.albedoEnabled = static_cast<int>(true);
			break;
		case TextureType::NORMAL:
			_MaterialSettingsBlock.normalMap = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.normalEnabled = static_cast<int>(true);
			break;
		case TextureType::METALLIC:
			_MaterialSettingsBlock.metallicMap = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.metallicEnabled = static_cast<int>(true);
			break;
		case TextureType::ROUGHNESS:
			_MaterialSettingsBlock.roughnessMap = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.roughnessEnabled = static_cast<int>(true);
			break;
		case TextureType::AO:
			_MaterialSettingsBlock.aoMap = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.aoEnabled = static_cast<int>(true);
			break;
		case TextureType::AMBIENT:
			_MaterialSettingsBlock.ambient = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.ambientEnabled = static_cast<int>(true);
			break;
		case TextureType::DIFFUSE:
			_MaterialSettingsBlock.diffuse = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.diffuseEnabled = static_cast<int>(true);
			break;
		case TextureType::SPECULAR:
			_MaterialSettingsBlock.specular = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.specularEnabled = static_cast<int>(true);
			break;
		case TextureType::EMISSIVE:
			_MaterialSettingsBlock.emissive = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.emissiveEnabled = static_cast<int>(true);
			break;
		case TextureType::DISPLACEMENT:
			_MaterialSettingsBlock.displacement = i.second->Texture()->GetHandle();
			_MaterialSettingsBlock.displacementEnabled = static_cast<int>(true);
			break;
		}
	}
	_MaterialSettingsBuffer->SubData(0, sizeof(MaterialSettingsBlock), &_MaterialSettingsBlock);
}

void RenderManager::DeferredPrepass(Mesh* mesh, Material* material, glm::mat4 model)
{
	if (mesh == nullptr || material == nullptr) return;
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	_DrawCall++;
	_Triangles += mesh->Size() / 3;
	auto& program = _GBufferPrepass;
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

	_DrawCall++;
	_Triangles += mesh->Size() * count / 3;
	auto& program = _GBufferInstancedPrepass;
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
	_DrawCall++;
	_Triangles += mesh->Size() * count / 3;
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
	_MaterialSettingsBlock.receiveShadow = receiveShadow;
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
	_DrawCall++;
	_Triangles += mesh->Size() / 3;
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
	_MaterialSettingsBlock.receiveShadow = receiveShadow;
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
	_DrawCall++;
	_Triangles += mesh->Size() * count / 3;
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

	_DrawCall++;
	_Triangles += mesh->Size() / 3;
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	GLVAO::BindDefault();
}
#pragma endregion

#pragma region External
void UniEngine::RenderManager::DrawGizmoMeshInstanced(Mesh* mesh, glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmoInstanced(mesh, color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void RenderManager::DrawGizmoRay(glm::vec4 color, glm::vec3 start, glm::vec3 end, float width)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();

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
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
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
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
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
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();

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
		if (cameraComponent == EditorManager::_SceneCamera.get()) return;
		if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
		CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
			EditorManager::_SceneCameraPosition,
			EditorManager::_SceneCameraRotation
		);
		CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
		EditorManager::_SceneCamera->Bind();
		DrawMesh(mesh, material, model, receiveShadow);
	}
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	const auto entity = cameraComponent->GetOwner();
	if (!entity.Enabled()) return;
	const auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
	glm::vec3 scale;
	glm::vec3 trans;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ltw.Value, scale, rotation, trans, skew, perspective);
	CameraComponent::_CameraInfoBlock.UpdateMatrices(cameraComponent,
		trans,
		rotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(cameraComponent);
	cameraComponent->Bind();
	DrawMesh(mesh, material, model, receiveShadow);
}

void RenderManager::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices,
	size_t count, CameraComponent* cameraComponent, bool receiveShadow)
{
	{
		if (cameraComponent == EditorManager::_SceneCamera.get()) return;
		if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
		CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
			EditorManager::_SceneCameraPosition,
			EditorManager::_SceneCameraRotation
		);
		CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
		EditorManager::_SceneCamera->Bind();
		DrawMeshInstanced(mesh, material, model, matrices, count, receiveShadow);
	}
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	const auto entity = cameraComponent->GetOwner();
	if (!entity.Enabled()) return;
	const auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
	glm::vec3 scale;
	glm::vec3 trans;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ltw.Value, scale, rotation, trans, skew, perspective);
	CameraComponent::_CameraInfoBlock.UpdateMatrices(cameraComponent,
		trans,
		rotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(cameraComponent);
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
		if (cameraComponent == EditorManager::_SceneCamera.get()) return;
		if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
		CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
			EditorManager::_SceneCameraPosition,
			EditorManager::_SceneCameraRotation
		);
		CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
		EditorManager::_SceneCamera->Bind();
		DrawTexture2D(texture->Texture().get(), depth, center, size);
	}
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	const auto entity = cameraComponent->GetOwner();
	if (!entity.Enabled()) return;
	cameraComponent->Bind();
	DrawTexture2D(texture->Texture().get(), depth, center, size);
}
void RenderManager::SetMainCamera(CameraComponent* value)
{
	if (_MainCameraComponent)
	{
		_MainCameraComponent->_IsMainCamera = false;
	}
	_MainCameraComponent = value;
	if (_MainCameraComponent) _MainCameraComponent->_IsMainCamera = true;
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
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmo(Default::Primitives::Sphere.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmoInstanced(Default::Primitives::Sphere.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCube(glm::vec4 color, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmo(Default::Primitives::Cube.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmoInstanced(Default::Primitives::Cube.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuad(glm::vec4 color, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmo(Default::Primitives::Quad.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmoInstanced(Default::Primitives::Quad.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoMesh(Mesh* mesh, glm::vec4 color, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera.get());
	EditorManager::_SceneCamera->Bind();
	DrawGizmo(mesh, color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}
#pragma endregion
#pragma endregion

#pragma region Status


size_t UniEngine::RenderManager::Triangles()
{
	return _Triangles;
}

size_t UniEngine::RenderManager::DrawCall()
{
	return _DrawCall;
}

#pragma endregion
#pragma endregion





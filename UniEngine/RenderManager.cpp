#include "pch.h"
#include "RenderManager.h"
#include "TransformManager.h"
#include <gtx/matrix_decompose.hpp>
#include "UniEngine.h"
using namespace UniEngine;
#pragma region Global Var
bool RenderManager::_EnableRenderMenu = false;
bool RenderManager::_EnableInfoWindow = true;
#pragma region Shadow
#pragma region DirectionalMap
GLUBO* RenderManager::_ShadowCascadeInfoBlock;
LightSettings RenderManager::_LightSettings;
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
bool RenderManager::_EnableShadow = true;

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
MaterialTextures RenderManager::_MaterialTextures;
std::unique_ptr<GLUBO> RenderManager::_MaterialTextureBindings;
CameraComponent* RenderManager::_MainCameraComponent;
int RenderManager::_MainCameraResolutionX = 1;
int RenderManager::_MainCameraResolutionY = 1;
EntityQuery RenderManager::_DirectionalLightQuery;
EntityQuery RenderManager::_PointLightQuery;
EntityQuery RenderManager::_SpotLightQuery;
size_t RenderManager::_DrawCall;
size_t RenderManager::_Triangles;
std::unique_ptr<GLUBO> RenderManager::_KernelBlock;
std::unique_ptr<GLProgram> RenderManager::_GBufferLightingPass;

#pragma endregion
#pragma region SSAO
bool RenderManager::_EnableSSAO = true;
std::unique_ptr<GLProgram> RenderManager::_SSAOGeometryPass;
std::unique_ptr<GLProgram> RenderManager::_SSAOBlurPass;

float RenderManager::_SSAOKernelRadius = 0.3f;
float RenderManager::_SSAOKernelBias = 0.0f;
float RenderManager::_SSAOScale = 4.0;
float RenderManager::_SSAOFactor = 1.0f;
int RenderManager::_SSAOSampleSize = 9;
#pragma endregion
#pragma endregion

void RenderManager::RenderToCameraDeferred(std::unique_ptr<CameraComponent>& cameraComponent, LocalToWorld& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds)
{
	auto& camera = cameraComponent->GetCamera();
	cameraComponent->_GBuffer->Bind();
	GLFrameBuffer::Enable(GL_DEPTH_TEST);
	GLFrameBuffer::Disable(GL_BLEND);
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	cameraComponent->_GBuffer->GetFrameBuffer()->DrawBuffers(3, attachments);
	cameraComponent->_GBuffer->Clear();
	const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
	if (owners) {
		auto& program = Default::GLPrograms::DeferredPrepass;
		program->Bind();
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto* mmc = owner.GetPrivateComponent<MeshRenderer>();
			if (!mmc->get()->IsEnabled() || mmc->get()->Material == nullptr || mmc->get()->Mesh == nullptr || mmc->get()->ForwardRendering) continue;
			if (mmc->get()->BackCulling) GLFrameBuffer::Enable(GL_CULL_FACE);
			else GLFrameBuffer::Disable(GL_CULL_FACE);
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
			auto ltw = EntityManager::GetComponentData<LocalToWorld>(owner).Value;
			if (calculateBounds) {
				auto meshBound = mmc->get()->Mesh->GetBound();
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
			}
			DeferredPrepass(
				mmc->get()->Mesh.get(),
				mmc->get()->Material.get(),
				ltw
			);
		}
	}

	owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
	if (owners) {
		auto& program = Default::GLPrograms::DeferredPrepassInstanced;
		program->Bind();
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto* immc = owner.GetPrivateComponent<Particles>();
			if (!immc->get()->IsEnabled() || immc->get()->Material == nullptr || immc->get()->Mesh == nullptr || immc->get()->ForwardRendering) continue;
			if (immc->get()->BackCulling)GLFrameBuffer::Enable(GL_CULL_FACE);
			else GLFrameBuffer::Disable(GL_CULL_FACE);
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
			auto ltw = EntityManager::GetComponentData<LocalToWorld>(owner).Value;
			if (calculateBounds) {
				glm::vec3 center = ltw * glm::vec4(immc->get()->BoundingBox.Center, 1.0f);
				glm::vec3 size = glm::vec4(immc->get()->BoundingBox.Size, 0) * ltw / 2.0f;
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			DeferredPrepassInstanced(
				immc->get()->Mesh.get(),
				immc->get()->Material.get(),
				ltw,
				immc->get()->Matrices.data(),
				immc->get()->Matrices.size()
			);
		}
	}

	Default::GLPrograms::ScreenVAO->Bind();
	if (_EnableSSAO) {
		cameraComponent->_SSAO->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_SSAOGeometryPass->Bind();
		cameraComponent->_GPositionBuffer->Bind(3);
		cameraComponent->_GNormalBuffer->Bind(4);
		cameraComponent->_SSAONoise->Bind(5);
		_SSAOGeometryPass->SetFloat("radius", _SSAOKernelRadius);
		_SSAOGeometryPass->SetFloat("bias", _SSAOKernelBias);
		_SSAOGeometryPass->SetFloat("factor", _SSAOFactor);
		_SSAOGeometryPass->SetInt("kernelSize", _SSAOSampleSize);
		_SSAOGeometryPass->SetInt("gPosition", 3);
		_SSAOGeometryPass->SetInt("gNormal", 4);
		_SSAOGeometryPass->SetInt("texNoise", 5);
		_SSAOGeometryPass->SetFloat2("noiseScale", camera->GetResolution() / _SSAOScale);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		cameraComponent->_SSAOBlurFilter->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		cameraComponent->_SSAOColor->Bind(3);
		_SSAOBlurPass->SetInt("ssaoInput", 3);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	camera->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_GBufferLightingPass->Bind();
	cameraComponent->_GPositionBuffer->Bind(3);
	cameraComponent->_GNormalBuffer->Bind(4);
	cameraComponent->_GColorSpecularBuffer->Bind(5);
	_GBufferLightingPass->SetBool("receiveShadow", true);
	_GBufferLightingPass->SetBool("enableSSAO", _EnableSSAO);
	if (_EnableSSAO)
	{
		cameraComponent->_SSAOBlur->Bind(6);
		_GBufferLightingPass->SetInt("ssao", 6);
	}
	_GBufferLightingPass->SetInt("directionalShadowMap", 0);
	_GBufferLightingPass->SetInt("pointShadowMap", 1);
	_GBufferLightingPass->SetBool("enableShadow", _EnableShadow);
	_GBufferLightingPass->SetInt("gPosition", 3);
	_GBufferLightingPass->SetInt("gNormal", 4);
	_GBufferLightingPass->SetInt("gAlbedoSpec", 5);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	auto res = camera->GetResolution();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, cameraComponent->_GBuffer->GetFrameBuffer()->ID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->GetFrameBuffer()->ID()); // write to default framebuffer
	glBlitFramebuffer(
		0, 0, res.x, res.y, 0, 0, res.x, res.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST
	);
	RenderTarget::BindDefault();

}

void RenderManager::RenderBackGround(std::unique_ptr<CameraComponent>& cameraComponent)
{
	if (cameraComponent->DrawSkyBox && cameraComponent->SkyBox.get()) {
		cameraComponent->_Camera->Bind();
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		Default::GLPrograms::SkyboxProgram->Bind();
		// skybox cube
		Default::GLPrograms::SkyboxVAO->Bind();
		cameraComponent->SkyBox->Texture()->Bind(3);
		Default::GLPrograms::SkyboxProgram->SetInt("skybox", 3);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLVAO::BindDefault();
		glDepthFunc(GL_LESS); // set depth function back to default
	}
	else
	{
		cameraComponent->_Camera->Bind();
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		Default::GLPrograms::BackGroundProgram->Bind();
		Default::GLPrograms::SkyboxVAO->Bind();
		Default::GLPrograms::BackGroundProgram->SetFloat3("clearColor", cameraComponent->ClearColor);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLVAO::BindDefault();
		glDepthFunc(GL_LESS); // set depth function back to default
	}
}

void RenderManager::RenderToCameraForward(std::unique_ptr<CameraComponent>& cameraComponent, LocalToWorld& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds)
{
	auto& camera = cameraComponent->_Camera;

	camera->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glDisable(GL_BLEND);
	std::map<float, std::pair<MeshRenderer*, glm::mat4>> transparentEntities;
	const std::vector<Entity>* owners = EntityManager::GetPrivateComponentOwnersList<MeshRenderer>();
	if (owners) {
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto* mmc = owner.GetPrivateComponent<MeshRenderer>();
			if (!mmc->get()->IsEnabled() || mmc->get()->Material == nullptr || mmc->get()->Mesh == nullptr || !mmc->get()->ForwardRendering) continue;
			if (mmc->get()->BackCulling)glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
			auto ltw = EntityManager::GetComponentData<LocalToWorld>(owner).Value;
			auto meshBound = mmc->get()->Mesh->GetBound();
			glm::vec3 center = ltw * glm::vec4(meshBound.Center, 1.0f);
			if (calculateBounds) {
				glm::vec3 size = glm::vec4(meshBound.Size, 0) * ltw / 2.0f;
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			if (!mmc->get()->Transparency) {
				DrawMesh(
					mmc->get()->Mesh.get(),
					mmc->get()->Material.get(),
					ltw,
					camera.get(),
					mmc->get()->ReceiveShadow);

			}
			else
			{
				transparentEntities.insert({ glm::distance(cameraTransform.GetPosition(), center), std::make_pair(mmc->get(), ltw) });
			}


		}
	}
	owners = EntityManager::GetPrivateComponentOwnersList<Particles>();
	if (owners) {
		for (auto owner : *owners) {
			if (!owner.Enabled()) continue;
			auto* immc = owner.GetPrivateComponent<Particles>();
			if (!immc->get()->IsEnabled() || immc->get()->Material == nullptr || immc->get()->Mesh == nullptr || !immc->get()->ForwardRendering) continue;
			if (immc->get()->BackCulling)glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
			if(immc->get()->Transparency)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}else
			{
				glDisable(GL_BLEND);
			}
			if (EntityManager::HasComponentData<CameraLayerMask>(owner) && !(EntityManager::GetComponentData<CameraLayerMask>(owner).Value & CameraLayer_MainCamera)) continue;
			auto ltw = EntityManager::GetComponentData<LocalToWorld>(owner).Value;
			if (calculateBounds) {
				glm::vec3 center = ltw * glm::vec4(immc->get()->BoundingBox.Center, 1.0f);
				glm::vec3 size = glm::vec4(immc->get()->BoundingBox.Size, 0) * ltw / 2.0f;
				minBound = glm::vec3(
					glm::min(minBound.x, center.x - size.x),
					glm::min(minBound.y, center.y - size.y),
					glm::min(minBound.z, center.z - size.z));

				maxBound = glm::vec3(
					glm::max(maxBound.x, center.x + size.x),
					glm::max(maxBound.y, center.y + size.y),
					glm::max(maxBound.z, center.z + size.z));
			}
			DrawMeshInstanced(
				immc->get()->Mesh.get(),
				immc->get()->Material.get(),
				ltw,
				immc->get()->Matrices.data(),
				immc->get()->Matrices.size(),
				camera.get(),
				immc->get()->ReceiveShadow);
		}
	}

	//Draw all transparent objects here:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto it = transparentEntities.rbegin(); it != transparentEntities.rend(); ++it)
	{
		const auto* mmc = it->second.first;
		DrawMesh(
			mmc->Mesh.get(),
			mmc->Material.get(),
			it->second.second,
			camera.get(),
			mmc->ReceiveShadow
		);
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

	_MaterialTextureBindings = std::make_unique<GLUBO>();
	_MaterialTextureBindings->SetData(sizeof(MaterialTextures), nullptr, GL_STREAM_DRAW);
	_MaterialTextureBindings->SetBase(6);
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
	_ShadowCascadeInfoBlock->SetData(sizeof(LightSettings), nullptr, GL_DYNAMIC_DRAW);
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
		FileIO::LoadFileAsString("Shaders/Vertex/DirectionalLightShadowMap.vert");
	std::string fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/DirectionalLightShadowMap.frag");
	std::string geomShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Geometry/DirectionalLightShadowMap.geom");
	_DirectionalLightProgram = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/DirectionalLightShadowMapInstanced.vert");
	_DirectionalLightInstancedProgram = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

#pragma region PointLight
	_PointLightShadowMap = std::make_unique<PointLightShadowMap>(_ShadowMapResolution);
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/PointLightShadowMap.vert");
	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/PointLightShadowMap.frag");
	geomShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Geometry/PointLightShadowMap.geom");

	_PointLightProgram = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/PointLightShadowMapInstanced.vert");
	_PointLightInstancedProgram = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);
#pragma endregion
#pragma region SpotLight
	_SpotLightShadowMap = std::make_unique<SpotLightShadowMap>(_ShadowMapResolution);
	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Vertex/SpotLightShadowMap.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Fragment/SpotLightShadowMap.frag");
	_SpotLightProgram = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
		);

	vertShaderCode = std::string("#version 460 core\n") 
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Vertex/SpotLightShadowMapInstanced.vert");
	_SpotLightInstancedProgram = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
		);
#pragma endregion
#pragma endregion
	_MaterialTextures.directionalShadowMap = _DirectionalLightShadowMap->DepthMapArray()->GetHandle();
	_MaterialTextures.pointShadowMap = _PointLightShadowMap->DepthMapArray()->GetHandle();
	_MaterialTextures.spotShadowMap = _SpotLightShadowMap->DepthMap()->GetHandle();
#pragma region GBuffer
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/DeferredLighting.frag");

	_GBufferLightingPass = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
		);

#pragma endregion
#pragma region SSAO
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/SSAOGeometry.frag");

	_SSAOGeometryPass = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
		);

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/SSAOBlur.frag");

	_SSAOBlurPass = std::make_unique<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
		);

#pragma endregion
}

void UniEngine::RenderManager::PreUpdate()
{
	glCullFace(GL_BACK);
	_Triangles = 0;
	_DrawCall = 0;
	const std::vector<Entity>* cameraEntities = EntityManager::GetPrivateComponentOwnersList<CameraComponent>();
	if (cameraEntities != nullptr)
	{
		for (auto cameraEntity : *cameraEntities) {
			cameraEntity.GetPrivateComponent<CameraComponent>()->get()->_Camera->Clear();
		}
	}
	auto worldBound = _World->GetBound();
	glm::vec3 maxBound = worldBound.Center + worldBound.Size;
	glm::vec3 minBound = worldBound.Center - worldBound.Size;
	if (_MainCameraComponent != nullptr) {
		auto& mainCamera = _MainCameraComponent->_Camera;
		auto mainCameraEntity = _MainCameraComponent->GetOwner();
		_MainCameraComponent->ResizeResolution(_MainCameraResolutionX, _MainCameraResolutionY);
#pragma region Shadow
		if (mainCameraEntity.Enabled() && _MainCameraComponent->IsEnabled()) {
			auto ltw = mainCameraEntity.GetComponentData<LocalToWorld>();
			glm::vec3 mainCameraPos = ltw.GetPosition();
			glm::quat mainCameraRot = ltw.GetRotation();

			_ShadowCascadeInfoBlock->SubData(0, sizeof(LightSettings), &_LightSettings);

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
					glm::quat rotation = lightEntity.GetComponentData<LocalToWorld>().GetRotation();
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

						center = ClosestPointOnLine(worldBound.Center, cameraFrustumCenter, cameraFrustumCenter + lightDir);
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
						if (split == Default::ShaderIncludes::ShadowCascadeAmount - 1) _DirectionalLights[enabledSize].ReservedParameters = glm::vec4(dlc.lightSize, 0, dlc.depthBias, dlc.normalOffset);

					}
					enabledSize++;
				}
				_DirectionalLightBlock->SubData(0, 4, &enabledSize);
				if (enabledSize != 0) {
					_DirectionalLightBlock->SubData(16, enabledSize * sizeof(DirectionalLightInfo), &_DirectionalLights[0]);
				}
				if (_EnableShadow) {
					_DirectionalLightShadowMap->Bind();
					_DirectionalLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
					glEnable(GL_DEPTH_TEST);
					glDisable(GL_BLEND);
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
								auto* mmc = owner.GetPrivateComponent<MeshRenderer>();
								if (!mmc->get()->IsEnabled() || !mmc->get()->CastShadow || mmc->get()->Material == nullptr || mmc->get()->Mesh == nullptr) continue;
								if (mmc->get()->BackCulling)glEnable(GL_CULL_FACE);
								else glDisable(GL_CULL_FACE);
								auto mesh = mmc->get()->Mesh;
								auto ltw = EntityManager::GetComponentData<LocalToWorld>(owner).Value;
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
								auto* immc = owner.GetPrivateComponent<Particles>();
								if (!immc->get()->IsEnabled() || !immc->get()->CastShadow || immc->get()->Material == nullptr || immc->get()->Mesh == nullptr) continue;
								if (immc->get()->BackCulling)glEnable(GL_CULL_FACE);
								else glDisable(GL_CULL_FACE);
								size_t count = immc->get()->Matrices.size();
								GLVBO* matricesBuffer = new GLVBO();
								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->get()->Matrices.data(), GL_STATIC_DRAW);
								auto mesh = immc->get()->Mesh;
								_DirectionalLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(owner).Value);
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
								delete matricesBuffer;
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
					glm::vec3 position = EntityManager::GetComponentData<LocalToWorld>(lightEntity).Value[3];
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
				if (_EnableShadow) {
#pragma region PointLight Shadowmap Pass
					_PointLightShadowMap->Bind();
					_PointLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
					glEnable(GL_DEPTH_TEST);
					glDisable(GL_BLEND);
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
								auto* mmc = owner.GetPrivateComponent<MeshRenderer>();
								if (!mmc->get()->IsEnabled() || !mmc->get()->CastShadow || mmc->get()->Material == nullptr || mmc->get()->Mesh == nullptr) continue;
								if (mmc->get()->BackCulling)glEnable(GL_CULL_FACE);
								else glDisable(GL_CULL_FACE);
								auto mesh = mmc->get()->Mesh;
								_PointLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(owner).Value);
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
								auto* immc = owner.GetPrivateComponent<Particles>();
								if (!immc->get()->IsEnabled() || !immc->get()->CastShadow || immc->get()->Material == nullptr || immc->get()->Mesh == nullptr) continue;
								if (immc->get()->BackCulling)glEnable(GL_CULL_FACE);
								else glDisable(GL_CULL_FACE);
								size_t count = immc->get()->Matrices.size();
								GLVBO* matricesBuffer = new GLVBO();
								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->get()->Matrices.data(), GL_STATIC_DRAW);
								auto mesh = immc->get()->Mesh;
								_PointLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(owner).Value);
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
								delete matricesBuffer;
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
			if(!spotLightsList.empty())
			{
				size_t enabledSize = 0;
				for (int i = 0; i < size; i++) {
					const auto& slc = spotLightsList[i];
					Entity lightEntity = spotLightEntities[i];
					if (!lightEntity.Enabled()) continue;
					auto ltw = EntityManager::GetComponentData<LocalToWorld>(lightEntity);
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
				if (_EnableShadow) {
#pragma region SpotLight Shadowmap Pass
					_SpotLightShadowMap->Bind();
					_SpotLightShadowMap->GetFrameBuffer()->DrawBuffer(GL_NONE);
					glEnable(GL_DEPTH_TEST);
					glDisable(GL_BLEND);
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
								auto* mmc = owner.GetPrivateComponent<MeshRenderer>();
								if (!mmc->get()->IsEnabled() || !mmc->get()->CastShadow || mmc->get()->Material == nullptr || mmc->get()->Mesh == nullptr) continue;
								if (mmc->get()->BackCulling)glEnable(GL_CULL_FACE);
								else glDisable(GL_CULL_FACE);
								auto mesh = mmc->get()->Mesh;
								_SpotLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(owner).Value);
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
								auto* immc = owner.GetPrivateComponent<Particles>();
								if (!immc->get()->IsEnabled() || !immc->get()->CastShadow || immc->get()->Material == nullptr || immc->get()->Mesh == nullptr) continue;
								if (immc->get()->BackCulling)glEnable(GL_CULL_FACE);
								else glDisable(GL_CULL_FACE);
								size_t count = immc->get()->Matrices.size();
								GLVBO* matricesBuffer = new GLVBO();
								matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->get()->Matrices.data(), GL_STATIC_DRAW);
								auto mesh = immc->get()->Mesh;
								_SpotLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(owner).Value);
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
								delete matricesBuffer;
							}
						}
						enabledSize++;
					}
#pragma endregion
				}
			}else
			{
				_SpotLightBlock->SubData(0, 4, &size);
			}
		}
#pragma endregion
	}
#pragma region Render to other cameras
	if (cameraEntities != nullptr)
	{
		for (auto cameraEntity : *cameraEntities) {
			if (!cameraEntity.Enabled()) continue;
			auto& cameraComponent = *cameraEntity.GetPrivateComponent<CameraComponent>();
			if (_MainCameraComponent && cameraComponent.get() == _MainCameraComponent) continue;
			if (cameraComponent->IsEnabled())
			{
				auto ltw = cameraEntity.GetComponentData<LocalToWorld>();
				Camera::CameraInfoBlock.UpdateMatrices(cameraComponent->_Camera.get(),
					ltw.GetPosition(),
					ltw.GetRotation()
				);
				Camera::CameraInfoBlock.UploadMatrices(cameraComponent->_Camera->CameraUniformBufferBlock);
				LocalToWorld cameraTransform = cameraEntity.GetComponentData<LocalToWorld>();
				RenderToCameraDeferred(cameraComponent, cameraTransform, minBound, maxBound, false);
				RenderBackGround(cameraComponent);
				RenderToCameraForward(cameraComponent, cameraTransform, minBound, maxBound, false);
			}
		}
	}
#pragma endregion
#pragma region Render to scene camera
	if (EditorManager::_Enabled && EditorManager::_SceneCamera->IsEnabled()) {
		Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
			EditorManager::_SceneCameraPosition,
			EditorManager::_SceneCameraRotation
		);
		Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
		LocalToWorld cameraTransform;
		cameraTransform.Value = glm::translate(EditorManager::_SceneCameraPosition) * glm::mat4_cast(EditorManager::_SceneCameraRotation);
		RenderToCameraDeferred(EditorManager::_SceneCamera, cameraTransform, minBound, maxBound, false);
		RenderBackGround(EditorManager::_SceneCamera);
		RenderToCameraForward(EditorManager::_SceneCamera, cameraTransform, minBound, maxBound, false);
	}
#pragma endregion

#pragma region Render to main Camera and calculate bounds.
	if (_MainCameraComponent != nullptr) {
		auto& mainCamera = _MainCameraComponent->_Camera;
		auto mainCameraEntity = _MainCameraComponent->GetOwner();
		if (mainCameraEntity.Enabled() && _MainCameraComponent->IsEnabled()) {
			auto minBound = glm::vec3((int)INT_MAX);
			auto maxBound = glm::vec3((int)INT_MIN);
			auto ltw = mainCameraEntity.GetComponentData<LocalToWorld>();
			Camera::CameraInfoBlock.UpdateMatrices(mainCamera.get(),
				ltw.GetPosition(),
				ltw.GetRotation()
			);
			Camera::CameraInfoBlock.UploadMatrices(mainCamera->CameraUniformBufferBlock);
			LocalToWorld cameraTransform = mainCameraEntity.GetComponentData<LocalToWorld>();
			RenderToCameraDeferred(*mainCameraEntity.GetPrivateComponent<CameraComponent>(), cameraTransform, minBound, maxBound, true);
			RenderBackGround(*mainCameraEntity.GetPrivateComponent<CameraComponent>());
			RenderToCameraForward(*mainCameraEntity.GetPrivateComponent<CameraComponent>(), cameraTransform, minBound, maxBound, true);
			worldBound.Size = (maxBound - minBound) / 2.0f;
			worldBound.Center = (maxBound + minBound) / 2.0f;
			worldBound.Radius = glm::length(worldBound.Size);
			_World->SetBound(worldBound);
		}
	}
#pragma endregion
}

inline float RenderManager::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
#pragma region Settings
void RenderManager::SetSSAOKernelRadius(float value)
{
	_SSAOKernelRadius = value;
}

void RenderManager::SetSSAOKernelBias(float value)
{
	_SSAOKernelBias = value;
}

void RenderManager::SetSSAOScale(float value)
{
	_SSAOScale = value;
}

void RenderManager::SetSSAOFactor(float value)
{
	_SSAOFactor = value;
}

void RenderManager::SetEnableSSAO(bool value)
{
	_EnableSSAO = value;
}

void RenderManager::SetSSAOSampleSize(int value)
{
	_SSAOSampleSize = glm::clamp(value, 0, 64);
}
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
	_EnableShadow = value;
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
		ImGui::Checkbox("Enable shadow", &_EnableShadow);
		if (_EnableShadow && ImGui::TreeNode("Shadow")) {
			if (ImGui::TreeNode("Distance"))
			{
				ImGui::DragFloat("Max shadow distance", &_MaxShadowDistance, _MaxShadowDistance / 10.0f, 0.1f);
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
		ImGui::Checkbox("Enable SSAO", &_EnableSSAO);
		if (_EnableSSAO && ImGui::TreeNode("SSAO")) {
			ImGui::DragFloat("Radius", &_SSAOKernelRadius, 0.01f, 0.1f, 5.0f);
			ImGui::DragFloat("Bias", &_SSAOKernelBias, 0.001f, 0.0f, 1.0f);
			ImGui::DragFloat("Factor", &_SSAOFactor, 0.01f, 1.0f, 10.0f);
			ImGui::DragInt("Sample Size", &_SSAOSampleSize, 1, 0, 64);
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
			if (_MainCameraComponent != nullptr) {
				auto id = _MainCameraComponent->_Camera->GetTexture()->ID();
				ImGui::Image((ImTextureID)id, viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
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
					glm::vec2 pos = InputManager::GetMouseScreenPosition();
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
void RenderManager::MaterialTextureBindHelper(Material* material, std::shared_ptr<GLProgram> program)
{
	if (material->_DiffuseMap && material->_DiffuseMap->Texture().get())
	{
		_MaterialTextures.diffuse = material->_DiffuseMap->Texture()->GetHandle();
	}
	else
	{
		_MaterialTextures.diffuse = Default::Textures::StandardTexture->Texture()->GetHandle();
	}
	if (material->_SpecularMap && material->_SpecularMap->Texture().get())
	{
		_MaterialTextures.specular = material->_SpecularMap->Texture()->GetHandle();
		program->SetBool("enableSpecularMapping", true);
	}
	else
	{
		program->SetBool("enableSpecularMapping", false);
	}
	if (material->_NormalMap && material->_NormalMap->Texture().get())
	{
		_MaterialTextures.normal = material->_NormalMap->Texture()->GetHandle();
		program->SetBool("enableNormalMapping", true);
	}
	else
	{
		program->SetBool("enableNormalMapping", false);
	}
	if (material->_DisplacementMap && material->_DisplacementMap->Texture().get())
	{
		_MaterialTextures.height = material->_DisplacementMap->Texture()->GetHandle();
		program->SetBool("enableParallaxMapping", true);
	}
	else
	{
		program->SetBool("enableParallaxMapping", false);
	}
	_MaterialTextureBindings->SubData(0, sizeof(MaterialTextures), &_MaterialTextures);
}

void RenderManager::DeferredPrepass(Mesh* mesh, Material* material, glm::mat4 model)
{
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	_DrawCall++;
	_Triangles += mesh->Size() / 3;
	auto& program = Default::GLPrograms::DeferredPrepass;
	program->SetFloat("material.shininess", material->_Shininess);
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	MaterialTextureBindHelper(material, program);
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	GLVAO::BindDefault();
}

void RenderManager::DeferredPrepassInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices,
	size_t count)
{
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
	auto& program = Default::GLPrograms::DeferredPrepassInstanced;
	program->SetFloat("material.shininess", material->_Shininess);
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	MaterialTextureBindHelper(material, program);
	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, bool receiveShadow)
{
	glEnable(GL_DEPTH_TEST);
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
	auto program = material->_Program;
	program->Bind();
	program->SetBool("receiveShadow", receiveShadow);
	program->SetFloat("material.shininess", material->_Shininess);
	program->SetBool("transparentDiscard", material->_TransparentDiscard);
	program->SetFloat("transparentDiscardLimit", material->_TransparentDiscardLimit);
	program->SetInt("directionalShadowMap", 0);
	program->SetInt("pointShadowMap", 1);
	program->SetBool("enableShadow", _EnableShadow);
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	MaterialTextureBindHelper(material, program);
	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 model, bool receiveShadow)
{
	if (mesh == nullptr || material == nullptr) return;
	glEnable(GL_DEPTH_TEST);
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);
	_DrawCall++;
	_Triangles += mesh->Size() / 3;
	auto program = material->_Program;
	program->Bind();
	program->SetBool("receiveShadow", receiveShadow);
	program->SetFloat("material.shininess", material->_Shininess);
	program->SetBool("transparentDiscard", material->_TransparentDiscard);
	program->SetFloat("transparentDiscardLimit", material->_TransparentDiscardLimit);
	program->SetInt("directionalShadowMap", 0);
	program->SetInt("pointShadowMap", 1);
	program->SetBool("enableShadow", _EnableShadow);
	program->SetFloat4x4("model", model);
	for (auto j : material->_FloatPropertyList) {
		program->SetFloat(j.Name, j.Value);
	}
	for (auto j : material->_Float4x4PropertyList) {
		program->SetFloat4x4(j.Name, j.Value);
	}
	MaterialTextureBindHelper(material, program);
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	GLVBO* matricesBuffer = new GLVBO();
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
	delete matricesBuffer;
}

void UniEngine::RenderManager::DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4 scaleMatrix)
{
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
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmoInstanced(mesh, color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void RenderManager::DrawGizmoRay(glm::vec4 color, glm::vec3 start, glm::vec3 end, float width)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();

	glm::quat rotation = glm::quatLookAt(end - start, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	glm::mat4 rotationMat = glm::mat4_cast(rotation);
	auto model = glm::translate((start + end) / 2.0f) * rotationMat * glm::scale(glm::vec3(width, glm::distance(end, start) / 2.0f, width));
	DrawGizmoMesh(Default::Primitives::Cylinder.get(), color, model);
}

void RenderManager::DrawGizmoRay(glm::vec4 color, Ray& ray, float width)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();

	glm::quat rotation = glm::quatLookAt(ray.Direction, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	glm::mat4 rotationMat = glm::mat4_cast(rotation);
	auto model = glm::translate((ray.Start + ray.Direction * ray.Length / 2.0f)) * rotationMat * glm::scale(glm::vec3(width, ray.Length / 2.0f, width));
	DrawGizmoMesh(Default::Primitives::Cylinder.get(), color, model);
}

void RenderManager::DrawMesh(Mesh* mesh, Material* material, glm::mat4 model,
	CameraComponent* cameraComponent, bool receiveShadow)
{
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	LocalToWorld ltw = EntityManager::GetComponentData<LocalToWorld>(cameraComponent->GetOwner());
	glm::vec3 scale;
	glm::vec3 trans;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ltw.Value, scale, rotation, trans, skew, perspective);
	Camera::CameraInfoBlock.UpdateMatrices(cameraComponent->_Camera.get(),
		trans,
		rotation
	);
	Camera::CameraInfoBlock.UploadMatrices(cameraComponent->_Camera->CameraUniformBufferBlock);
	DrawMesh(mesh, material, model, cameraComponent->GetCamera().get(), receiveShadow);
}

void RenderManager::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices,
	size_t count, CameraComponent* cameraComponent, bool receiveShadow)
{
	if (cameraComponent == nullptr || !cameraComponent->IsEnabled()) return;
	LocalToWorld ltw = EntityManager::GetComponentData<LocalToWorld>(cameraComponent->GetOwner());
	glm::vec3 scale;
	glm::vec3 trans;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ltw.Value, scale, rotation, trans, skew, perspective);
	Camera::CameraInfoBlock.UpdateMatrices(cameraComponent->_Camera.get(),
		trans,
		rotation
	);
	Camera::CameraInfoBlock.UploadMatrices(cameraComponent->_Camera->CameraUniformBufferBlock);
	DrawMeshInstanced(mesh, material, model, matrices, count, cameraComponent->GetCamera().get(), receiveShadow);
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

void UniEngine::RenderManager::DrawTexture2D(Texture2D* texture, float depth, float centerX, float centerY, float sizeX, float sizeY, RenderTarget* target)
{
	DrawTexture2D(texture, depth, glm::vec2(centerX, centerY), glm::vec2(sizeX, sizeY), target);
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
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmo(Default::Primitives::Sphere.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmoInstanced(Default::Primitives::Sphere.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCube(glm::vec4 color, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmo(Default::Primitives::Cube.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmoInstanced(Default::Primitives::Cube.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuad(glm::vec4 color, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmo(Default::Primitives::Quad.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
	DrawGizmoInstanced(Default::Primitives::Quad.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoMesh(Mesh* mesh, glm::vec4 color, glm::mat4 model, float size)
{
	if (!EditorManager::_Enabled || !EditorManager::_SceneCamera->IsEnabled()) return;
	Camera::CameraInfoBlock.UpdateMatrices(EditorManager::_SceneCamera->_Camera.get(),
		EditorManager::_SceneCameraPosition,
		EditorManager::_SceneCameraRotation
	);
	Camera::CameraInfoBlock.UploadMatrices(EditorManager::_SceneCamera->_Camera->CameraUniformBufferBlock);
	EditorManager::_SceneCamera->_Camera->Bind();
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





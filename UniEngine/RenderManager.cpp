#include "pch.h"
#include "RenderManager.h"
#include "TransformSystem.h"
#include "UniEngine.h"
using namespace UniEngine;
#pragma region Global Var
#pragma region Shadow
#pragma region DirectionalMap
GLUBO* RenderManager::_DirectionalLightBlock;
DirectionalLight RenderManager::_DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
DirectionalLightShadowMap* RenderManager::_DirectionalLightShadowMap;
RenderTarget* RenderManager::_DirectionalLightShadowMapFilter;
GLTexture* RenderManager::_DLVSMVFilter;

GLProgram* RenderManager::_DirectionalLightProgram;
GLProgram* RenderManager::_DirectionalLightInstancedProgram;
GLProgram* RenderManager::_DirectionalLightVFilterProgram;
GLProgram* RenderManager::_DirectionalLightHFilterProgram;
GLUBO* RenderManager::_ShadowCascadeInfoBlock;
LightSettings RenderManager::_LightSettings;
float RenderManager::_ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = { 0.15f, 0.3f, 0.5f, 1.0f };
float RenderManager::_MaxShadowDistance = 500;
size_t RenderManager::_DirectionalShadowMapResolution = 4096;
bool RenderManager::_StableFit = true;
#pragma endregion
bool RenderManager::_EnableLightMenu = true;
bool RenderManager::_EnableRenderMenu = false;
bool RenderManager::_EnableInfoWindow = true;
GLUBO* RenderManager::_PointLightBlock;
GLUBO* RenderManager::_SpotLightBlock;
PointLight RenderManager::_PointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLight RenderManager::_SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];
bool RenderManager::_EnableShadow = true;

PointLightShadowMap* RenderManager::_PointLightShadowMap;

GLProgram* RenderManager::_PointLightProgram;
GLProgram* RenderManager::_PointLightInstancedProgram;

#pragma endregion
#pragma region Render
int RenderManager::_ResolutionX;
int RenderManager::_ResolutionY;
EntityQuery RenderManager::_DirectionalLightQuery;
EntityQuery RenderManager::_PointLightQuery;
EntityQuery RenderManager::_SpotLightQuery;
size_t RenderManager::_DrawCall;
size_t RenderManager::_Triangles;
std::unique_ptr<GLUBO> RenderManager::_KernelBlock;
std::unique_ptr<GLProgram> RenderManager::_GBufferLightingPass;
std::unique_ptr<RenderTarget> RenderManager::_GBuffer;
std::unique_ptr<GLRenderBuffer> RenderManager::_GDepthBuffer;
std::unique_ptr<GLTexture2D> RenderManager::_GPositionBuffer;
std::unique_ptr<GLTexture2D> RenderManager::_GNormalBuffer;
std::unique_ptr<GLTexture2D> RenderManager::_GColorSpecularBuffer;
#pragma endregion
#pragma region SSAO
bool RenderManager::_EnableSSAO = true;
std::unique_ptr<GLProgram> RenderManager::_SSAOGeometryPass;
std::unique_ptr<GLProgram> RenderManager::_SSAOBlurPass;
std::unique_ptr<RenderTarget> RenderManager::_SSAO;
std::unique_ptr<GLTexture2D> RenderManager::_SSAOColor;
std::unique_ptr<GLTexture2D> RenderManager::_SSAOBlur;
std::unique_ptr<RenderTarget> RenderManager::_SSAOBlurFilter;
std::unique_ptr<GLTexture2D> RenderManager::_SSAONoise;
float RenderManager::_SSAOKernelRadius = 3.0f;
float RenderManager::_SSAOKernelBias = 0.1;
float RenderManager::_SSAOScale = 4.0;
float RenderManager::_SSAOFactor = 1.0f;
int RenderManager::_SSAOSampleSize = 9;
#pragma endregion
#pragma endregion

void RenderManager::ResizeResolution(int x, int y)
{
	const auto originalResolution = _GBuffer->GetResolution();
	if (static_cast<int>(originalResolution.x) == x && static_cast<int>(originalResolution.y) == y) return;
	_GBuffer->SetResolution(x, y);
	_GPositionBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GNormalBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GColorSpecularBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GDepthBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, x, y);

	_GBuffer->AttachRenderBuffer(_GDepthBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	_GBuffer->AttachTexture(_GPositionBuffer.get(), GL_COLOR_ATTACHMENT0);
	_GBuffer->AttachTexture(_GNormalBuffer.get(), GL_COLOR_ATTACHMENT1);
	_GBuffer->AttachTexture(_GColorSpecularBuffer.get(), GL_COLOR_ATTACHMENT2);

	_SSAO->SetResolution(x, y);
	_SSAOBlurFilter->SetResolution(x, y);
	_SSAOColor->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
	_SSAOBlur->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
	_SSAO->AttachTexture(_SSAOColor.get(), GL_COLOR_ATTACHMENT0);
	_SSAOBlurFilter->AttachTexture(_SSAOBlur.get(), GL_COLOR_ATTACHMENT0);
}

void RenderManager::RenderToCameraDeferred(CameraComponent* cameraComponent, Entity cameraEntity, glm::vec3& minBound, glm::vec3& maxBound)
{
	auto camera = cameraComponent->Value;
	_GBuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
	if (meshMaterials != nullptr) {
		auto& program = Default::GLPrograms::DeferredPrepass;
		program->Bind();
		for (const auto& mmc : *meshMaterials) {
			if (!mmc->Enabled || mmc->Material == nullptr || mmc->Mesh == nullptr || mmc->ForwardRendering) continue;
			if (mmc->BackCulling)glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
			for (auto& j : *EntityManager::GetSharedComponentEntities<MeshRenderer>(mmc)) {
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
				DeferredPrepass(
					mmc->Mesh.get(),
					mmc->Material.get(),
					ltw
				);
			}
		}
	}

	auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshRenderer>();
	if (instancedMeshMaterials != nullptr) {
		auto& program = Default::GLPrograms::DeferredPrepassInstanced;
		program->Bind();
		for (const auto& immc : *instancedMeshMaterials) {
			if (!immc->Enabled || immc->Material == nullptr || immc->Mesh == nullptr || immc->ForwardRendering) continue;
			if (immc->BackCulling)glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
			for (auto& j : *EntityManager::GetSharedComponentEntities<InstancedMeshRenderer>(immc)) {
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

				DeferredPrepassInstanced(
					immc->Mesh.get(),
					immc->Material.get(),
					ltw,
					immc->Matrices.data(),
					immc->Matrices.size()
				);
			}
		}
	}

	Default::GLPrograms::ScreenVAO->Bind();
	if (_EnableSSAO) {
		_SSAO->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_SSAOGeometryPass->Bind();
		_GPositionBuffer->Bind(3);
		_GNormalBuffer->Bind(4);
		_SSAONoise->Bind(5);
		_SSAOGeometryPass->SetFloat("radius", _SSAOKernelRadius);
		_SSAOGeometryPass->SetFloat("bias", _SSAOKernelBias);
		_SSAOGeometryPass->SetFloat("factor", _SSAOFactor);
		_SSAOGeometryPass->SetInt("kernelSize", _SSAOSampleSize);
		_SSAOGeometryPass->SetInt("gPosition", 3);
		_SSAOGeometryPass->SetInt("gNormal", 4);
		_SSAOGeometryPass->SetInt("texNoise", 5);
		_SSAOGeometryPass->SetFloat2("noiseScale", camera->GetResolution() / _SSAOScale);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		_SSAOBlurFilter->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_SSAOColor->Bind(3);
		_SSAOBlurPass->SetInt("ssaoInput", 3);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);

	camera->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_GBufferLightingPass->Bind();
	_GPositionBuffer->Bind(3);
	_GNormalBuffer->Bind(4);
	_GColorSpecularBuffer->Bind(5);
	_GBufferLightingPass->SetBool("receiveShadow", true);

	_GBufferLightingPass->SetBool("enableSSAO", _EnableSSAO);
	if (_EnableSSAO)
	{
		_SSAOBlur->Bind(6);
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
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _GBuffer->GetFrameBuffer()->ID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->GetFrameBuffer()->ID()); // write to default framebuffer
	glBlitFramebuffer(
		0, 0, res.x, res.y, 0, 0, res.x, res.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST
	);
	RenderTarget::BindDefault();

}

void RenderManager::RenderToCameraForward(CameraComponent* cameraComponent, Entity cameraEntity, glm::vec3& minBound, glm::vec3& maxBound)
{
	auto camera = cameraComponent->Value;
	camera->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
	if (meshMaterials != nullptr) {
		for (const auto& mmc : *meshMaterials) {
			auto entities = EntityManager::GetSharedComponentEntities<MeshRenderer>(mmc);
			if (!mmc->Enabled || mmc->Material == nullptr || mmc->Mesh == nullptr || !mmc->ForwardRendering) continue;
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
			if (!immc->Enabled || immc->Material == nullptr || immc->Mesh == nullptr || !immc->ForwardRendering) continue;
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
}

void RenderManager::Init()
{
	_ResolutionX = 100;
	_ResolutionY = 100;
	_DirectionalLightQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_DirectionalLightQuery, DirectionalLightComponent());
	_PointLightQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PointLightQuery, PointLightComponent());
	_SpotLightQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_SpotLightQuery, SpotLightComponent());

#pragma region Kernel Setup
	std::vector<glm::vec4> uniformKernel;
	std::vector<glm::vec4> gaussianKernel;
	for (unsigned int i = 0; i < Default::ShaderIncludes::MaxKernelAmount; i++)
	{
		uniformKernel.emplace_back(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f));
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
	size_t size = 16 + Default::ShaderIncludes::MaxDirectionalLightAmount * sizeof(DirectionalLight);
	_DirectionalLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	_DirectionalLightBlock->SetBase(1);
	size = 16 + Default::ShaderIncludes::MaxPointLightAmount * sizeof(PointLight);
	_PointLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	_PointLightBlock->SetBase(2);
	size = 16 + Default::ShaderIncludes::MaxSpotLightAmount * sizeof(SpotLight);
	_SpotLightBlock->SetData((GLsizei)size, nullptr, (GLsizei)GL_DYNAMIC_DRAW);
	_SpotLightBlock->SetBase(3);
#pragma endregion
#pragma region DirectionalLight
	_DirectionalLightShadowMap = new DirectionalLightShadowMap(_DirectionalShadowMapResolution);

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
	_DirectionalLightProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/DirectionalLightShadowMapInstanced.vert");
	_DirectionalLightInstancedProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);


	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Fragment/GaussianVFilter.frag");
	geomShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Geometry/VSMVFilterHelper.geom");

	_DirectionalLightVFilterProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Fragment/GaussianHFilter.frag");
	geomShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Geometry/VSMHFilterHelper.geom");

	_DirectionalLightHFilterProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);



	_DirectionalLightShadowMapFilter = new RenderTarget(_DirectionalShadowMapResolution, _DirectionalShadowMapResolution);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DLVSMVFilter = new GLTexture2DArray(1, GL_RG32F, (GLsizei)_DirectionalShadowMapResolution, (GLsizei)_DirectionalShadowMapResolution, (GLsizei)Default::ShaderIncludes::ShadowCascadeAmount);

	_DLVSMVFilter->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DLVSMVFilter->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DLVSMVFilter->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DLVSMVFilter->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DLVSMVFilter->SetFloat4(GL_TEXTURE_BORDER_COLOR, borderColor);
	_DirectionalLightShadowMapFilter->AttachTexture(_DLVSMVFilter, GL_COLOR_ATTACHMENT0);
	_DirectionalLightShadowMapFilter->AttachTexture(_DirectionalLightShadowMap->DepthMapArray().get(), GL_COLOR_ATTACHMENT1);
#pragma endregion
#pragma region PointLight
	_PointLightShadowMap = new PointLightShadowMap(Default::ShaderIncludes::MaxPointLightAmount);
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

	_PointLightProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/PointLightShadowMapInstanced.vert");
	_PointLightInstancedProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);
#pragma endregion
#pragma endregion
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

	_GBuffer = std::make_unique<RenderTarget>(0, 0);

	_GDepthBuffer = std::make_unique<GLRenderBuffer>();

	_GPositionBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_GPositionBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GPositionBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_GNormalBuffer = std::make_unique <GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_GNormalBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GNormalBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_GColorSpecularBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);



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

	_SSAO = std::make_unique<RenderTarget>(0, 0);
	_SSAOColor = std::make_unique<GLTexture2D>(0, GL_R32F, 0, 0, false);
	_SSAOColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_SSAOBlurFilter = std::make_unique<RenderTarget>();
	_SSAOBlur = std::make_unique<GLTexture2D>(0, GL_R32F, 0, 0, false);
	_SSAOBlur->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOBlur->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// generate noise texture
	// ----------------------
	std::vector<glm::vec3> ssaoNoise;
	for (unsigned int i = 0; i < 16; i++)
	{
		glm::vec3 noise(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), 0.0f); // rotate around z-axis (in tangent space)
		ssaoNoise.push_back(noise);
	}
	_SSAONoise = std::make_unique<GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_SSAONoise->ReSize(0, GL_RGBA32F, GL_RGB, GL_FLOAT, ssaoNoise.data(), 4, 4);
	_SSAONoise->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAONoise->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

#pragma endregion
	ResizeResolution(_ResolutionX, _ResolutionY);
}

void UniEngine::RenderManager::Start()
{
	Application::GetMainCameraComponent()->Value->SetResolution(_ResolutionX, _ResolutionY);
	ResizeResolution(_ResolutionX, _ResolutionY);

	_Triangles = 0;
	_DrawCall = 0;
	auto cameras = EntityManager::GetSharedComponentDataArray<CameraComponent>();
	for (auto cc : *cameras) {
		cc->Value->Clear();
	}

#pragma region Shadow
	auto mainCameraComponent = Application::GetMainCameraComponent()->Value;
	glm::vec3 mainCameraPos = EntityManager::GetComponentData<Translation>(Application::GetMainCameraEntity()).Value;
	glm::quat mainCameraRot = EntityManager::GetComponentData<Rotation>(Application::GetMainCameraEntity()).Value;
	auto worldBound = _World->GetBound();
	glm::vec3 maxBound = worldBound.Center + worldBound.Size;
	glm::vec3 minBound = worldBound.Center - worldBound.Size;

	_ShadowCascadeInfoBlock->SubData(0, sizeof(LightSettings), &_LightSettings);

	std::vector<DirectionalLightComponent> directionLightsList;
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
			glm::quat rotation = EntityManager::GetComponentData<Rotation>(lightEntity).Value;
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
				mainCameraComponent->CalculateFrustumPoints(splitStart, splitEnd, mainCameraPos, mainCameraRot, cornerPoints);
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
					_DirectionalLights[enabledSize].viewPort = glm::ivec4(0, 0, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				case 1:
					_DirectionalLights[enabledSize].viewPort = glm::ivec4(_DirectionalShadowMapResolution / 2, 0, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				case 2:
					_DirectionalLights[enabledSize].viewPort = glm::ivec4(0, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				case 3:
					_DirectionalLights[enabledSize].viewPort = glm::ivec4(_DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
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
			_DirectionalLightBlock->SubData(16, enabledSize * sizeof(DirectionalLight), &_DirectionalLights[0]);
		}
		if (_EnableShadow) {
			_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
			_DirectionalLightShadowMap->Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			enabledSize = 0;
			for (int i = 0; i < size; i++) {
				Entity lightEntity = directionalLightEntities[i];
				if (!lightEntity.Enabled()) continue;
				glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(),
					0, _DirectionalLights[enabledSize].viewPort.x, _DirectionalLights[enabledSize].viewPort.y,
					0, (GLsizei)_DirectionalLights[enabledSize].viewPort.z, (GLsizei)_DirectionalLights[enabledSize].viewPort.w, (GLsizei)4, GL_RED, GL_FLOAT, nullptr);

				glViewport(_DirectionalLights[enabledSize].viewPort.x, _DirectionalLights[enabledSize].viewPort.y, _DirectionalLights[enabledSize].viewPort.z, _DirectionalLights[enabledSize].viewPort.w);

				_DirectionalLightProgram->Bind();
				_DirectionalLightProgram->SetInt("index", enabledSize);
				auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
				if (meshMaterials != nullptr) {
					for (auto mmc : *meshMaterials) {
						if (!mmc->Enabled || !mmc->CastShadow || mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
						if (mmc->BackCulling)glEnable(GL_CULL_FACE);
						else glDisable(GL_CULL_FACE);
						auto entities = EntityManager::GetSharedComponentEntities<MeshRenderer>(std::shared_ptr<MeshRenderer>(mmc));
						for (auto& j : *entities) {
							if (!j.Enabled()) continue;
							auto mesh = mmc->Mesh;
							auto ltw = EntityManager::GetComponentData<LocalToWorld>(j).Value;
							_DirectionalLightProgram->SetFloat4x4("model", ltw);
							mesh->Enable();
							mesh->VAO()->DisableAttributeArray(12);
							mesh->VAO()->DisableAttributeArray(13);
							mesh->VAO()->DisableAttributeArray(14);
							mesh->VAO()->DisableAttributeArray(15);
							glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);

						}
					}
				}

				_DirectionalLightInstancedProgram->Bind();
				_DirectionalLightInstancedProgram->SetInt("index", enabledSize);
				auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshRenderer>();
				if (instancedMeshMaterials != nullptr) {
					for (auto immc : *instancedMeshMaterials) {
						if (!immc->Enabled || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
						if (immc->BackCulling)glEnable(GL_CULL_FACE);
						else glDisable(GL_CULL_FACE);

						auto entities = EntityManager::GetSharedComponentEntities<InstancedMeshRenderer>(std::shared_ptr<InstancedMeshRenderer>(immc));
						size_t count = immc->Matrices.size();
						GLVBO* matricesBuffer = new GLVBO();
						matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
						for (auto& entity : *entities) {
							if (!entity.Enabled()) continue;
							auto mesh = immc->Mesh;
							_DirectionalLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(entity).Value);
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
						delete matricesBuffer;

					}
				}
				enabledSize++;
			}
			/*
			_DirectionalLightShadowMapFilter->Bind();
			_DirectionalLightShadowMapFilter->AttachTexture(_DLVSMVFilter, GL_COLOR_ATTACHMENT0);
			_DirectionalLightShadowMapFilter->AttachTexture(_DirectionalLightShadowMap->DepthMapArray(), GL_COLOR_ATTACHMENT1);
			glDisable(GL_DEPTH_TEST);
			Default::GLPrograms::ScreenVAO->Bind();
			for (int i = 0; i < size; i++) {
				glDrawBuffer(GL_COLOR_ATTACHMENT0);
				_DirectionalLightVFilterProgram->Bind();
				_DirectionalLightVFilterProgram->SetInt("textureMapArray", 0);
				_DirectionalLightVFilterProgram->SetInt("lightIndex", i);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				_DLVSMVFilter->Bind(1);
				glDrawBuffer(GL_COLOR_ATTACHMENT1);
				_DirectionalLightHFilterProgram->Bind();
				_DirectionalLightHFilterProgram->SetInt("textureMapArray", 1);
				_DirectionalLightHFilterProgram->SetInt("lightIndex", i);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			*/

		}
	}
	else
	{
		_DirectionalLightBlock->SubData(0, 4, &size);
	}
	std::vector<Entity> pointLightEntities;
	std::vector<PointLightComponent> pointLightsList;
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
			_PointLights[enabledSize].specular = glm::vec4(plc.specular * plc.diffuseBrightness, 0);
			_PointLights[enabledSize].constantLinearQuadFarPlane.w = plc.farPlane;

			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), _PointLightShadowMap->GetResolutionRatio(), 1.0f, _PointLights[enabledSize].constantLinearQuadFarPlane.w);
			_PointLights[enabledSize].lightSpaceMatrix[0] = shadowProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[enabledSize].lightSpaceMatrix[1] = shadowProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[enabledSize].lightSpaceMatrix[2] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			_PointLights[enabledSize].lightSpaceMatrix[3] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
			_PointLights[enabledSize].lightSpaceMatrix[4] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[enabledSize].lightSpaceMatrix[5] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[enabledSize].ReservedParameters = glm::vec4(plc.bias, 0, 0, 0);
			enabledSize++;
		}
		_PointLightBlock->SubData(0, 4, &enabledSize);
		if (enabledSize != 0)_PointLightBlock->SubData(16, enabledSize * sizeof(PointLight), &_PointLights[0]);
		if (_EnableShadow) {
#pragma region PointLight Shadowmap Pass
			_PointLightShadowMap->DepthCubeMapArray()->Bind(0);
			_PointLightShadowMap->Bind();
			glCullFace(GL_FRONT);
			glEnable(GL_DEPTH_TEST);
			enabledSize = 0;
			for (int i = 0; i < size; i++) {
				Entity lightEntity = pointLightEntities[i];
				if (!lightEntity.Enabled()) continue;
				glClear(GL_DEPTH_BUFFER_BIT);
				_PointLightProgram->Bind();
				_PointLightProgram->SetInt("index", i);
				auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
				for (const auto& mmc : *meshMaterials) {
					if (!mmc->Enabled || !mmc->CastShadow || mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
					if (mmc->BackCulling)glEnable(GL_CULL_FACE);
					else glDisable(GL_CULL_FACE);

					auto entities = EntityManager::GetSharedComponentEntities<MeshRenderer>(std::shared_ptr<MeshRenderer>(mmc));
					for (auto& entity : *entities) {
						if (!entity.Enabled()) continue;
						auto mesh = mmc->Mesh;
						_PointLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(entity).Value);
						mesh->Enable();
						mesh->VAO()->DisableAttributeArray(12);
						mesh->VAO()->DisableAttributeArray(13);
						mesh->VAO()->DisableAttributeArray(14);
						mesh->VAO()->DisableAttributeArray(15);
						glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
					}

				}
				_PointLightInstancedProgram->Bind();
				_PointLightInstancedProgram->SetInt("index", i);
				auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshRenderer>();
				if (instancedMeshMaterials != nullptr) {
					for (const auto& immc : *instancedMeshMaterials) {
						if (!immc->Enabled || !immc->CastShadow || immc->Material == nullptr || immc->Mesh == nullptr) continue;
						if (immc->BackCulling)glEnable(GL_CULL_FACE);
						else glDisable(GL_CULL_FACE);
						auto entities = EntityManager::GetSharedComponentEntities<InstancedMeshRenderer>(std::shared_ptr<InstancedMeshRenderer>(immc));
						size_t count = immc->Matrices.size();
						GLVBO* matricesBuffer = new GLVBO();
						matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
						for (auto& entity : *entities) {
							if (!entity.Enabled()) continue;
							auto mesh = immc->Mesh;
							_PointLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(entity).Value);
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
						delete matricesBuffer;

					}
				}
				enabledSize++;
			}
			glCullFace(GL_BACK);
#pragma endregion
		}
	}
	else
	{
		_PointLightBlock->SubData(0, 4, &size);
	}


	/*
	if (_UpdateSpotLightBlock) {
		size_t size = _SpotLights.size();
		_SpotLightBlock->SubData(0, 4, &size);
		size = size * sizeof(SpotLight);
		if (size != 0)_SpotLightBlock->SubData(16, size, &_SpotLights[0]);
	}

	*/
#pragma endregion
	minBound = glm::vec3((int)INT_MAX);
	maxBound = glm::vec3((int)INT_MIN);
	auto cC = Application::GetMainCameraComponent();
	auto cE = Application::GetMainCameraEntity();

	Camera::_MainCameraInfoBlock.UpdateMatrices(cC->Value.get(),
		EntityManager::GetComponentData<Translation>(cE).Value,
		EntityManager::GetComponentData<Rotation>(cE).Value
	);
	Camera::_MainCameraInfoBlock.UploadMatrices(mainCameraComponent->_CameraData);
	RenderToCameraDeferred(cC, cE, minBound, maxBound);
	RenderToCameraForward(cC, cE, minBound, maxBound);
	worldBound.Size = (maxBound - minBound) / 2.0f;
	worldBound.Center = (maxBound + minBound) / 2.0f;
	worldBound.Radius = glm::length(worldBound.Size);
	_World->SetBound(worldBound);
}

void RenderManager::End()
{
	
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

void UniEngine::RenderManager::SetDirectionalLightResolution(size_t value)
{
	_DirectionalShadowMapResolution = value;
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

void RenderManager::OnGui()
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
				ImGui::DragFloat("PCSS Factor", &_LightSettings.PCSSScaleFactor, 0.1f, 0.0f);
				ImGui::DragInt("Blocker search side amount", &_LightSettings.PCSSBSAmount, 1, 1, 8);
				ImGui::DragInt("PCF Sample Size", &_LightSettings.PCSSPCFSampleAmount, 1, 1, 64);
				ImGui::TreePop();
			}
			ImGui::DragFloat("Seam fix ratio", &_LightSettings.SeamFixRatio, 0.01f, 0.0f, 0.1f);
			ImGui::Checkbox("Stable fit", &_StableFit);
			ImGui::TreePop();
		}
		ImGui::Checkbox("Enable SSAO", &_EnableSSAO);
		if (_EnableSSAO && ImGui::TreeNode("SSAO")) {
			ImGui::DragFloat("Radius", &_SSAOKernelRadius, 0.1f, 0.1f, 5.0f);
			ImGui::DragFloat("Bias", &_SSAOKernelBias, 0.1f, 0.0f, 1.0f);
			ImGui::DragFloat("Factor", &_SSAOFactor, 0.1f, 1.0f, 10.0f);
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

	ImGui::Begin("Scene");
	{
		viewPortSize = ImGui::GetWindowSize();
		ImVec2 overlayPos;
		static int corner = 1;
		ImGuiIO& io = ImGui::GetIO();

		InputManager::SetFocused(ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows));
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			viewPortSize = ImGui::GetWindowSize();
			ImGuiViewport* viewPort = ImGui::GetWindowViewport();
			InputManager::SetWindow((GLFWwindow*)viewPort->PlatformHandle);
			// Get the size of the child (i.e. the whole draw size of the windows).
			overlayPos = ImGui::GetWindowPos();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			ImGui::Image((ImTextureID)Application::GetMainCameraComponent()->Value->GetTexture()->ID(), viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_MODEL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Model>));
					std::shared_ptr<Model> payload_n = *(std::shared_ptr<Model>*)payload->Data;
					EntityArchetype archetype = EntityManager::CreateEntityArchetype("Model",
						EulerRotation(),
						LocalToParent(),
						Translation(),
						Rotation(),
						Scale(),
						LocalToWorld());
					Scale t;
					t.Value = glm::vec3(1.0f);
					AssetManager::ToEntity(archetype, payload_n).SetComponentData(t);
				}
				ImGui::EndDragDropTarget();
			}

			if (_EnableInfoWindow)
			{
				ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
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
					float x = io.MousePos.x - window_pos.x;
					float y = io.MousePos.y - window_pos.y;
					InputManager::SetMouseScreenPosition(glm::vec2(x, y));
					ImGui::Text("Mouse Position: (%.1f,%.1f)", x, y);
				}
				else {
					InputManager::SetMouseScreenPosition(glm::vec2(FLT_MAX, FLT_MAX));
					ImGui::Text("Mouse Position: <invalid>");
				}
				ImGui::EndChild();
			}
		}
		ImGui::EndChild();

	}
	ImGui::End();
	ImGui::PopStyleVar();
	_ResolutionX = viewPortSize.x;
	_ResolutionY = viewPortSize.y;
}

#pragma endregion
#pragma region RenderAPI
#pragma region Internal
void RenderManager::MaterialTextureBindHelper(Material* material, std::shared_ptr<GLProgram> program)
{
	if (material->_DiffuseMap)
	{
		material->_DiffuseMap->Texture()->Bind(3);
	}
	else
	{
		Default::Textures::StandardTexture->Texture()->Bind(3);
	}
	program->SetInt("TEXTURE_DIFFUSE0", 3);
	if (material->_SpecularMap)
	{
		material->_SpecularMap->Texture()->Bind(4);
		program->SetInt("TEXTURE_SPECULAR0", 4);
		program->SetBool("enableSpecularMapping", true);
	}
	else
	{
		program->SetBool("enableSpecularMapping", false);
	}
	if (material->_NormalMap)
	{
		material->_NormalMap->Texture()->Bind(5);
		program->SetInt("TEXTURE_NORMAL0", 5);
		program->SetBool("enableNormalMapping", true);
	}
	else
	{
		program->SetBool("enableNormalMapping", false);
	}

	if (material->_DisplacementMap)
	{
		material->_DisplacementMap->Texture()->Bind(6);
		program->SetInt("TEXTURE_HEIGHT0", 6);
		program->SetBool("enableParallaxMapping", true);
	}
	else
	{
		program->SetBool("enableParallaxMapping", false);
	}
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

	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);

	_DrawCall++;
	_Triangles += mesh->Size() * count / 3;
	auto program = material->_Program;
	program->Bind();
	program->SetBool("receiveShadow", receiveShadow);
	program->SetFloat("material.shininess", material->_Shininess);
	
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
	glEnable(GL_DEPTH_TEST);
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);

	_DrawCall++;
	_Triangles += mesh->Size() / 3;
	auto program = material->_Program;
	program->Bind();
	program->SetBool("receiveShadow", receiveShadow);
	program->SetFloat("material.shininess", material->_Shininess);
	
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
	RenderManager::_DrawCall++;
	RenderManager::_Triangles += mesh->Size() * count / 3;
	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	GLVAO::BindDefault();
	delete matricesBuffer;
}

void UniEngine::RenderManager::DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4 scaleMatrix)
{
	glEnable(GL_DEPTH_TEST);
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	Default::GLPrograms::GizmoProgram->Bind();
	Default::GLPrograms::GizmoProgram->SetFloat4("surfaceColor", color);
	Default::GLPrograms::GizmoProgram->SetFloat4x4("model", model);
	Default::GLPrograms::GizmoProgram->SetFloat4x4("scaleMatrix", scaleMatrix);

	RenderManager::_DrawCall++;
	RenderManager::_Triangles += mesh->Size() / 3;
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	GLVAO::BindDefault();
}
#pragma endregion

#pragma region External
void UniEngine::RenderManager::DrawGizmoMeshInstanced(Mesh* mesh, glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmoInstanced(mesh, color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void RenderManager::DrawGizmoRay(glm::vec4 color, RenderTarget* target, glm::vec3 start, glm::vec3 end, float width)
{


}

void RenderManager::DrawGizmoRay(glm::vec4 color, RenderTarget* target, Ray& ray, float width)
{
	glm::quat rotation = glm::quatLookAt(ray.Direction, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation *= glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	glm::mat4 rotationMat = glm::mat4_cast(rotation);
	auto model = glm::translate((ray.Start + ray.Direction * ray.Length / 2.0f)) * rotationMat * glm::scale(glm::vec3(width, ray.Length / 2.0f, width));
	DrawGizmoMesh(Default::Primitives::Cylinder.get(), color, target, model);
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

void UniEngine::RenderManager::DrawGizmoPoint(glm::vec4 color, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmo(Default::Primitives::Sphere.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmoInstanced(Default::Primitives::Sphere.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCube(glm::vec4 color, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmo(Default::Primitives::Cube.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmoInstanced(Default::Primitives::Cube.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuad(glm::vec4 color, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmo(Default::Primitives::Quad.get(), color, model, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
	DrawGizmoInstanced(Default::Primitives::Quad.get(), color, model, matrices, count, glm::scale(glm::mat4(1.0f), glm::vec3(size)));
}

void UniEngine::RenderManager::DrawGizmoMesh(Mesh* mesh, glm::vec4 color, RenderTarget* target, glm::mat4 model, float size)
{
	target->Bind();
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





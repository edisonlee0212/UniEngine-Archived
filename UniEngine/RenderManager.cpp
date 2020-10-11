#include "pch.h"
#include "RenderManager.h"
#include "TransformSystem.h"
#include "UniEngine.h"
using namespace UniEngine;
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
ShadowSettings RenderManager::_ShadowSettings;
float RenderManager::_ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = { 0.15f, 0.3f, 0.5f, 1.0f };
float RenderManager::_MaxShadowDistance = 500;
size_t RenderManager::_DirectionalShadowMapResolution = 2048;
bool RenderManager::_StableFit = true;
#pragma endregion

GLUBO* RenderManager::_PointLightBlock;
GLUBO* RenderManager::_SpotLightBlock;
PointLight RenderManager::_PointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLight RenderManager::_SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];
bool RenderManager::_EnableShadow = false;

PointLightShadowMap* RenderManager::_PointLightShadowMap;

GLProgram* RenderManager::_PointLightProgram;
GLProgram* RenderManager::_PointLightInstancedProgram;

#pragma endregion
#pragma region Render
size_t RenderManager::_DrawCall;
size_t RenderManager::_Triangles;
#pragma endregion



std::shared_ptr<GLProgram> RenderManager::_GBufferLightingPass;
std::shared_ptr<RenderTarget> RenderManager::_GBuffer;
std::shared_ptr<GLRenderBuffer> RenderManager::_GDepthBuffer;
std::shared_ptr<Texture2D> RenderManager::_GPositionBuffer;
std::shared_ptr<Texture2D> RenderManager::_GNormalBuffer;
std::shared_ptr<Texture2D> RenderManager::_GColorSpecularBuffer;

void RenderManager::ResizeGBuffer(int x, int y)
{
	const auto originalResolution = _GBuffer->GetResolution();
	if (static_cast<int>(originalResolution.x) == x && static_cast<int>(originalResolution.y) == y) return;
	_GBuffer->SetResolution(x, y);
	_GPositionBuffer->Texture()->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GNormalBuffer->Texture()->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GColorSpecularBuffer->Texture()->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, x, y);
	_GDepthBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, x, y);

	_GBuffer->AttachRenderBuffer(_GDepthBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	_GBuffer->AttachTexture(_GPositionBuffer->Texture(), GL_COLOR_ATTACHMENT0);
	_GBuffer->AttachTexture(_GNormalBuffer->Texture(), GL_COLOR_ATTACHMENT1);
	_GBuffer->AttachTexture(_GColorSpecularBuffer->Texture(), GL_COLOR_ATTACHMENT2);
}

void RenderManager::RenderToMainCamera()
{
	auto camera = Application::GetMainCameraComponent()->Value;

	auto cameraEntity = Application::GetMainCameraEntity();
	camera->Bind();
	Camera::_MainCameraInfoBlock.UpdateMatrices(camera.get(),
		EntityManager::GetComponentData<Translation>(cameraEntity).Value,
		EntityManager::GetComponentData<Rotation>(cameraEntity).Value
	);
	Camera::_MainCameraInfoBlock.UploadMatrices(camera->_CameraData);
	auto worldBound = _World->GetBound();
	glm::vec3 minBound = glm::vec3((int)INT_MAX);
	glm::vec3 maxBound = glm::vec3((int)INT_MIN);
	_GBuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
	if (meshMaterials != nullptr) {
		auto& program = Default::GLPrograms::DeferredPrepass;
		program->Bind();
		program->SetInt("directionalShadowMap", 0);
		program->SetInt("pointShadowMap", 1);
		program->SetBool("enableShadow", _EnableShadow);
		for (const auto& mmc : *meshMaterials) {
			if (mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
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
		program->SetInt("directionalShadowMap", 0);
		program->SetInt("pointShadowMap", 1);
		program->SetBool("enableShadow", _EnableShadow);
		
		for (const auto& immc : *instancedMeshMaterials) {
			if (immc->Material == nullptr || immc->Mesh == nullptr) continue;
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
	camera->Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_GBufferLightingPass->Bind();
	_GPositionBuffer->Texture()->Bind(3);
	_GNormalBuffer->Texture()->Bind(4);
	_GColorSpecularBuffer->Texture()->Bind(5);
	_GBufferLightingPass->SetBool("receiveShadow", true);
	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);
	_GBufferLightingPass->SetInt("directionalShadowMap", 0);
	_GBufferLightingPass->SetInt("pointShadowMap", 1);
	_GBufferLightingPass->SetBool("enableShadow", RenderManager::_EnableShadow);
	_GBufferLightingPass->SetInt("gPosition", 3);
	_GBufferLightingPass->SetInt("gNormal", 4);
	_GBufferLightingPass->SetInt("gAlbedoSpec", 5);

	Default::GLPrograms::ScreenVAO->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	auto res = camera->GetResolution();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _GBuffer->GetFrameBuffer()->ID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->GetFrameBuffer()->ID()); // write to default framebuffer
	glBlitFramebuffer(
		0, 0, res.x, res.y, 0, 0, res.x, res.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST
	);
	RenderTarget::BindDefault();
	worldBound.Size = (maxBound - minBound) / 2.0f;
	worldBound.Center = (maxBound + minBound) / 2.0f;
	worldBound.Radius = glm::length(worldBound.Size);
	_World->SetBound(worldBound);
}

void RenderManager::Init()
{
#pragma region Shadow
	_ShadowCascadeInfoBlock = new GLUBO();
	_ShadowCascadeInfoBlock->SetData(sizeof(ShadowSettings), NULL, GL_DYNAMIC_DRAW);
	_ShadowCascadeInfoBlock->SetBase(4);

#pragma region LightInfoBlocks
	_DirectionalLightBlock = new GLUBO();
	_PointLightBlock = new GLUBO();
	_SpotLightBlock = new GLUBO();
	size_t size = 16 + Default::ShaderIncludes::MaxDirectionalLightAmount * sizeof(DirectionalLight);
	_DirectionalLightBlock->SetData((GLsizei)size, NULL, (GLsizei)GL_DYNAMIC_DRAW);
	_DirectionalLightBlock->SetBase(1);
	size = 16 + Default::ShaderIncludes::MaxPointLightAmount * sizeof(PointLight);
	_PointLightBlock->SetData((GLsizei)size, NULL, (GLsizei)GL_DYNAMIC_DRAW);
	_PointLightBlock->SetBase(2);
	size = 16 + Default::ShaderIncludes::MaxSpotLightAmount * sizeof(SpotLight);
	_SpotLightBlock->SetData((GLsizei)size, NULL, (GLsizei)GL_DYNAMIC_DRAW);
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
	_DirectionalLightShadowMapFilter->AttachTexture(_DirectionalLightShadowMap->DepthMapArray(), GL_COLOR_ATTACHMENT1);
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
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/DeferredLighting.frag");

	_GBufferLightingPass = std::make_shared<GLProgram>(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
		);

	_GBuffer = std::make_shared<RenderTarget>(0, 0);

	_GDepthBuffer = std::make_shared<GLRenderBuffer>();

	_GPositionBuffer = std::make_shared<Texture2D>(TextureType::NONE);
	auto gPositionTex = new GLTexture2D(0, GL_RGBA32F, 0, 0, false);
	gPositionTex->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gPositionTex->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GPositionBuffer->SetTexture(gPositionTex);

	_GNormalBuffer = std::make_shared<Texture2D>(TextureType::NONE);
	auto gNormalTex = new GLTexture2D(0, GL_RGBA32F, 0, 0, false);
	gNormalTex->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gNormalTex->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GNormalBuffer->SetTexture(gNormalTex);

	_GColorSpecularBuffer = std::make_shared<Texture2D>(TextureType::NONE);
	auto gColSpecTex = new GLTexture2D(0, GL_RGBA32F, 0, 0, false);
	gColSpecTex->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gColSpecTex->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GColorSpecularBuffer->SetTexture(gColSpecTex);

	auto camera = Application::GetMainCameraComponent()->Value;
	ResizeGBuffer(camera->GetResolution().x, camera->GetResolution().y);
}

void UniEngine::RenderManager::Start()
{
	_Triangles = 0;
	_DrawCall = 0;
	auto cameras = EntityManager::GetSharedComponentDataArray<CameraComponent>();
	for (auto cc : *cameras) {
		cc->Value->Clear();
	}

#pragma region Shadow
	auto camera = Application::GetMainCameraComponent()->Value;
	glm::vec3 cameraPos = EntityManager::GetComponentData<Translation>(Application::GetMainCameraEntity()).Value;
	glm::quat cameraRot = EntityManager::GetComponentData<Rotation>(Application::GetMainCameraEntity()).Value;
	auto worldBound = _World->GetBound();
	glm::vec3 maxBound = worldBound.Center + worldBound.Size;
	glm::vec3 minBound = worldBound.Center - worldBound.Size;

	_ShadowCascadeInfoBlock->SubData(0, sizeof(ShadowSettings), &_ShadowSettings);


	//1.	利用EntityManager找到场景内所有Light instance。
	auto directionLightsList = EntityManager::GetSharedComponentDataArray<DirectionalLightComponent>();
	if (directionLightsList != nullptr) {
		size_t size = directionLightsList->size();
		for (int i = 0; i < size; i++) {
			DirectionalLightComponent* dlc = directionLightsList->at(i).get();
			Entity lightEntity = EntityManager::GetSharedComponentEntities<DirectionalLightComponent>(directionLightsList->at(i))->at(0);
			glm::quat rotation = EntityManager::GetComponentData<Rotation>(lightEntity).Value;
			glm::vec3 lightDir = glm::normalize(rotation * glm::vec3(0, 0, 1));
			float planeDistance = 0;
			glm::vec3 center;
			_DirectionalLights[i].direction = glm::vec4(lightDir, 0.0f);
			_DirectionalLights[i].diffuse = glm::vec4(dlc->diffuse, 1);
			_DirectionalLights[i].specular = glm::vec4(dlc->specular, 1);
			for (int split = 0; split < Default::ShaderIncludes::ShadowCascadeAmount; split++) {
				//2.	计算Cascade Split所需信息
				float splitStart = 0;
				float splitEnd = _MaxShadowDistance;
				if (split != 0) splitStart = _MaxShadowDistance * _ShadowCascadeSplit[split - 1];
				if (split != Default::ShaderIncludes::ShadowCascadeAmount - 1) splitEnd = _MaxShadowDistance * _ShadowCascadeSplit[split];
				_ShadowSettings.SplitDistance[split] = splitEnd;
				glm::mat4 lightProjection, lightView;
				float max = 0;
				glm::vec3 lightPos;
				glm::vec3 cornerPoints[8];
				camera->CalculateFrustumPoints(splitStart, splitEnd, cameraPos, cameraRot, cornerPoints);
				glm::vec3 cameraFrustumCenter = (cameraRot * glm::vec3(0, 0, -1)) * ((splitEnd - splitStart) / 2.0f + splitStart) + cameraPos;
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
				lightView = glm::lookAt(lightPos, lightPos + lightDir, glm::vec3(0.0, 1.0, 0.0));
				if (glm::any(glm::isnan(lightView[3]))) {
					lightView = glm::lookAt(lightPos, lightPos + lightDir, glm::vec3(0.0, 0.0, 1.0));
				}
				lightProjection = glm::ortho(-max, max, -max, max, 0.0f, planeDistance * 2.0f);
				switch (i)
				{
				case 0:
					_DirectionalLights[i].viewPort = glm::ivec4(0, 0, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				case 1:
					_DirectionalLights[i].viewPort = glm::ivec4(_DirectionalShadowMapResolution / 2, 0, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				case 2:
					_DirectionalLights[i].viewPort = glm::ivec4(0, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				case 3:
					_DirectionalLights[i].viewPort = glm::ivec4(_DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2, _DirectionalShadowMapResolution / 2);
					break;
				}
				
#pragma region Fix Shimmering due to the movement of the camera

				glm::mat4 shadowMatrix = lightProjection * lightView;
				glm::vec4 shadowOrigin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
				shadowOrigin = shadowMatrix * shadowOrigin;
				GLfloat storedW = shadowOrigin.w;
				shadowOrigin = shadowOrigin * (float)_DirectionalLights[i].viewPort.z / 2.0f;
				glm::vec4 roundedOrigin = glm::round(shadowOrigin);
				glm::vec4 roundOffset = roundedOrigin - shadowOrigin;
				roundOffset = roundOffset * 2.0f / (float)_DirectionalLights[i].viewPort.z;
				roundOffset.z = 0.0f;
				roundOffset.w = 0.0f;
				glm::mat4 shadowProj = lightProjection;
				shadowProj[3] += roundOffset;
				lightProjection = shadowProj;
#pragma endregion
				_DirectionalLights[i].lightSpaceMatrix[split] = lightProjection * lightView;
				_DirectionalLights[i].lightFrustumWidth[split] = max;
				_DirectionalLights[i].lightFrustumDistance[split] = planeDistance;
				if (split == Default::ShaderIncludes::ShadowCascadeAmount - 1) _DirectionalLights[i].ReservedParameters = glm::vec4(dlc->lightSize, 0, dlc->depthBias, dlc->normalOffset);
				
			}
		}
		_DirectionalLightBlock->SubData(0, 4, &size);
		if (size != 0) {
			_DirectionalLightBlock->SubData(16, size * sizeof(DirectionalLight), &_DirectionalLights[0]);
		}
		if (_EnableShadow) {
			_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
			_DirectionalLightShadowMap->Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			for (int i = 0; i < size; i++) {
				glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(), 
					0, _DirectionalLights[i].viewPort.x, _DirectionalLights[i].viewPort.y, 
					0, (GLsizei)_DirectionalLights[i].viewPort.z, (GLsizei)_DirectionalLights[i].viewPort.w, (GLsizei)4, GL_RED, GL_FLOAT, nullptr);
				
				glViewport(_DirectionalLights[i].viewPort.x, _DirectionalLights[i].viewPort.y, _DirectionalLights[i].viewPort.z, _DirectionalLights[i].viewPort.w);
				
				_DirectionalLightProgram->Bind();
				_DirectionalLightProgram->SetInt("index", i);
				auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
				if (meshMaterials != nullptr) {
					for (auto mmc : *meshMaterials) {
						if (mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
						if (mmc->BackCulling)glEnable(GL_CULL_FACE);
						else glDisable(GL_CULL_FACE);
						if (mmc->CastShadow) {
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
				}

				_DirectionalLightInstancedProgram->Bind();
				_DirectionalLightInstancedProgram->SetInt("index", i);
				auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshRenderer>();
				if (instancedMeshMaterials != nullptr) {
					for (auto immc : *instancedMeshMaterials) {
						if (immc->Material == nullptr || immc->Mesh == nullptr) continue;
						if (immc->BackCulling)glEnable(GL_CULL_FACE);
						else glDisable(GL_CULL_FACE);
						if (immc->CastShadow) {
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
				}
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


	auto pointLightsList = EntityManager::GetSharedComponentDataArray<PointLightComponent>();
	if (pointLightsList != nullptr) {
		size_t size = pointLightsList->size();
		for (int i = 0; i < size; i++) {
			PointLightComponent* plc = pointLightsList->at(i).get();
			Entity lightEntity = EntityManager::GetSharedComponentEntities<PointLightComponent>(pointLightsList->at(i))->at(0);
			glm::vec3 position = EntityManager::GetComponentData<LocalToWorld>(lightEntity).Value[3];
			_PointLights[i].position = glm::vec4(position, 0);

			_PointLights[i].constantLinearQuadFarPlane.x = plc->constant;
			_PointLights[i].constantLinearQuadFarPlane.y = plc->linear;
			_PointLights[i].constantLinearQuadFarPlane.z = plc->quadratic;
			_PointLights[i].diffuse = glm::vec4(plc->diffuse, 0);
			_PointLights[i].specular = glm::vec4(plc->specular, 0);
			_PointLights[i].constantLinearQuadFarPlane.w = plc->farPlane;

			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), _PointLightShadowMap->GetResolutionRatio(), 1.0f, _PointLights[i].constantLinearQuadFarPlane.w);
			_PointLights[i].lightSpaceMatrix[0] = shadowProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[i].lightSpaceMatrix[1] = shadowProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[i].lightSpaceMatrix[2] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			_PointLights[i].lightSpaceMatrix[3] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
			_PointLights[i].lightSpaceMatrix[4] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[i].lightSpaceMatrix[5] = shadowProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			_PointLights[i].ReservedParameters = glm::vec4(plc->bias, 0, 0, 0);
		}
		_PointLightBlock->SubData(0, 4, &size);
		if (size != 0)_PointLightBlock->SubData(16, size * sizeof(PointLight), &_PointLights[0]);
		if (_EnableShadow) {
#pragma region PointLight Shadowmap Pass
			_PointLightShadowMap->DepthCubeMapArray()->Bind(0);
			_PointLightShadowMap->Bind();
			glCullFace(GL_FRONT);
			glEnable(GL_DEPTH_TEST);
			for (int i = 0; i < size; i++) {
				glClear(GL_DEPTH_BUFFER_BIT);
				_PointLightProgram->Bind();
				_PointLightProgram->SetInt("index", i);
				auto meshMaterials = EntityManager::GetSharedComponentDataArray<MeshRenderer>();
				for (auto mmc : *meshMaterials) {
					if (mmc->Material == nullptr || mmc->Mesh == nullptr) continue;
					if (mmc->BackCulling)glEnable(GL_CULL_FACE);
					else glDisable(GL_CULL_FACE);
					if (mmc->CastShadow) {
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
				}
				_PointLightInstancedProgram->Bind();
				_PointLightInstancedProgram->SetInt("index", i);
				auto instancedMeshMaterials = EntityManager::GetSharedComponentDataArray<InstancedMeshRenderer>();
				if (instancedMeshMaterials != nullptr) {
					for (auto immc : *instancedMeshMaterials) {
						if (immc->Material == nullptr || immc->Mesh == nullptr) continue;
						if (immc->BackCulling)glEnable(GL_CULL_FACE);
						else glDisable(GL_CULL_FACE);
						if (immc->CastShadow) {
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
				}
			}
			glCullFace(GL_BACK);
#pragma endregion
		}
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

	RenderToMainCamera();	
}

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
	if(_DirectionalLightShadowMap != nullptr)_DirectionalLightShadowMap->SetResolution(value);
}

void UniEngine::RenderManager::SetShadowMode(ShadowMode value)
{
	_ShadowSettings.SoftShadowMode = (int)value;
}


void UniEngine::RenderManager::SetEnableSplitDisplay(bool value)
{
	_ShadowSettings.DisplaySplit = value ? 1.0f : 0.0f;
}

void UniEngine::RenderManager::SetStableFit(bool value)
{
	_StableFit = true;
}

void UniEngine::RenderManager::SetSeamFixRatio(float value)
{
	_ShadowSettings.SeamFixRatio = value;
}

void UniEngine::RenderManager::SetMaxShadowDistance(float value)
{
	_MaxShadowDistance = value;
}

void UniEngine::RenderManager::SetVSMMaxVariance(float value)
{
	_ShadowSettings.VSMMaxVariance = value;
}

void UniEngine::RenderManager::SetLightBleedControlFactor(float value)
{
	_ShadowSettings.LightBleedFactor = value;
}

void UniEngine::RenderManager::SetPCSSScaleFactor(float value)
{
	_ShadowSettings.PCSSScaleFactor = value;
}

void UniEngine::RenderManager::SetEVSMExponent(float value)
{
	_ShadowSettings.EVSMExponent = value;
}

void UniEngine::RenderManager::SetAmbientLight(float value)
{
	_ShadowSettings.AmbientLight = value;
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

#pragma endregion


#pragma region Render
#pragma region Internal
void RenderManager::MaterialTextureBindHelper(Material* material, std::shared_ptr<GLProgram> program)
{
	if (material->_DiffuseMap)
	{
		material->_DiffuseMap->Texture()->Bind(3);
	}else
	{
		Default::Textures::StandardTexture->Texture()->Bind(3);
	}
	program->SetInt("TEXTURE_DIFFUSE0", 3);
	if (material->_SpecularMap)
	{
		material->_SpecularMap->Texture()->Bind(4);
		program->SetInt("TEXTURE_SPECULAR0", 4);
		program->SetBool("enableSpecularMapping", true);
	}else
	{
		program->SetBool("enableSpecularMapping", false);
	}
	if (material->_NormalMap)
	{
		material->_NormalMap->Texture()->Bind(5);
		program->SetInt("TEXTURE_NORMAL0", 5);
		program->SetBool("enableNormalMapping", true);
	}else
	{
		program->SetBool("enableNormalMapping", false);
	}
	
	if (material->_HeightMap)
	{
		material->_HeightMap->Texture()->Bind(6);
		program->SetInt("TEXTURE_HEIGHT0", 6);
		program->SetBool("enableNormalMapping", true);
	}else
	{
		program->SetBool("enableHeightMapping", false);
	}
}

void RenderManager::DeferredPrepass(Mesh* mesh, Material* material, glm::mat4 model)
{
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);

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

	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);

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
	DrawTexture2D(texture->Texture(), depth, center, size);
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





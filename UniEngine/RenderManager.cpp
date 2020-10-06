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
size_t RenderManager::_DirectionalShadowMapResolution = 1024;
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


void RenderManager::Init()
{
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
	_DirectionalLightShadowMap = new DirectionalLightShadowMap(1, _DirectionalShadowMapResolution, _DirectionalShadowMapResolution, _ShadowSettings.SoftShadowMode == (int)ShadowMode::VSM);

	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/DirectionalLightShadowMap.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
		"\n#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(Default::ShaderIncludes::MaxDirectionalLightAmount) +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/DirectionalLightShadowMap.frag");
	std::string geomShaderCode = std::string("#version 460 core\n") +
		"\n#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(Default::ShaderIncludes::MaxDirectionalLightAmount) +
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
	fragShaderCode = std::string("#version 460 core\n") +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(Default::ShaderIncludes::MaxPointLightAmount) +
		"\n" +
		FileIO::LoadFileAsString("Shaders/Fragment/PointLightShadowMap.frag");
	geomShaderCode = std::string("#version 460 core\n") +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(Default::ShaderIncludes::MaxPointLightAmount) +
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

#pragma region Fix Shimmering due to the movement of the camera

				glm::mat4 shadowMatrix = lightProjection * lightView;
				glm::vec4 shadowOrigin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
				shadowOrigin = shadowMatrix * shadowOrigin;
				GLfloat storedW = shadowOrigin.w;
				shadowOrigin = shadowOrigin * (float)_DirectionalShadowMapResolution / 2.0f;
				glm::vec4 roundedOrigin = glm::round(shadowOrigin);
				glm::vec4 roundOffset = roundedOrigin - shadowOrigin;
				roundOffset = roundOffset * 2.0f / (float)_DirectionalShadowMapResolution;
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
			_DirectionalLightShadowMap->SetLightAmount(size);
			_DirectionalLightShadowMap->SetVSM(_ShadowSettings.SoftShadowMode == (int)ShadowMode::VSM);
			_DirectionalLightShadowMap->Bind();
			glEnable(GL_DEPTH_TEST);
			if (_ShadowSettings.SoftShadowMode == (int)ShadowMode::VSM) {
				glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(), 0, 0, 0, 0, (GLsizei)_DirectionalShadowMapResolution, (GLsizei)_DirectionalShadowMapResolution, (GLsizei)size * 4, GL_RG, GL_FLOAT, NULL);
			}
			else {
				GLfloat clearColor[4] = { 1.0f };
				glClearBufferfv(GL_COLOR, 0, clearColor);
				//glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(), 0, 0, 0, 0, (GLsizei)_DirectionalShadowMapResolution, (GLsizei)_DirectionalShadowMapResolution, (GLsizei)size * 4, GL_RED, GL_FLOAT, NULL);
			}
			for (int i = 0; i < size; i++) {
				glClear(GL_DEPTH_BUFFER_BIT);
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
								/*
								#pragma region Sphere test 1. discard useless meshes. 2. Calculate scene boundary for lightFrustum;
													auto bound = mesh->GetBound();
													glm::vec3 center = ltw * glm::vec4(bound.Center, 1.0f);
													float radius = glm::length(bound.Size * scale);

													if (glm::distance(center, ClosestPointOnLine(center, cameraPos, cameraPos - glm::vec3(_DirectionalLights[imm].direction))) - radius > _DirectionalLights[imm].ReservedParameters.y) {
														continue;
													}
								#pragma endregion
								*/
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
			_DirectionalLightShadowMapFilter->Bind();
			_DirectionalLightShadowMapFilter->AttachTexture(_DLVSMVFilter, GL_COLOR_ATTACHMENT0);
			_DirectionalLightShadowMapFilter->AttachTexture(_DirectionalLightShadowMap->DepthMapArray(), GL_COLOR_ATTACHMENT1);
			glDisable(GL_DEPTH_TEST);
			Default::GLPrograms::ScreenVAO->Bind();
			for (int i = 0; i < size; i++) {
				//if (_DirectionalLights[i].ReservedParameters.y != 0) {
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
				//}
			}
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
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
void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, bool receiveShadow)
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



	size_t textureStartIndex = 0;
	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);
	textureStartIndex += 2;

	GLint max = GLTexture::GetMaxAllowedTexture();
	if (material->Textures2Ds()->size() != 0) {
		for (auto texture : *material->Textures2Ds()) {
			if (textureStartIndex >= max) {
				Debug::Error("Max allowed texture exceeded!");
				break;
			}
			texture->Texture()->Bind((GLenum)textureStartIndex);
			textureStartIndex++;
		}
	}

	auto programs = material->Programs();
	textureStartIndex = 0;
	for (auto i = 0; i < programs->size(); i++) {
		_DrawCall++;
		_Triangles += mesh->Size() * count / 3;
		auto program = programs->at(i);
		program->Bind();
		program->SetBool("receiveShadow", receiveShadow);

		program->SetInt("directionalShadowMap", 0);
		program->SetInt("pointShadowMap", 1);
		textureStartIndex += 2;

		program->SetBool("enableShadow", _EnableShadow);
		program->SetFloat4x4("model", model);
		for (auto j : material->_FloatPropertyList) {
			program->SetFloat(j.first, j.second);
		}
		for (auto j : material->_Float4x4PropertyList) {
			program->SetFloat4x4(j.first, j.second);
		}
		if (material->Textures2Ds()->size() != 0) {
			auto textures = material->Textures2Ds();
			auto tsize = textures->size();
			unsigned diffuseNr = 0;
			unsigned ambientNr = 0;
			unsigned emissiveNr = 0;
			unsigned heightNr = 0;
			unsigned specularNr = 0;
			unsigned normalNr = 0;

			for (auto j = 0; j < tsize; j++)
			{
				std::string name = "";
				int size = -1;
				auto texture = textures->at(j);
				switch (texture->Type())
				{
				case TextureType::DIFFUSE:
					size = diffuseNr;
					name = "DIFFUSE";
					diffuseNr++;
					break;
				case TextureType::SPECULAR:
					size = specularNr;
					name = "SPECULAR";
					specularNr++;
					break;
				case TextureType::AMBIENT:
					size = ambientNr;
					name = "AMBIENT";
					ambientNr++;
					break;
				case TextureType::EMISSIVE:
					size = emissiveNr;
					name = "EMISSIVE";
					emissiveNr++;
					break;
				case TextureType::HEIGHT:
					size = heightNr;
					name = "HEIGHT";
					heightNr++;
					break;
				case TextureType::NORMAL:
					size = normalNr;
					name = "NORMAL";
					normalNr++;
					break;
				default:
					break;
				}
				if (size != -1 && size < Default::ShaderIncludes::MaxMaterialsAmount) {
					program->SetInt("TEXTURE_" + name + std::to_string(size), (int)(j + textureStartIndex));
				}
				if (normalNr == 0) {
					program->SetInt("TEXTURE_NORMAL0", (int)textureStartIndex);
					program->SetBool("enableNormalMapping", false);
				}
				else {
					program->SetBool("enableNormalMapping", true);
				}
				if (specularNr == 0) {
					program->SetInt("TEXTURE_SPECULAR0", (int)textureStartIndex);
					program->SetBool("enableSpecularMapping", false);
				}
				else {
					program->SetBool("enableSpecularMapping", true);
				}
			}
		}
		glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	}
	GLVAO::BindDefault();
	delete matricesBuffer;
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

	size_t textureStartIndex = 0;
	_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
	_PointLightShadowMap->DepthCubeMapArray()->Bind(1);
	textureStartIndex += 2;

	GLint max = GLTexture::GetMaxAllowedTexture();
	if (material->Textures2Ds()->size() != 0) {
		for (auto texture : *material->Textures2Ds()) {
			if (textureStartIndex >= max) {
				Debug::Error("Max allowed texture exceeded!");
				break;
			}
			texture->Texture()->Bind((GLenum)textureStartIndex);
			textureStartIndex++;
		}
	}

	auto programs = material->Programs();
	textureStartIndex = 0;
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() / 3;
		auto program = programs->at(i);
		program->Bind();
		program->SetBool("receiveShadow", receiveShadow);

		program->SetInt("directionalShadowMap", 0);
		program->SetInt("pointShadowMap", 1);
		textureStartIndex += 2;

		program->SetBool("enableShadow", _EnableShadow);
		program->SetFloat4x4("model", model);
		for (auto j : material->_FloatPropertyList) {
			program->SetFloat(j.first, j.second);
		}
		for (auto j : material->_Float4x4PropertyList) {
			program->SetFloat4x4(j.first, j.second);
		}
		if (material->Textures2Ds()->size() != 0) {
			auto textures = material->Textures2Ds();
			auto tsize = textures->size();
			unsigned diffuseNr = 0;
			unsigned ambientNr = 0;
			unsigned emissiveNr = 0;
			unsigned heightNr = 0;
			unsigned specularNr = 0;
			unsigned normalNr = 0;

			for (auto j = 0; j < tsize; j++)
			{
				std::string name = "";
				int size = -1;
				auto texture = textures->at(j);

				switch (texture->Type())
				{
				case TextureType::DIFFUSE:
					size = diffuseNr;
					name = "DIFFUSE";
					diffuseNr++;
					break;
				case TextureType::SPECULAR:
					size = specularNr;
					name = "SPECULAR";
					specularNr++;
					break;
				case TextureType::AMBIENT:
					size = ambientNr;
					name = "AMBIENT";
					ambientNr++;
					break;
				case TextureType::EMISSIVE:
					size = emissiveNr;
					name = "EMISSIVE";
					emissiveNr++;
					break;
				case TextureType::HEIGHT:
					size = heightNr;
					name = "HEIGHT";
					heightNr++;
					break;
				case TextureType::NORMAL:
					size = normalNr;
					name = "NORMAL";
					normalNr++;
					break;
				default:
					break;
				}
				if (size != -1 && size < Default::ShaderIncludes::MaxMaterialsAmount) {
					program->SetInt("TEXTURE_" + name + std::to_string(size), (int)(j + textureStartIndex));
				}
				if (normalNr == 0) {
					program->SetInt("TEXTURE_NORMAL0", (int)textureStartIndex);
					program->SetBool("enableNormalMapping", false);
				}
				else {
					program->SetBool("enableNormalMapping", true);
				}
				if (specularNr == 0) {
					program->SetInt("TEXTURE_SPECULAR0", (int)textureStartIndex);
					program->SetBool("enableSpecularMapping", false);
				}
				else {
					program->SetBool("enableSpecularMapping", true);
				}
			}
		}
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
	}
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





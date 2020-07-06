#include "pch.h"
#include "LightingManager.h"
#include "MeshMaterialComponent.h"
using namespace UniEngine;

#pragma region DirectionalMap
GLUBO* LightingManager::_DirectionalLightBlock;
DirectionalLight LightingManager::_DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
DirectionalLightShadowMap* LightingManager::_DirectionalLightShadowMap;
GLProgram* LightingManager::_DirectionalLightProgram;
GLProgram* LightingManager::_DirectionalLightInstancedProgram;

GLProgram* LightingManager::_DirectionalLightVFilterProgram;
GLProgram* LightingManager::_DirectionalLightHFilterProgram;

float LightingManager::_ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = {0.1f, 0.3f, 0.6f, 1.0f};
GLUBO* LightingManager::_ShadowCascadeInfoBlock;
ShadowCascadeInfo LightingManager::_ShadowCascadeInfo;
unsigned LightingManager::_DirectionalShadowMapResolution = 512;
RenderTarget* LightingManager::_DirectionalLightShadowMapFilter;

GLTexture* LightingManager::_DLVSMVFilter;
GLTexture* LightingManager::_DLVSM;

#pragma endregion





CameraComponent* LightingManager::_TargetMainCamera;
Entity LightingManager::_TargetMainCameraEntity;


GLUBO* LightingManager::_PointLightBlock;
GLUBO* LightingManager::_SpotLightBlock;


PointLight LightingManager::_PointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLight LightingManager::_SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

bool LightingManager::_UpdateDirectionalLightBlock;
bool LightingManager::_UpdatePointLightBlock;
bool LightingManager::_UpdateSpotLightBlock;


PointLightShadowMap* LightingManager::_PointLightShadowMap;


GLProgram* LightingManager::_PointLightProgram;

GLProgram* LightingManager::_PointLightInstancedProgram;


void UniEngine::LightingManager::Init()
{
	_ShadowCascadeInfoBlock = new GLUBO();
	_ShadowCascadeInfoBlock->SetData(sizeof(ShadowCascadeInfo), NULL, GL_DYNAMIC_DRAW);
	_ShadowCascadeInfoBlock->SetBase(4);

#pragma region LightInfoBlocks
	_DirectionalLightBlock = new GLUBO();
	_PointLightBlock = new GLUBO();
	_SpotLightBlock = new GLUBO();
	size_t size = 16 + Default::ShaderIncludes::MaxDirectionalLightAmount * sizeof(DirectionalLight);
	_DirectionalLightBlock->SetData(size, NULL, GL_DYNAMIC_DRAW);
	_DirectionalLightBlock->SetBase(1);
	size = 16 + Default::ShaderIncludes::MaxPointLightAmount * sizeof(PointLight);
	_PointLightBlock->SetData(size, NULL, GL_DYNAMIC_DRAW);
	_PointLightBlock->SetBase(2);
	size = 16 + Default::ShaderIncludes::MaxSpotLightAmount * sizeof(SpotLight);
	_SpotLightBlock->SetData(size, NULL, GL_DYNAMIC_DRAW);
	_SpotLightBlock->SetBase(3);
#pragma endregion
#pragma region DirectionalLight
	_DirectionalLightShadowMap = new DirectionalLightShadowMap(Default::ShaderIncludes::MaxDirectionalLightAmount * Default::ShaderIncludes::ShadowCascadeAmount, _DirectionalShadowMapResolution, _DirectionalShadowMapResolution);

	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/DirectionalLightShadowMap.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
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
		FileIO::LoadFileAsString("Shaders/Geometry/VSMFilterHelper.geom");

	_DirectionalLightVFilterProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);

	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Fragment/GaussianHFilter.frag");

	_DirectionalLightHFilterProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);
	_DirectionalLightShadowMapFilter = new RenderTarget(_DirectionalShadowMapResolution, _DirectionalShadowMapResolution);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DLVSMVFilter = new GLTexture();
	_DLVSMVFilter->SetImage2DArray(0, GL_RGBA32F, _DirectionalShadowMapResolution, _DirectionalShadowMapResolution, Default::ShaderIncludes::MaxDirectionalLightAmount * Default::ShaderIncludes::ShadowCascadeAmount, 0, GL_RGBA, GL_FLOAT, NULL);
	_DLVSMVFilter->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DLVSMVFilter->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DLVSMVFilter->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DLVSMVFilter->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DLVSMVFilter->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
	_DirectionalLightShadowMapFilter->AttachTexture(_DLVSMVFilter, GL_COLOR_ATTACHMENT0);
	_DLVSM = new GLTexture();
	_DLVSM->SetImage2DArray(0, GL_RGBA32F, _DirectionalShadowMapResolution, _DirectionalShadowMapResolution, Default::ShaderIncludes::MaxDirectionalLightAmount * Default::ShaderIncludes::ShadowCascadeAmount, 0, GL_RGBA, GL_FLOAT, NULL);
	_DLVSM->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DLVSM->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DLVSM->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DLVSM->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DLVSM->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	_DirectionalLightShadowMapFilter->AttachTexture(_DLVSM, GL_COLOR_ATTACHMENT1);
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
	_UpdateDirectionalLightBlock = true;
	_UpdatePointLightBlock = true;
	_UpdateSpotLightBlock = true;

	GLTexture::Activate(GL_TEXTURE0);
	LightingManager::_DirectionalLightShadowMap->DepthMapArray()->Bind(GL_TEXTURE_2D_ARRAY);
	GLTexture::Activate(GL_TEXTURE1);
	LightingManager::_PointLightShadowMap->DepthCubeMapArray()->Bind(GL_TEXTURE_CUBE_MAP_ARRAY);
	GLTexture::BindDefault();
}

void UniEngine::LightingManager::Start()
{
	Camera* camera = _TargetMainCamera->Value;
	glm::vec3 cameraPos = EntityManager::GetComponentData<Position>(_TargetMainCameraEntity).value;
	auto worldBound = _World->GetBound();
	glm::vec3 maxBound = worldBound.Center + worldBound.Size;
	glm::vec3 minBound = worldBound.Center - worldBound.Size;



	if (_UpdateDirectionalLightBlock) {
		//1.	利用EntityManager找到场景内所有Light instance。
		auto directionLightsList = EntityManager::QuerySharedComponents<DirectionalLightComponent>();
		if (directionLightsList != nullptr) {
#pragma region Prepare DirectionalLight data
			size_t size = directionLightsList->size();
			for (int i = 0; i < size; i++) {
#pragma region DirectionalLight data collection
				DirectionalLightComponent* dlc = directionLightsList->at(i);
				Entity lightEntity = EntityManager::QueryEntities<DirectionalLightComponent>(dlc)->at(0);

				glm::quat rotation = EntityManager::GetComponentData<Rotation>(lightEntity).value;
				glm::vec3 lightDir = glm::normalize(rotation * glm::vec3(0, 0, 1));
#pragma region Light Frustum
				glm::vec3 p0 = ClosestPointOnLine(glm::vec3(maxBound.x, maxBound.y, maxBound.z), cameraPos, cameraPos + lightDir);
				glm::vec3 p7 = ClosestPointOnLine(glm::vec3(minBound.x, minBound.y, minBound.z), cameraPos, cameraPos + lightDir);

				float d0 = glm::distance(p0, p7);

				glm::vec3 p1 = ClosestPointOnLine(glm::vec3(maxBound.x, maxBound.y, minBound.z), cameraPos, cameraPos + lightDir);
				glm::vec3 p6 = ClosestPointOnLine(glm::vec3(minBound.x, minBound.y, maxBound.z), cameraPos, cameraPos + lightDir);

				float d1 = glm::distance(p1, p6);

				glm::vec3 p2 = ClosestPointOnLine(glm::vec3(maxBound.x, minBound.y, maxBound.z), cameraPos, cameraPos + lightDir);
				glm::vec3 p5 = ClosestPointOnLine(glm::vec3(minBound.x, maxBound.y, minBound.z), cameraPos, cameraPos + lightDir);

				float d2 = glm::distance(p2, p5);

				glm::vec3 p3 = ClosestPointOnLine(glm::vec3(maxBound.x, minBound.y, minBound.z), cameraPos, cameraPos + lightDir);
				glm::vec3 p4 = ClosestPointOnLine(glm::vec3(minBound.x, maxBound.y, maxBound.z), cameraPos, cameraPos + lightDir);

				float d3 = glm::distance(p3, p4);

				glm::vec3 center = ClosestPointOnLine(worldBound.Center, cameraPos, cameraPos + lightDir);
				float planeDistance = glm::max(glm::max(d0, d1), glm::max(d2, d3));
#pragma endregion
				_DirectionalLights[i].direction = glm::vec4(lightDir, 0.0f);
				
				_DirectionalLights[i].diffuse = glm::vec4(dlc->diffuse, 0);
				_DirectionalLights[i].specular = glm::vec4(dlc->specular, 0);
#pragma endregion
				for (int split = 0; split < Default::ShaderIncludes::ShadowCascadeAmount; split++) {
					//2.	计算Cascade Split所需信息
					float splitStart = camera->_Near;
					float splitEnd = camera->_Far;
					if (split != 0) splitStart = camera->_Near + (camera->_Far - camera->_Near) * _ShadowCascadeSplit[split - 1];
					if (split != Default::ShaderIncludes::ShadowCascadeAmount - 1) splitEnd = camera->_Near + (camera->_Far - camera->_Near) * _ShadowCascadeSplit[split];
					_ShadowCascadeInfo.SplitDistance[split] = splitEnd;
					glm::mat4 lightProjection, lightView;
					float max = 0;
#pragma region AABB
					/*
					glm::vec3 cornerPoints[8];
					camera->CalculateFrustumPoints(splitStart, splitEnd, cameraPos, cornerPoints);
					glm::vec3 cameraFrustumCenter = camera->_Front * ((splitEnd - splitStart) / 2.0f + splitStart) + cameraPos;

					lightView = glm::lookAt(cameraFrustumCenter - lightDir * (dlc->farPlane - dlc->nearPlane) / 2.0f, cameraFrustumCenter, glm::vec3(0.0, 1.0, 0.0));



					max = glm::max(max, glm::distance(cornerPoints[0], ClosestPointOnLine(cornerPoints[0], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[1], ClosestPointOnLine(cornerPoints[1], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[2], ClosestPointOnLine(cornerPoints[2], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[3], ClosestPointOnLine(cornerPoints[3], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[4], ClosestPointOnLine(cornerPoints[4], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[5], ClosestPointOnLine(cornerPoints[5], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[6], ClosestPointOnLine(cornerPoints[6], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					max = glm::max(max, glm::distance(cornerPoints[7], ClosestPointOnLine(cornerPoints[7], cameraFrustumCenter, cameraFrustumCenter - lightDir)));
					*/
#pragma endregion
#pragma region Sphere
					max = splitEnd;
#pragma endregion
					glm::vec3 lightPos = center - lightDir * planeDistance;
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
					if (split == Default::ShaderIncludes::ShadowCascadeAmount - 1) _DirectionalLights[i].ReservedParameters = glm::vec4(planeDistance, max, dlc->depthBias, dlc->normalOffset);

				}


			}
#pragma endregion
			_DirectionalLightBlock->SubData(0, 4, &size);
			if (size != 0) {
				_DirectionalLightBlock->SubData(16, size * sizeof(DirectionalLight), &_DirectionalLights[0]);
				_ShadowCascadeInfoBlock->SubData(0, sizeof(ShadowCascadeInfo), &_ShadowCascadeInfo);
			}
#pragma region Directional Light Shadowmap pass
			GLTexture::Activate(GL_TEXTURE0);
			LightingManager::_DirectionalLightShadowMap->DepthMapArray()->Bind(GL_TEXTURE_2D_ARRAY);
			_DirectionalLightShadowMap->Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			glClearTexSubImage(_DirectionalLightShadowMap->DepthMapArray()->ID(), 0, 0, 0, 0, _DirectionalShadowMapResolution, _DirectionalShadowMapResolution, size * 4, GL_RGBA, GL_FLOAT, NULL);
			for (int i = 0; i < size; i++) {
				_DirectionalLightProgram->Bind();
				_DirectionalLightProgram->SetInt("index", i);
				auto meshMaterials = EntityManager::QuerySharedComponents<MeshMaterialComponent>();
				if (meshMaterials != nullptr) {
					for (auto mmc : *meshMaterials) {
						if (mmc->_CastShadow) {
							auto entities = EntityManager::QueryEntities<MeshMaterialComponent>(mmc);
							for (auto j : *entities) {
								auto mesh = mmc->_Mesh;
								auto ltw = EntityManager::GetComponentData<LocalToWorld>(j).value;
								auto scale = EntityManager::GetComponentData<Scale>(j).value;
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
								glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
							}
						}
					}
				}

				_DirectionalLightInstancedProgram->Bind();
				_DirectionalLightInstancedProgram->SetInt("index", i);
				auto instancedMeshMaterials = EntityManager::QuerySharedComponents<InstancedMeshMaterialComponent>();
				if (instancedMeshMaterials != nullptr) {
					for (auto immc : *instancedMeshMaterials) {
						if (immc->_CastShadow) {
							auto entities = EntityManager::QueryEntities<InstancedMeshMaterialComponent>(immc);
							size_t count = immc->_Matrices->size();
							GLVBO* matricesBuffer = new GLVBO();
							matricesBuffer->SetData(count * sizeof(glm::mat4), &immc->_Matrices->at(0), GL_STATIC_DRAW);
							for (auto entity : *entities) {
								auto mesh = immc->_Mesh;
								_DirectionalLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(entity).value);
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
								glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, count);
								GLVAO::BindDefault();
							}
							delete matricesBuffer;
						}
					}
				}
			}
			//_DirectionalLightShadowMap->DepthMapArray()->GenerateMipMap(GL_TEXTURE_2D_ARRAY);
#pragma endregion
#pragma region VSM Filter Pass
			
			_DirectionalLightShadowMapFilter->Bind();
			glDisable(GL_DEPTH_TEST);
			Default::GLPrograms::ScreenVAO->Bind();
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			_DirectionalLightVFilterProgram->Bind();
			_DirectionalLightVFilterProgram->SetInt("textureMapArray", 0);
			for (int i = 0; i < size; i++) {
				_DirectionalLightVFilterProgram->SetInt("lightIndex", i);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}

			GLTexture::Activate(GL_TEXTURE0);
			_DLVSMVFilter->Bind(GL_TEXTURE_2D_ARRAY);
			glDrawBuffer(GL_COLOR_ATTACHMENT1);
			_DirectionalLightHFilterProgram->Bind();
			_DirectionalLightHFilterProgram->SetInt("textureMapArray", 0);
			for (int i = 0; i < size; i++) {
				_DirectionalLightHFilterProgram->SetInt("lightIndex", i);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}

			GLTexture::Activate(GL_TEXTURE0);
			_DLVSM->Bind(GL_TEXTURE_2D_ARRAY);
			
#pragma endregion

		}
	}





	

	if (_UpdatePointLightBlock) {
		auto pointLightsList = EntityManager::QuerySharedComponents<PointLightComponent>();
		if (pointLightsList != nullptr) {
#pragma region Prepare PointLight data
			size_t size = pointLightsList->size();
			for (int i = 0; i < size; i++) {
				PointLightComponent* plc = pointLightsList->at(i);
				Entity lightEntity = EntityManager::QueryEntities<PointLightComponent>(plc)->at(0);
				glm::vec3 position = EntityManager::GetComponentData<Position>(lightEntity).value;
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
#pragma endregion
			_PointLightBlock->SubData(0, 4, &size);
			if (size != 0)_PointLightBlock->SubData(16, size * sizeof(PointLight), &_PointLights[0]);
#pragma region PointLight Shadowmap Pass
			_PointLightShadowMap->Bind();
			glCullFace(GL_FRONT);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			for (int i = 0; i < size; i++) {
				_PointLightProgram->Bind();
				_PointLightProgram->SetInt("index", i);
				auto meshMaterials = EntityManager::QuerySharedComponents<MeshMaterialComponent>();
				for (auto mmc : *meshMaterials) {
					if (mmc->_CastShadow) {
						auto entities = EntityManager::QueryEntities<MeshMaterialComponent>(mmc);
						for (auto entity : *entities) {
							auto mesh = mmc->_Mesh;
							_PointLightProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(entity).value);
							mesh->Enable();
							mesh->VAO()->DisableAttributeArray(12);
							mesh->VAO()->DisableAttributeArray(13);
							mesh->VAO()->DisableAttributeArray(14);
							mesh->VAO()->DisableAttributeArray(15);
							glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
						}
					}
				}
				_PointLightInstancedProgram->Bind();
				_PointLightInstancedProgram->SetInt("index", i);
				auto instancedMeshMaterials = EntityManager::QuerySharedComponents<InstancedMeshMaterialComponent>();
				if (instancedMeshMaterials != nullptr) {
					for (auto immc : *instancedMeshMaterials) {
						if (immc->_CastShadow) {
							auto entities = EntityManager::QueryEntities<InstancedMeshMaterialComponent>(immc);
							size_t count = immc->_Matrices->size();
							GLVBO* matricesBuffer = new GLVBO();
							matricesBuffer->SetData(count * sizeof(glm::mat4), &immc->_Matrices->at(0), GL_STATIC_DRAW);
							for (auto entity : *entities) {
								auto mesh = immc->_Mesh;
								_PointLightInstancedProgram->SetFloat4x4("model", EntityManager::GetComponentData<LocalToWorld>(entity).value);
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
								glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, count);
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
}

void UniEngine::LightingManager::SetSplitRatio(float r1, float r2, float r3, float r4)
{
	_ShadowCascadeSplit[0] = r1;
	_ShadowCascadeSplit[1] = r2;
	_ShadowCascadeSplit[2] = r3;
	_ShadowCascadeSplit[3] = r4;
}

void UniEngine::LightingManager::SetDirectionalLightResolution(float value)
{
	_DirectionalShadowMapResolution = value;
}

glm::vec3 UniEngine::LightingManager::ClosestPointOnLine(glm::vec3 point, glm::vec3 a, glm::vec3 b)
{
	float LineLength = distance(a, b);
	glm::vec3 Vector = point - a;
	glm::vec3 LineDirection = (b - a) / LineLength;

	// Project Vector to LineDirection to get the distance of point from a
	float Distance = dot(Vector, LineDirection);
	return a + LineDirection * Distance;
}

void UniEngine::LightingManager::SetMainCamera(Entity entity)
{
	_TargetMainCameraEntity = entity;
	_TargetMainCamera = EntityManager::GetSharedComponent<CameraComponent>(entity);
}

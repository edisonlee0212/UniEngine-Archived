#include "LightingManager.h"
#include "EntityCollection.h"
#include "MeshMaterialComponent.h"


using namespace UniEngine;
GLUBO* LightingManager::_DirectionalLightBlock;
GLUBO* LightingManager::_PointLightBlock;
GLUBO* LightingManager::_SpotLightBlock;

DirectionalLight LightingManager::_DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
PointLight LightingManager::_PointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLight LightingManager::_SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

bool LightingManager::_UpdateDirectionalLightBlock;
bool LightingManager::_UpdatePointLightBlock;
bool LightingManager::_UpdateSpotLightBlock;

DirectionalLightShadowMap* LightingManager::_DirectionalLightShadowMap;
PointShadowMap* LightingManager::_PointLightShadowMap;

GLProgram* LightingManager::_DirectionalLightProgram;
GLProgram* LightingManager::_PointLightProgram;

void UniEngine::LightingManager::Init()
{

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

	MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
	dlmmc->_Mesh = Default::Primitives::Cylinder;
	dlmmc->_Material = Default::Materials::StandardMaterial;
	Scale scale;
	scale.value = glm::vec3(0.5f);


	DirectionalLightComponent* dlc = new DirectionalLightComponent();
	dlc->diffuse = glm::vec3(1.0f);
	dlc->specular = glm::vec3(0.5f);
	Entity* dle = _EntityCollection->CreateEntity();
	_EntityCollection->SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	_EntityCollection->SetFixedData<Scale>(dle, scale);
	_EntityCollection->SetSharedComponent<MeshMaterialComponent>(dle, dlmmc);


	MeshMaterialComponent* plmmc = new MeshMaterialComponent();
	plmmc->_Mesh = Default::Primitives::Sphere;
	plmmc->_Material = Default::Materials::StandardMaterial;
	scale.value = glm::vec3(0.5f);

	PointLightComponent* plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 70.0f;
	plc->diffuse = glm::vec3(5.0f);
	plc->specular = glm::vec3(5.0f);
	Entity* ple = _EntityCollection->CreateEntity();
	_EntityCollection->SetSharedComponent<PointLightComponent>(ple, plc);
	_EntityCollection->SetFixedData<Scale>(ple, scale);
	_EntityCollection->SetSharedComponent<MeshMaterialComponent>(ple, plmmc);

	_UpdateDirectionalLightBlock = true;
	_UpdatePointLightBlock = true;
	_UpdateSpotLightBlock = true;

	_DirectionalLightShadowMap = new DirectionalLightShadowMap(Default::ShaderIncludes::MaxDirectionalLightAmount);
	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Vertex/DirectionalLightShadowMap.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Fragment/DirectionalLightShadowMap.frag");
	_DirectionalLightProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
	);


	_PointLightShadowMap = new PointShadowMap();
	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Vertex/PointLightShadowMap.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Fragment/PointLightShadowMap.frag");
	std::string geomShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Geometry/PointLightShadowMap.geom");

	_PointLightProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode),
		new GLShader(ShaderType::Geometry, &geomShaderCode)
	);
}

void UniEngine::LightingManager::Start()
{
	if (_UpdateDirectionalLightBlock) {
		auto directionLightsList = _EntityCollection->QuerySharedComponents<DirectionalLightComponent>();

		size_t size = directionLightsList->size();
		for (int i = 0; i < size; i++) {
			SCOC* scoc = directionLightsList->at(i);
			Entity* lightEntity = scoc->second->second->at(0);
#pragma region ToBeRemoved
			Position p;
			p.value = glm::vec4(glm::vec3(0.0f, 20.0f * glm::abs(glm::sin(Time::WorldTime() / 2.0f)), -20.0f * glm::cos(Time::WorldTime() / 2.0f)), 0.0f);
			_EntityCollection->SetFixedData<Position>(lightEntity, p);
#pragma endregion
			glm::vec3 position = _EntityCollection->GetFixedData<Position>(lightEntity).value;
			_DirectionalLights[i].position = glm::vec4(position, 0);
			glm::vec3 lightTarget = glm::vec3(0.0f);
			_DirectionalLights[i].direction = glm::normalize(glm::vec4(lightTarget.x - _DirectionalLights[i].position.x, lightTarget.y - _DirectionalLights[i].position.y, lightTarget.z - _DirectionalLights[i].position.z, 0.0f));
			DirectionalLightComponent* dlc = dynamic_cast<DirectionalLightComponent*>(scoc->first);
			_DirectionalLights[i].diffuse = glm::vec4(dlc->diffuse, 0);
			_DirectionalLights[i].specular = glm::vec4(dlc->specular, 0);
			glm::mat4 lightProjection, lightView;

			float near_plane = 1.0f, far_plane = 50.0f;
			lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
			lightView = glm::lookAt(position, lightTarget, glm::vec3(0.0, 1.0, 0.0));
			_DirectionalLights[i].lightSpaceMatrix = lightProjection * lightView;
		}
		_DirectionalLightBlock->SubData(0, 4, &size);
		if (size != 0)_DirectionalLightBlock->SubData(16, size * sizeof(DirectionalLight), &_DirectionalLights[0]);
		
		for (int i = 0; i < size; i++) {
			_DirectionalLightShadowMap->Bind(0);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);

			_DirectionalLightProgram->Use();
			_DirectionalLightProgram->SetFloat4x4("lightSpaceMatrix", _DirectionalLights[i].lightSpaceMatrix);

			auto meshMaterials = _EntityCollection->QuerySharedComponents<MeshMaterialComponent>();
			for (auto i : *meshMaterials) {
				auto mmc = dynamic_cast<MeshMaterialComponent*>(i->first);
				auto entities = _EntityCollection->QueryEntities<MeshMaterialComponent>(mmc);
				for (auto j : *entities) {
					auto mesh = mmc->_Mesh;
					_DirectionalLightProgram->SetFloat4x4("model", _EntityCollection->GetFixedData<LocalToWorld>(j).value);
					mesh->VAO()->Bind();
					glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
				}
			}
		}
	}
	
	if (_UpdatePointLightBlock) {
		auto pointLightsList = _EntityCollection->QuerySharedComponents<PointLightComponent>();
		size_t size = pointLightsList->size();
		for (int i = 0; i < size; i++) {
			SCOC* scoc = pointLightsList->at(i);
			Entity* lightEntity = scoc->second->second->at(0);
#pragma region ToBeRemoved
			Position p;
			p.value = glm::vec4(glm::vec3(-20.0f * glm::cos(Time::WorldTime() / 2.0f), 20.0f * glm::abs(glm::sin(Time::WorldTime() / 2.0f)), 0.0f), 0.0f);
			_EntityCollection->SetFixedData<Position>(lightEntity, p);
#pragma endregion		
			glm::vec3 position = _EntityCollection->GetFixedData<Position>(lightEntity).value;
			_PointLights[i].position = glm::vec4(position, 0);
			PointLightComponent* plc = dynamic_cast<PointLightComponent*>(scoc->first);
			_PointLights[i].constantLinearQuadFarPlane.x = plc->constant;
			_PointLights[i].constantLinearQuadFarPlane.y = plc->linear;
			_PointLights[i].constantLinearQuadFarPlane.z = plc->quadratic;
			_PointLights[i].diffuse = glm::vec4(plc->diffuse, 0);
			_PointLights[i].specular = glm::vec4(plc->specular, 0);
			_PointLights[i].constantLinearQuadFarPlane.w = plc->farPlane;
		}
		_PointLightBlock->SubData(0, 4, &size);
		if (size != 0)_PointLightBlock->SubData(16, size * sizeof(PointLight), &_PointLights[0]);
		for (int i = 0; i < size; i++) {
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), _PointLightShadowMap->GetResolutionRatio(), 1.0f, _PointLights[i].constantLinearQuadFarPlane.w);
			glm::mat4 shadowTransforms[6];
			auto lightPos = glm::vec3(_PointLights[i].position);
			shadowTransforms[0] = shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			shadowTransforms[1] = shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			shadowTransforms[2] = shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			shadowTransforms[3] = shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
			shadowTransforms[4] = shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			shadowTransforms[5] = shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));

			_PointLightShadowMap->Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			_PointLightProgram->Use();
			_PointLightProgram->SetFloat4x4("shadowMatrices[0]", shadowTransforms[0]);
			_PointLightProgram->SetFloat4x4("shadowMatrices[1]", shadowTransforms[1]);
			_PointLightProgram->SetFloat4x4("shadowMatrices[2]", shadowTransforms[2]);
			_PointLightProgram->SetFloat4x4("shadowMatrices[3]", shadowTransforms[3]);
			_PointLightProgram->SetFloat4x4("shadowMatrices[4]", shadowTransforms[4]);
			_PointLightProgram->SetFloat4x4("shadowMatrices[5]", shadowTransforms[5]);
			_PointLightProgram->SetFloat("far_plane", _PointLights[i].constantLinearQuadFarPlane.w);
			_PointLightProgram->SetFloat3("lightPos", lightPos);

			auto meshMaterials = _EntityCollection->QuerySharedComponents<MeshMaterialComponent>();
			for (auto i : *meshMaterials) {
				auto entities = _EntityCollection->QueryEntities<MeshMaterialComponent>(dynamic_cast<MeshMaterialComponent*>(i->first));
				for (auto j : *entities) {
					auto mesh = dynamic_cast<MeshMaterialComponent*>(i->first)->_Mesh;
					_PointLightProgram->SetFloat4x4("model", _EntityCollection->GetFixedData<LocalToWorld>(j).value);
					mesh->VAO()->Bind();
					glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
				}
			}
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

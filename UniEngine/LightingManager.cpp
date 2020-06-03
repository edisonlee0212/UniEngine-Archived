#include "LightingManager.h"
#include "Default.h"
#include "EntityCollection.h"
#include "MeshMaterialComponent.h"


using namespace UniEngine;
GLUBO* LightingManager::_DirectionalLightBlock;
GLUBO* LightingManager::_PointLightBlock;
GLUBO* LightingManager::_SpotLightBlock;

std::vector<DirectionalLight> LightingManager::_DirectionalLights;
std::vector<PointLight> LightingManager::_PointLights;
std::vector<SpotLight> LightingManager::_SpotLights;

bool LightingManager::_UpdateDirectionalLightBlock;
bool LightingManager::_UpdatePointLightBlock;
bool LightingManager::_UpdateSpotLightBlock;

DirectionalShadowMap* LightingManager::_DirectionalLightShadowMap;
GLProgram* LightingManager::_DirectionalLightProgram;
glm::mat4 LightingManager::_LightSpaceMatrix;
glm::vec3 LightingManager::_LightPos;
glm::vec3 LightingManager::_LightDir;

void UniEngine::LightingManager::Init()
{
	_DirectionalLights = std::vector<DirectionalLight>();
	_PointLights = std::vector<PointLight>();
	_SpotLights = std::vector<SpotLight>();

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


	DirectionalLight dl = DirectionalLight();
	dl.direction = glm::vec4(0.0f, -1.0f, 0.5f, 0.0f);
	dl.ambient = glm::vec4(0.5f);
	dl.diffuse = glm::vec4(1.0f);
	dl.specular = glm::vec4(0.5f);
	_DirectionalLights.push_back(dl);

	PointLight pl = PointLight();
	pl.position = glm::vec4(0.7f, 0.2f, 2.0f, 0.0f);
	pl.ambient = glm::vec4(0.05f);
	pl.diffuse = glm::vec4(0.8f);
	pl.specular = glm::vec4(1.0f);
	pl.constant = 1.0f;
	pl.linear = 0.09f;
	pl.quadratic = 0.032f;

	//_PointLights.push_back(pl);
	pl.position = glm::vec4(2.3f, -3.3f, -4.0f, 0.0f);
	//_PointLights.push_back(pl);
	pl.position = glm::vec4(4.0f, 2.0f, -12.0f, 0.0f);
	//_PointLights.push_back(pl);
	pl.position = glm::vec4(0.0f, 0.0f, -3.0f, 0.0f);
	//_PointLights.push_back(pl);
	//Start();

	_UpdateDirectionalLightBlock = true;
	_UpdatePointLightBlock = true;
	_UpdateSpotLightBlock = true;

	_DirectionalLightShadowMap = new DirectionalShadowMap();
	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Vertex/DirectionalLightShadowMap.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Resources/Shaders/Fragment/DirectionalLightShadowMap.frag");
	_DirectionalLightProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode)
	);
}

void UniEngine::LightingManager::Start()
{
	if (_DirectionalLights.size() > 0) {
		auto dl = _DirectionalLights[0];
		glm::vec3 lightTarget = glm::vec3(0.0f);
		_LightPos = glm::vec3(0.0f, 20.0f * glm::abs(glm::sin(Time::WorldTime() / 2.0f)), -20.0f * glm::cos(Time::WorldTime() / 2.0f));
		dl.direction = glm::normalize(glm::vec4(lightTarget.x - _LightPos.x, lightTarget.y - _LightPos.y, lightTarget.z - _LightPos.z, 0.0f));
		_DirectionalLights[0] = dl;
		glm::mat4 lightProjection, lightView;

		_LightDir = glm::vec3(dl.direction);

		float near_plane = 1.0f, far_plane = 50.0f;
		lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
		lightView = glm::lookAt(_LightPos, lightTarget, glm::vec3(0.0, 1.0, 0.0));
		_LightSpaceMatrix = lightProjection * lightView;

		_DirectionalLightShadowMap->Bind();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);


		_DirectionalLightProgram->Use();
		_DirectionalLightProgram->SetFloat4x4("lightSpaceMatrix", _LightSpaceMatrix);

		auto meshMaterials = _EntityCollection->QuerySharedComponents<MeshMaterialComponent>();
		for (auto i : *meshMaterials) {
			auto entities = _EntityCollection->QueryEntities<MeshMaterialComponent>(dynamic_cast<MeshMaterialComponent*>(i->first));
			for (auto j : *entities) {
				auto mesh = dynamic_cast<MeshMaterialComponent*>(i->first)->_Mesh;
				_DirectionalLightProgram->SetFloat4x4("model", _EntityCollection->GetFixedData<LocalToWorld>(j).value);
				mesh->VAO()->Bind();
				glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
			}
		}

		glCullFace(GL_BACK);
	}
	if (_UpdateDirectionalLightBlock) {
		size_t size = _DirectionalLights.size();
		_DirectionalLightBlock->SubData(0, 4, &size);
		size = size * sizeof(DirectionalLight);
		if (size != 0)_DirectionalLightBlock->SubData(16, size, &_DirectionalLights[0]);
	}
	if (_UpdatePointLightBlock) {
		size_t size = _PointLights.size();
		_PointLightBlock->SubData(0, 4, &size);
		size = size * sizeof(PointLight);
		if (size != 0)_PointLightBlock->SubData(16, size, &_PointLights[0]);
	}
	if (_UpdateSpotLightBlock) {
		size_t size = _SpotLights.size();
		_SpotLightBlock->SubData(0, 4, &size);
		size = size * sizeof(SpotLight);
		if (size != 0)_SpotLightBlock->SubData(16, size, &_SpotLights[0]);
	}


}

#include "LightingManager.h"
#include "Default.h"
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
	dl.diffuse = glm::vec4(0.5f);
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
}

void UniEngine::LightingManager::Start()
{
	if (_DirectionalLights.size() > 0) {
		auto dl = _DirectionalLights[0];
		dl.direction = glm::vec4(0.0f, -glm::abs(glm::sin(Time::WorldTime() / 2.0f)), glm::cos(Time::WorldTime() / 2.0f), 0.0f);
		_DirectionalLights[0] = dl;
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

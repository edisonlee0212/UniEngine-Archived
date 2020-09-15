#include "pch.h"
#include "Material.h"
using namespace UniEngine;

void UniEngine::Material::SetMaterialProperty(std::string name, float value)
{
	_FloatPropertyList[name] = value;
}

void UniEngine::Material::SetMaterialProperty(std::string name, glm::mat4 value)
{
	_Float4x4PropertyList[name] = value;
}

std::vector<Texture2D*>* UniEngine::Material::Textures2Ds()
{
	return &_Texture2Ds;
}

std::vector<Cubemap*>* UniEngine::Material::Cubemaps()
{
	return &_Cubemaps;
}

std::vector<GLProgram*>* UniEngine::Material::Programs()
{
	return &_Programs;
}

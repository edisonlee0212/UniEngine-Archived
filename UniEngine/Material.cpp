#include "pch.h"
#include "Material.h"
using namespace UniEngine;

void Material::SetMaterialProperty(std::string name, float value)
{
	_FloatPropertyList[name] = value;
}

void Material::SetMaterialProperty(std::string name, glm::mat4 value)
{
	_Float4x4PropertyList[name] = value;
}

std::vector<Texture2D*>* Material::Textures2Ds()
{
	return &_Texture2Ds;
}

std::vector<Cubemap*>* Material::Cubemaps()
{
	return &_Cubemaps;
}

std::vector<GLProgram*>* Material::Programs()
{
	return &_Programs;
}

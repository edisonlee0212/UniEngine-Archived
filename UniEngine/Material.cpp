#include "pch.h"
#include "Material.h"
using namespace UniEngine;

void UniEngine::Material::SetMaterialProperty(std::string name, float value)
{
	for(auto& property : _FloatPropertyList)
	{
		if(property.Name._Equal(name))
		{
			property.Value = value;
			return;
		}
	}
	_FloatPropertyList.emplace_back(name, value);
}

void UniEngine::Material::SetMaterialProperty(std::string name, glm::mat4 value)
{
	for (auto& property : _Float4x4PropertyList)
	{
		if (property.Name._Equal(name))
		{
			property.Value = value;
			return;
		}
	}
	_Float4x4PropertyList.emplace_back(name, value);
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

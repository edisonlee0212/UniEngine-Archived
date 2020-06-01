#include "Material.h"
using namespace UniEngine;

float UniEngine::Material::Shininess()
{
	return _Shininess;
}

void UniEngine::Material::SetShininess(float value)
{
	_Shininess = value;
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

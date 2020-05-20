#include "Material.h"
using namespace UniEngine;

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

#include "Material.h"
using namespace UniEngine;
std::vector<GLTexture*>* UniEngine::Material::Textures()
{
	return &_Textures;
}

std::vector<GLProgram*>* UniEngine::Material::Programs()
{
	return &_Programs;
}

#include "pch.h"
#include "Texture2D.h"
#include <stb_image.h>
#include "ResourceManager.h"
using namespace UniEngine;


UniEngine::Texture2D::Texture2D()
{
	Name = "New Texture";
}

std::shared_ptr<GLTexture2D> UniEngine::Texture2D::Texture() const
{
	return _Texture;
}

std::string UniEngine::Texture2D::Path() const
{
	return _Path;
}

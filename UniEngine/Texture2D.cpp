#include "pch.h"
#include "Texture2D.h"
#include <stb_image.h>
#include "AssetManager.h"
using namespace UniEngine;


UniEngine::Texture2D::Texture2D(TextureType type) : _Type(type)
{
	Name = "New Texture";
}

std::unique_ptr<GLTexture2D>& UniEngine::Texture2D::Texture()
{
	return _Texture;
}

TextureType UniEngine::Texture2D::Type()
{
	return _Type;
}

std::string UniEngine::Texture2D::Path()
{
	return _Path;
}

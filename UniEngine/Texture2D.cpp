#include "pch.h"
#include "Texture2D.h"
#include <stb_image.h>

using namespace UniEngine;
UniEngine::Texture2D::Texture2D(TextureType type) : _Type(type)
{
    _Texture = nullptr;
}

UniEngine::Texture2D::~Texture2D()
{
    if(_Texture != nullptr) delete _Texture;
}

GLTexture2D* UniEngine::Texture2D::Texture()
{
	return _Texture;
}

TextureType UniEngine::Texture2D::Type()
{
	return _Type;
}

void UniEngine::Texture2D::LoadTexture(std::string path, const std::string& directory)
{
    _Path = path;
    std::string filename = path;
    if (!directory._Equal(""))
        filename = directory + '/' + filename;

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RED;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        _Texture = new GLTexture2D(1, GL_RGBA16, width, height);
        _Texture->SetData(0, format, GL_UNSIGNED_BYTE, data);
        _Texture->GenerateMipMap();

        _Texture->SetInt(GL_TEXTURE_WRAP_S, GL_REPEAT);
        _Texture->SetInt(GL_TEXTURE_WRAP_T, GL_REPEAT);
        _Texture->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        _Texture->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        Debug::Log("Texture failed to load at path: " + filename);
        stbi_image_free(data);
    }
}

std::string UniEngine::Texture2D::Path()
{
    return _Path;
}

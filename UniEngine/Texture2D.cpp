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
        GLenum iformat = GL_R8;
        if (nrComponents == 2) {
            format = GL_RG;
            iformat = GL_RG8;
        }
        else if (nrComponents == 3) {
            format = GL_RGB;
            iformat = GL_RGB8;
        }
        else if (nrComponents == 4) {
            format = GL_RGBA;
            iformat = GL_RGBA8;
        }
        _Texture = new GLTexture2D(1, iformat, width, height, false);
        _Texture->SetData(0, iformat, format, GL_UNSIGNED_BYTE, data);
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

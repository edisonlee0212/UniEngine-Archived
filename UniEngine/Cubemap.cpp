#include "pch.h"
#include "Cubemap.h"
#include <stb_image.h>

UniEngine::Cubemap::Cubemap()
{
	_Texture = nullptr;
}

UniEngine::Cubemap::~Cubemap()
{
    if (_Texture != nullptr) delete _Texture;
}

void UniEngine::Cubemap::LoadCubeMap(std::vector<std::string> paths)
{
	_Paths = paths;
    int width, height, nrComponents;
    auto size = _Paths.size();
    if (size != 6) {
        Debug::Error("Texture::LoadCubeMap: Size error.");
        return;
    }
    delete _Texture;
    unsigned char* temp = stbi_load(_Paths[0].c_str(), &width, &height, &nrComponents, 0);
    stbi_image_free(temp);
    _Texture = new GLTextureCubeMap(1, GL_RGB, width, height, false);
    for (int i = 0; i < size; i++)
    {
        unsigned char* data = stbi_load(_Paths[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum iformat = GL_R8;
            GLenum format = GL_RED;
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
        	
            _Texture->SetData((CubeMapIndex)i, 0, iformat, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << _Paths[i] << std::endl;
            stbi_image_free(data);
        }
    }
    _Texture->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    _Texture->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    _Texture->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _Texture->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    _Texture->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

std::vector<std::string> UniEngine::Cubemap::Paths()
{
	return _Paths;
}

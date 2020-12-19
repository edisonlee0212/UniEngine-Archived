#include "pch.h"
#include "Texture2D.h"
#include <stb_image.h>
#include "ResourceManager.h"
using namespace UniEngine;

Texture2D::Texture2D(TextureType type)
{
	_Type = type;
}

void Texture2D::SetType(TextureType type)
{
	_Type = type;
}

TextureType Texture2D::GetType() const
{
	return _Type;
}

glm::vec2 Texture2D::GetResolution() const
{
	return { _Texture->_Width, _Texture->_Height };
}

void Texture2D::StoreToPng(const std::string& path, int resizeX, int resizeY) const
{
	const auto resolutionX = _Texture->_Width;
	const auto resolutionY = _Texture->_Height;
	std::vector<float> dst;
	dst.resize(resolutionX * resolutionY * 3);
	_Texture->Bind(0);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, (void*)dst.data());
	std::vector<uint8_t> pixels;
	if (resizeX > 0 && resizeY > 0)
	{
		std::vector<float> res;
		res.resize(resizeX * resizeY * 3);
		stbir_resize_float(dst.data(), resolutionX, resolutionY, 0,
			res.data(), resizeX, resizeY, 0, 3);
		pixels.resize(resizeX * resizeY * 3);
		for (int i = 0; i < resizeX * resizeY; i++)
		{
			pixels[i * 3] = glm::clamp<int>(int(255.99f * res[i * 3]), 0, 255);
			pixels[i * 3 + 1] = glm::clamp<int>(int(255.99f * res[i * 3 + 1]), 0, 255);
			pixels[i * 3 + 2] = glm::clamp<int>(int(255.99f * res[i * 3 + 2]), 0, 255);
		}
		stbi_flip_vertically_on_write(true);
		stbi_write_png(path.c_str(), resizeX, resizeY, 3, pixels.data(), resizeX * 3);
	}
	else {
		pixels.resize(resolutionX * resolutionY * 3);
		for (int i = 0; i < resolutionX * resolutionY; i++)
		{
			pixels[i * 3] = glm::clamp<int>(int(255.99f * dst[i * 3]), 0, 255);
			pixels[i * 3 + 1] = glm::clamp<int>(int(255.99f * dst[i * 3 + 1]), 0, 255);
			pixels[i * 3 + 2] = glm::clamp<int>(int(255.99f * dst[i * 3 + 2]), 0, 255);
		}
		stbi_flip_vertically_on_write(true);
		stbi_write_png(path.c_str(), resolutionX, resolutionY, 3, pixels.data(), resolutionX * 3);
	}
}

void Texture2D::StoreToJpg(const std::string& path, int resizeX, int resizeY) const
{
	const auto resolutionX = _Texture->_Width;
	const auto resolutionY = _Texture->_Height;
	std::vector<float> dst;
	dst.resize(resolutionX * resolutionY * 3);
	_Texture->Bind(0);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, (void*)dst.data());
	std::vector<uint8_t> pixels;
	if (resizeX > 0 && resizeY > 0)
	{
		std::vector<float> res;
		res.resize(resizeX * resizeY * 3);
		stbir_resize_float(dst.data(), resolutionX, resolutionY, 0,
			res.data(), resizeX, resizeY, 0, 3);
		pixels.resize(resizeX * resizeY * 3);
		for (int i = 0; i < resizeX * resizeY; i++)
		{
			pixels[i * 3] = glm::clamp<int>(int(255.99f * res[i * 3]), 0, 255);
			pixels[i * 3 + 1] = glm::clamp<int>(int(255.99f * res[i * 3 + 1]), 0, 255);
			pixels[i * 3 + 2] = glm::clamp<int>(int(255.99f * res[i * 3 + 2]), 0, 255);
		}
		stbi_flip_vertically_on_write(true);
		stbi_write_jpg(path.c_str(), resizeX, resizeY, 3, pixels.data(), 100);
	}
	else {
		pixels.resize(resolutionX * resolutionY * 3);
		for (int i = 0; i < resolutionX * resolutionY; i++)
		{
			pixels[i * 3] = glm::clamp<int>(int(255.99f * dst[i * 3]), 0, 255);
			pixels[i * 3 + 1] = glm::clamp<int>(int(255.99f * dst[i * 3 + 1]), 0, 255);
			pixels[i * 3 + 2] = glm::clamp<int>(int(255.99f * dst[i * 3 + 2]), 0, 255);
		}
		stbi_flip_vertically_on_write(true);
		stbi_write_jpg(path.c_str(), resolutionX, resolutionY, 3, pixels.data(), 100);
	}
}

std::shared_ptr<GLTexture2D> UniEngine::Texture2D::Texture() const
{
	return _Texture;
}

std::string UniEngine::Texture2D::Path() const
{
	return _Path;
}

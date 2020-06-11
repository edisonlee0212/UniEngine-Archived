#include "pch.h"
#include "GLTexture.h"
using namespace UniEngine;

void UniEngine::GLTexture::BindDefault()
{
	glActiveTexture(GL_TEXTURE0);
}
UniEngine::GLTexture::GLTexture()
{
	glGenTextures(1, &_ID);
}

UniEngine::GLTexture::~GLTexture()
{
	glDeleteTextures(1, &_ID);
}

void UniEngine::GLTexture::SetImage1D(GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* data)
{
	Bind(GL_TEXTURE_1D);
	glTexImage1D(GL_TEXTURE_1D, level, internalformat, width, border, format, type, data);
}

void UniEngine::GLTexture::SetImage2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)
{
	Bind(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, border, format, type, data);
}

void UniEngine::GLTexture::SetImage3D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* data)
{
	Bind(GL_TEXTURE_3D);
	glTexImage3D(GL_TEXTURE_3D, level, internalformat, width, height, depth, border, format, type, data);
}

void UniEngine::GLTexture::SetCubeMap(CubeMapIndex index, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)
{
	Bind(GL_TEXTURE_CUBE_MAP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (int)index, level, internalformat, width, height, border, format, type, data);
}

void UniEngine::GLTexture::SetIntParameter(GLenum target, GLenum pname, GLint param)
{
	Bind(target);
	glTexParameteri(target, pname, param);
}


void UniEngine::GLTexture::SetImage2DArray(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei layer, GLint border, GLenum format, GLenum type, const void* data)
{
	Bind(GL_TEXTURE_2D_ARRAY);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, level, internalformat, width, height, layer, border, format, type, data);
}

void UniEngine::GLTexture::SetCubeMapArray(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei layer, GLint border, GLenum format, GLenum type, const void* data)
{
	Bind(GL_TEXTURE_CUBE_MAP_ARRAY);
	glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, level, internalformat, width, height, layer * 6, border, format, type, data);
}

void UniEngine::GLTexture::SetFloatParameter(GLenum target, GLenum pname, GLfloat param)
{
	Bind(target);
	glTexParameterf(target, pname, param);
}

void UniEngine::GLTexture::SetFloat4Parameter(GLenum target, GLenum pname, GLfloat* param)
{
	Bind(target);
	glTexParameterfv(target, pname, param);
}

void UniEngine::GLTexture::Activate(GLenum texture)
{
	glActiveTexture(texture);
}

void UniEngine::GLTexture::Bind(GLenum target)
{
	if (_ID == _CurrentBinding) return;
	glBindTexture(target, _ID);
	_CurrentBinding = _ID;
}

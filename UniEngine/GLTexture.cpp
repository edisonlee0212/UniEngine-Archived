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
	glBindTexture(GL_TEXTURE_1D, _ID);
	glTexImage1D(GL_TEXTURE_1D, level, internalformat, width, border, format, type, data);
}

void UniEngine::GLTexture::SetImage2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)
{
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, border, format, type, data);
}

void UniEngine::GLTexture::SetImage3D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* data)
{
	glBindTexture(GL_TEXTURE_3D, _ID);
	glTexImage3D(GL_TEXTURE_3D, level, internalformat, width, height, depth, border, format, type, data);
}

void UniEngine::GLTexture::SetCubeMap(CubeMapIndex index, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (int)index, level, internalformat, width, height, border, format, type, data);
}

void UniEngine::GLTexture::SetIntParameter(GLenum target, GLenum pname, GLint param)
{
	glBindTexture(target, _ID);
	glTexParameteri(target, pname, param);
}

void UniEngine::GLTexture::SetFloatParameter(GLenum target, GLenum pname, GLfloat param)
{
	glBindTexture(target, _ID);
	glTexParameterf(target, pname, param);
}

void UniEngine::GLTexture::SetFloat4Parameter(GLenum target, GLenum pname, GLfloat* param)
{
	glBindTexture(target, _ID);
	glTexParameterfv(target, pname, param);
}

void UniEngine::GLTexture::Activate(GLenum texture)
{
	glActiveTexture(texture);
}

void UniEngine::GLTexture::Bind(GLenum target)
{
	glBindTexture(target, _ID);
}

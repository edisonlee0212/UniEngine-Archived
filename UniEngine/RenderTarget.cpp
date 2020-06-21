#include "pch.h"
#include "RenderTarget.h"
#include "RenderManager.h"
using namespace UniEngine;

UniEngine::RenderTarget::RenderTarget()
{
	_Bound = false;
	_FrameBuffer = new GLFrameBuffer();
}

glm::vec2 UniEngine::RenderTarget::GetResolution()
{
	return glm::vec2(_ResolutionX, _ResolutionY);
}

float UniEngine::RenderTarget::GetResolutionRatio()
{
	if (_ResolutionX == 0 || _ResolutionY == 0) return 0;
	return (float)_ResolutionX / (float)_ResolutionY;
}

void UniEngine::RenderTarget::AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTextureLayer(texture, attachPoint, layer);
}

void UniEngine::RenderTarget::AttachTexture2D(GLTexture* texture, GLenum attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTexture2D(texture, attachPoint);
}

void UniEngine::RenderTarget::AttachTexture(GLTexture* texture, GLenum attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTexture(texture, attachPoint);
}

void UniEngine::RenderTarget::AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLenum attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachRenderBuffer(renderBuffer, attachPoint);
}

GLTexture* UniEngine::RenderTarget::SetTexture2D(GLenum attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type, const void* data)
{
	GLTexture* retVal = new GLTexture();
	retVal->SetImage2D(level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	AttachTexture2D(retVal, attachPoint);
	return retVal;
}

GLTexture* UniEngine::RenderTarget::SetCubeMap(GLenum attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type, const void* data)
{
	GLTexture* retVal = new GLTexture();
	retVal->SetCubeMap((CubeMapIndex)0, level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	retVal->SetCubeMap((CubeMapIndex)1, level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	retVal->SetCubeMap((CubeMapIndex)2, level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	retVal->SetCubeMap((CubeMapIndex)3, level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	retVal->SetCubeMap((CubeMapIndex)4, level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	retVal->SetCubeMap((CubeMapIndex)5, level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	AttachTexture(retVal, attachPoint);
	return retVal;
}

GLRenderBuffer* UniEngine::RenderTarget::SetRenderBuffer(GLenum attachPoint, GLenum internalformat​)
{
	GLRenderBuffer* retVal = new GLRenderBuffer();
	retVal->AllocateStorage(internalformat​, _ResolutionX, _ResolutionY);
	AttachRenderBuffer(retVal, attachPoint);
	return retVal;
}

void UniEngine::RenderTarget::Bind()
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->Bind();
	if (!_FrameBuffer->Color()) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glViewport(0, 0, _ResolutionX, _ResolutionY);
	RenderManager::_CurrentRenderTarget = this;
}

void UniEngine::RenderTarget::BindDefault()
{
	GLFrameBuffer::BindDefault();
}

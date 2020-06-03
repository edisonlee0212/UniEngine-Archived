#include "RenderTarget.h"
#include "Debug.h"
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

void UniEngine::RenderTarget::AttachTexture2D(GLTexture* texture, GLint attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTexture2D(texture, attachPoint);
}

void UniEngine::RenderTarget::AttachTexture(GLTexture* texture, GLint attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTexture(texture, attachPoint);
}

void UniEngine::RenderTarget::AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLint attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachRenderBuffer(renderBuffer, attachPoint);
}

GLTexture* UniEngine::RenderTarget::SetTexture2D(GLint attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type, const void* data)
{
	GLTexture* retVal = new GLTexture();
	retVal->SetImage2D(level, internalformat, _ResolutionX, _ResolutionY, border, format, type, data);
	AttachTexture2D(retVal, attachPoint);
	return retVal;
}

GLTexture* UniEngine::RenderTarget::SetCubeMap(GLint attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type, const void* data)
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

GLRenderBuffer* UniEngine::RenderTarget::SetRenderBuffer(GLint attachPoint, GLenum internalformat​)
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
	glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer->ID());
	if (!_FrameBuffer->Color()) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glViewport(0, 0, _ResolutionX, _ResolutionY);
	RenderManager::_CurrentRenderTarget = this;
}

void UniEngine::RenderTarget::BindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

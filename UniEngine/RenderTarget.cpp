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

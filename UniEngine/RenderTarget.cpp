#include "pch.h"
#include "RenderTarget.h"
#include "RenderManager.h"
using namespace UniEngine;

UniEngine::RenderTarget::RenderTarget()
{
	_Bound = false;
	_FrameBuffer = new GLFrameBuffer();
	_ResolutionX = 0;
	_ResolutionY = 0;
}

UniEngine::RenderTarget::RenderTarget(size_t width, size_t height)
{
	_Bound = false;
	_FrameBuffer = new GLFrameBuffer();
	_ResolutionX = width;
	_ResolutionY = height;
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

void UniEngine::RenderTarget::Bind()
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	
	if (!_FrameBuffer->Color()) {
		glNamedFramebufferDrawBuffer(_FrameBuffer->ID(), GL_NONE);
		glNamedFramebufferDrawBuffer(_FrameBuffer->ID(), GL_NONE);
	}
	_FrameBuffer->Bind();
	auto status = glCheckNamedFramebufferStatus(_FrameBuffer->ID(), GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glViewport(0, 0, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY);
}

void UniEngine::RenderTarget::Clear()
{
	_FrameBuffer->Clear();
}

void UniEngine::RenderTarget::BindDefault()
{
	GLFrameBuffer::BindDefault();
}

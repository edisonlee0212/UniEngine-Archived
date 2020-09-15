#include "pch.h"
#include "RenderTarget.h"
#include "RenderManager.h"
using namespace UniEngine;

RenderTarget::RenderTarget()
{
	_Bound = false;
	_FrameBuffer = new GLFrameBuffer();
	_ResolutionX = 0;
	_ResolutionY = 0;
}

RenderTarget::RenderTarget(size_t width, size_t height)
{
	_Bound = false;
	_FrameBuffer = new GLFrameBuffer();
	_ResolutionX = width;
	_ResolutionY = height;
}

glm::vec2 RenderTarget::GetResolution()
{
	return glm::vec2(_ResolutionX, _ResolutionY);
}

float RenderTarget::GetResolutionRatio()
{
	if (_ResolutionX == 0 || _ResolutionY == 0) return 0;
	return static_cast<float>(_ResolutionX) / static_cast<float>(_ResolutionY);
}

void RenderTarget::AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer)
{
	if (_Bound)
	{
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTextureLayer(texture, attachPoint, layer);
}

void RenderTarget::AttachTexture(GLTexture* texture, GLenum attachPoint)
{
	if (_Bound)
	{
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTexture(texture, attachPoint);
}

void RenderTarget::AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLenum attachPoint)
{
	if (_Bound)
	{
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachRenderBuffer(renderBuffer, attachPoint);
}

void RenderTarget::Bind()
{
	if (_Bound)
	{
		Debug::Error("Error");
		return;
	}

	if (!_FrameBuffer->Color())
	{
		glNamedFramebufferDrawBuffer(_FrameBuffer->ID(), GL_NONE);
		glNamedFramebufferDrawBuffer(_FrameBuffer->ID(), GL_NONE);
	}
	_FrameBuffer->Bind();
	auto status = glCheckNamedFramebufferStatus(_FrameBuffer->ID(), GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glViewport(0, 0, static_cast<GLsizei>(_ResolutionX), static_cast<GLsizei>(_ResolutionY));
}

void RenderTarget::Clear()
{
	_FrameBuffer->Clear();
}

void RenderTarget::BindDefault()
{
	GLFrameBuffer::BindDefault();
}

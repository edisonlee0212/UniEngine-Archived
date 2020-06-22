#include "pch.h"
#include "GLFrameBuffer.h"

GLuint UniEngine::GLFrameBuffer::_CurrentBinding = 0;

void UniEngine::GLFrameBuffer::Bind()
{
	if (_CurrentBinding == _ID) return;
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
	_CurrentBinding = _ID;
}

void UniEngine::GLFrameBuffer::BindDefault()
{
	if (_CurrentBinding == 0) return;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_CurrentBinding = 0;
}

UniEngine::GLFrameBuffer::GLFrameBuffer()
{
	_Color = false;
	_Depth = false;
	_Stencil = false;
	glGenFramebuffers(1, &_ID);
}

UniEngine::GLFrameBuffer::~GLFrameBuffer()
{
	BindDefault();
	glDeleteFramebuffers(1, &_ID);
}

bool UniEngine::GLFrameBuffer::Color()
{
	return _Color;
}

bool UniEngine::GLFrameBuffer::Depth()
{
	return _Depth;
}

bool UniEngine::GLFrameBuffer::Stencil()
{
	return _Stencil;
}

void UniEngine::GLFrameBuffer::AttachRenderBuffer(GLRenderBuffer* buffer, GLenum attachPoint)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		_Depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		_Stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		_Depth = true;
		_Stencil = true;
		break;
	default:
		_Color = true;
		break;
	}
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachPoint, GL_RENDERBUFFER, buffer->ID());
}

void UniEngine::GLFrameBuffer::AttachTexture2D(GLTexture* texture, GLenum attachPoint)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		_Depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		_Stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		_Depth = true;
		_Stencil = true;
		break;
	default:
		_Color = true;
		break;
	}
	Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachPoint, GL_TEXTURE_2D, texture->ID(), 0);
}

void UniEngine::GLFrameBuffer::AttachTexture(GLTexture* texture, GLenum attachPoint)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		_Depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		_Stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		_Depth = true;
		_Stencil = true;
		break;
	default:
		_Color = true;
		break;
	}
	Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, attachPoint, texture->ID(), 0);
}

void UniEngine::GLFrameBuffer::AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		_Depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		_Stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		_Depth = true;
		_Stencil = true;
		break;
	default:
		_Color = true;
		break;
	}
	Bind();
	glFramebufferTextureLayer(GL_FRAMEBUFFER, attachPoint, texture->ID(), 0, layer);
}

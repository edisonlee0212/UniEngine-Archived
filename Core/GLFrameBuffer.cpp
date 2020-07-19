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
	glCreateFramebuffers(1, &_ID);
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
	glNamedFramebufferRenderbuffer(_ID, attachPoint, GL_RENDERBUFFER, buffer->ID());
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
	glNamedFramebufferTexture(_ID, attachPoint, texture->ID(), 0);
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
	glNamedFramebufferTextureLayer(_ID, attachPoint, texture->ID(), 0, layer);
}

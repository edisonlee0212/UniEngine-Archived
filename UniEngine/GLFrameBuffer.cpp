#include "GLFrameBuffer.h"

UniEngine::GLFrameBuffer::GLFrameBuffer()
{
	_Color = false;
	_Depth = false;
	_Stencil = false;
	glGenFramebuffers(1, &_ID);
}

UniEngine::GLFrameBuffer::~GLFrameBuffer()
{
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

void UniEngine::GLFrameBuffer::AttachRenderBuffer(GLRenderBuffer* buffer, GLint attachPoint)
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
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachPoint, GL_RENDERBUFFER, buffer->ID());
}

void UniEngine::GLFrameBuffer::AttachTexture(GLTexture* texture, GLint attachPoint)
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
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachPoint, GL_TEXTURE_2D, texture->ID(), 0);
}

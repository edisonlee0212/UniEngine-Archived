#include "pch.h"
#include "GLFrameBuffer.h"


inline void UniEngine::GLFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

inline void UniEngine::GLFrameBuffer::BindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline UniEngine::GLFrameBuffer::GLFrameBuffer()
{
	_Color = false;
	_Depth = false;
	_Stencil = false;
	glCreateFramebuffers(1, &_ID);
}

inline UniEngine::GLFrameBuffer::~GLFrameBuffer()
{
	BindDefault();
	glDeleteFramebuffers(1, &_ID);
}

inline bool UniEngine::GLFrameBuffer::Color()
{
	return _Color;
}

inline bool UniEngine::GLFrameBuffer::Depth()
{
	return _Depth;
}

inline bool UniEngine::GLFrameBuffer::Stencil()
{
	return _Stencil;
}

inline void UniEngine::GLFrameBuffer::AttachRenderBuffer(GLRenderBuffer* buffer, GLenum attachPoint)
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

inline void UniEngine::GLFrameBuffer::AttachTexture(GLTexture* texture, GLenum attachPoint)
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

inline void UniEngine::GLFrameBuffer::AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer)
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

void UniEngine::GLFrameBuffer::Clear()
{
	Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
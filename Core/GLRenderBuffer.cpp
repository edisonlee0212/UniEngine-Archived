#include "pch.h"
#include "GLRenderBuffer.h"

GLuint UniEngine::GLRenderBuffer::_CurrentBinding = 0;

void UniEngine::GLRenderBuffer::Bind()
{
	if (_CurrentBinding == _ID) return;
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
	_CurrentBinding = _ID;
}

void UniEngine::GLRenderBuffer::BindDefault()
{
	if (_CurrentBinding == 0) return;
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	_CurrentBinding = 0;
}

UniEngine::GLRenderBuffer::GLRenderBuffer()
{
	glGenRenderbuffers(1, &_ID);
}

UniEngine::GLRenderBuffer::~GLRenderBuffer()
{
	glDeleteRenderbuffers(1, &_ID);
}

void UniEngine::GLRenderBuffer::AllocateStorage(GLenum internalformat​, GLsizei width​, GLsizei height)
{
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, internalformat​, width​, height);
}

void UniEngine::GLRenderBuffer::Attach(GLenum attachment, GLuint frameBufferID)
{
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, _ID);
}

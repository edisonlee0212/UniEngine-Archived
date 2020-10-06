#include "pch.h"
#include "GLRenderBuffer.h"


inline void UniEngine::GLRenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
}

inline void UniEngine::GLRenderBuffer::BindDefault()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

inline UniEngine::GLRenderBuffer::GLRenderBuffer()
{
	glGenRenderbuffers(1, &_ID);
}

inline UniEngine::GLRenderBuffer::~GLRenderBuffer()
{
	BindDefault();
	glDeleteRenderbuffers(1, &_ID);
}

inline void UniEngine::GLRenderBuffer::AllocateStorage(GLenum internalformat​, GLsizei width​, GLsizei height)
{
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, internalformat​, width​, height);
}

inline void UniEngine::GLRenderBuffer::Attach(GLenum attachment, GLuint frameBufferID)
{
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, _ID);
}

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

inline void UniEngine::GLRenderBuffer::AllocateStorage(GLenum internalFormat​, GLsizei width​, GLsizei height) 
{
	Bind();
	glNamedRenderbufferStorage(_ID, internalFormat​, width​, height);
}
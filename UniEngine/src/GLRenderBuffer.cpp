#include "pch.h"
#include "GLRenderBuffer.h"


inline void UniEngine::GLRenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

inline void UniEngine::GLRenderBuffer::BindDefault()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

inline UniEngine::GLRenderBuffer::GLRenderBuffer()
{
	glGenRenderbuffers(1, &m_id);
}

inline UniEngine::GLRenderBuffer::~GLRenderBuffer()
{
	BindDefault();
	glDeleteRenderbuffers(1, &m_id);
}

inline void UniEngine::GLRenderBuffer::AllocateStorage(GLenum internalFormat​, GLsizei width​, GLsizei height) 
{
	Bind();
	glNamedRenderbufferStorage(m_id, internalFormat​, width​, height);
}
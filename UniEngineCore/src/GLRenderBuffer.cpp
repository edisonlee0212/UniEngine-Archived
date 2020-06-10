#include "GLRenderBuffer.h"

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
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
	glRenderbufferStorage(GL_RENDERBUFFER, internalformat​, width​, height);
}

void UniEngine::GLRenderBuffer::Attach(GLenum attachment, GLuint frameBufferID)
{
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, _ID);
}

#include "pch.h"
#include "GLFrameBuffer.h"


void UniEngine::GLFrameBuffer::Enable(const GLenum& cap)
{
	glEnable(cap);
}

void UniEngine::GLFrameBuffer::Disable(const GLenum& cap)
{
	glDisable(cap);
}

inline void UniEngine::GLFrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void UniEngine::GLFrameBuffer::ClearColor(const glm::vec4& value) const
{
	Bind();
	glClearColor(value.r, value.g, value.b, value.a);
}

void UniEngine::GLFrameBuffer::ViewPort(const glm::ivec4& value) const
{
	Bind();
	glViewport(value[0], value[1], value[2], value[3]);
}

void UniEngine::GLFrameBuffer::Check() const
{
	Bind();
	const auto status = glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		Debug::Error("GLFrameBuffer: Not Complete!");
}

void UniEngine::GLFrameBuffer::DrawBuffer(const GLenum& buffer) const
{
	Bind();
	glNamedFramebufferDrawBuffer(m_id, buffer);
}

void UniEngine::GLFrameBuffer::DrawBuffers(const GLsizei& n, const GLenum* buffers) const
{
	Bind();
	glNamedFramebufferDrawBuffers(m_id, n, buffers);
}

inline void UniEngine::GLFrameBuffer::BindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline UniEngine::GLFrameBuffer::GLFrameBuffer()
{
	m_color = false;
	m_depth = false;
	m_stencil = false;
	glCreateFramebuffers(1, &m_id);
}

inline UniEngine::GLFrameBuffer::~GLFrameBuffer()
{
	BindDefault();
	glDeleteFramebuffers(1, &m_id);
}

inline bool UniEngine::GLFrameBuffer::Color() const
{
	return m_color;
}

inline bool UniEngine::GLFrameBuffer::Depth() const
{
	return m_depth;
}

inline bool UniEngine::GLFrameBuffer::Stencil() const
{
	return m_stencil;
}

inline void UniEngine::GLFrameBuffer::AttachRenderBuffer(const GLRenderBuffer* buffer, const GLenum& attachPoint)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		m_depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		m_stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		m_depth = true;
		m_stencil = true;
		break;
	default:
		m_color = true;
		break;
	}
	Bind();
	glNamedFramebufferRenderbuffer(m_id, attachPoint, GL_RENDERBUFFER, buffer->Id());
}

inline void UniEngine::GLFrameBuffer::AttachTexture(const GLTexture* texture, const GLenum& attachPoint)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		m_depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		m_stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		m_depth = true;
		m_stencil = true;
		break;
	default:
		m_color = true;
		break;
	}
	Bind();
	glNamedFramebufferTexture(m_id, attachPoint, texture->Id(), 0);
}

inline void UniEngine::GLFrameBuffer::AttachTextureLayer(const GLTexture* texture, const GLenum& attachPoint, const GLint& layer)
{
	switch (attachPoint)
	{
	case GL_DEPTH_ATTACHMENT:
		m_depth = true;
		break;
	case GL_STENCIL_ATTACHMENT:
		m_stencil = true;
		break;
	case GL_DEPTH_STENCIL_ATTACHMENT:
		m_depth = true;
		m_stencil = true;
		break;
	default:
		m_color = true;
		break;
	}
	Bind();
	glNamedFramebufferTextureLayer(m_id, attachPoint, texture->Id(), 0, layer);
}

void UniEngine::GLFrameBuffer::Clear()
{
	Bind();
	glClear((m_color ? GL_COLOR_BUFFER_BIT : 0) | (m_depth ? GL_DEPTH_BUFFER_BIT : 0) | (m_stencil ? GL_STENCIL_BUFFER_BIT : 0));
}
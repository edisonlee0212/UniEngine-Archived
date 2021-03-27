#include "pch.h"
#include "GLBuffer.h"
using namespace UniEngine;

GLBuffer::GLBuffer(GLenum target)
{
	glGenBuffers(1, &m_id);
	m_target = target;
}

void GLBuffer::Bind() const
{
	glBindBuffer(m_target, m_id);
}

void GLBuffer::SetData(const GLsizei& length, const GLvoid* data, const GLenum& usage) const
{
	Bind();
	glNamedBufferData(m_id, length, data, usage);
}

void GLBuffer::SubData(const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data) const
{
	Bind();
	glNamedBufferSubData(m_id, offset, size, data);
}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &m_id);
}

GLPPBO::GLPPBO(): GLBuffer(GL_PIXEL_PACK_BUFFER)
{
}

void GLPPBO::BindDefault()
{
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}

GLPUBO::GLPUBO(): GLBuffer(GL_PIXEL_UNPACK_BUFFER)
{
}

void GLPUBO::BindDefault()
{
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

GLEBO::GLEBO(): GLBuffer(GL_ELEMENT_ARRAY_BUFFER)
{
}

void GLEBO::BindDefault()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLVBO::GLVBO(): GLBuffer(GL_ARRAY_BUFFER)
{
}

void GLVBO::BindDefault()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLUBO::GLUBO(): GLBuffer(GL_UNIFORM_BUFFER)
{
}

void GLUBO::BindDefault()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLUBO::SetBase(const GLuint& index) const
{
	glBindBufferBase(GL_UNIFORM_BUFFER, index, m_id);
}

void GLUBO::SetRange(const GLuint& index, const GLintptr& offset, const GLsizeiptr& size) const
{
	glBindBufferRange(GL_UNIFORM_BUFFER, index, m_id, offset, size);
}

GLVAO::~GLVAO()
{
	BindDefault();
	glDeleteVertexArrays(1, &m_id);
}

void GLVAO::Bind() const
{
	glBindVertexArray(m_id);
}

void GLVAO::BindDefault()
{
	glBindVertexArray(0);
}

GLVAO::GLVAO()
{
	glGenVertexArrays(1, &m_id);
}

GLVBO* GLVAO::Vbo()
{
	return &m_vbo;
}

GLEBO* GLVAO::Ebo()
{
	return &m_ebo;
}

void GLVAO::SetData(const GLsizei& length, const GLvoid* data, const GLenum& usage) const
{
	Bind();
	m_vbo.SetData(length, data, usage);
}

void GLVAO::SubData(const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data) const
{
	Bind();
	m_vbo.SubData(offset, size, data);
}

void GLVAO::EnableAttributeArray(const GLuint& index) const
{
	Bind();
	glEnableVertexAttribArray(index);
}

void GLVAO::DisableAttributeArray(const GLuint& index) const
{
	Bind();
	glDisableVertexAttribArray(index);
}

void GLVAO::SetAttributePointer(const GLuint& index, const GLint& size, const GLenum& type, const GLboolean& normalized,
                                const GLsizei& stride, const void* pointer) const
{
	Bind();
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void GLVAO::SetAttributeIntPointer(const GLuint& index, const GLint& size, const GLenum& type, const GLsizei& stride,
                                   const void* pointer) const
{
	Bind();
	glVertexAttribIPointer(index, size, type, stride, pointer);
}

void GLVAO::SetAttributeDivisor(const GLuint& index, const GLuint& divisor) const
{
	Bind();
	glVertexAttribDivisor(index, divisor);
}

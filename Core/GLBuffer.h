#pragma once
#include "GLObject.h"
namespace UniEngine {
	class CORE_API GLBuffer : public GLObject
	{
		GLenum _Target;
	public:
		GLBuffer(GLenum target) {
			glGenBuffers(1, &_ID);
			_Target = target;
		}
		void Bind() {
			glBindBuffer(_Target, _ID);
		}
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			Bind();
			glBufferData(_Target, length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			Bind();
			glBufferSubData(_Target, offset, size, data);
		}
		~GLBuffer() {
			glDeleteBuffers(1, &_ID);
		}
	};

	class CORE_API GLPPBO : public GLBuffer {
	public:
		GLPPBO() : GLBuffer(GL_PIXEL_PACK_BUFFER) {}
		static void BindDefault() {
			glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
		}
	};

	class CORE_API GLPUBO : public GLBuffer {
	public:
		GLPUBO() : GLBuffer(GL_PIXEL_UNPACK_BUFFER) {}
		static void BindDefault() {
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		}
	};

	class CORE_API GLEBO : public GLBuffer {
	public:
		GLEBO() : GLBuffer(GL_ELEMENT_ARRAY_BUFFER) {}
		static void BindDefault() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	};

	class CORE_API GLVBO : public GLBuffer {
	public:
		GLVBO() : GLBuffer(GL_ARRAY_BUFFER) {}
		static void BindDefault() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};

	class CORE_API GLUBO : public GLBuffer {
	public:
		GLUBO() : GLBuffer(GL_UNIFORM_BUFFER){}
		static void BindDefault() {
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		void SetBase(GLuint index) {
			glBindBufferBase(GL_UNIFORM_BUFFER, index, _ID);
		}
		void SetRange(GLuint index,
			GLintptr offset,
			GLsizeiptr size) {
			glBindBufferRange(GL_UNIFORM_BUFFER, index, _ID, offset, size);
		}
	};

	class CORE_API GLVAO : public GLObject {
	protected:
		GLVBO* _VBO;
		GLEBO* _EBO;
	public:
		~GLVAO() {
			delete _VBO;
			delete _EBO;
			BindDefault();
			glDeleteVertexArrays(1, &_ID);
		}

		void Bind() {
			glBindVertexArray(_ID);
		}

		static void BindDefault() {
			glBindVertexArray(0);
		}
		GLVAO() {
			glGenVertexArrays(1, &_ID);
			_VBO = new GLVBO();
			_EBO = new GLEBO();
		}
		GLVBO* VBO() {
			return _VBO;
		}

		GLEBO* EBO() {
			return _EBO;
		}

		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			Bind();
			_VBO->SetData(length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			Bind();
			_VBO->SubData(offset, size, data);
		}

		void EnableAttributeArray(GLuint index)
		{
			Bind();
			glEnableVertexAttribArray(index);
		}

		void DisableAttributeArray(GLuint index)
		{
			Bind();
			glDisableVertexAttribArray(index);
		}

		void SetAttributePointer(GLuint index,
			GLint size,
			GLenum type,
			GLboolean normalized,
			GLsizei stride,
			const void* pointer) {
			Bind();
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		}

		void SetAttributeIntPointer(GLuint index,
			GLint size,
			GLenum type,
			GLsizei stride,
			const void* pointer) {
			Bind();
			glVertexAttribIPointer(index, size, type, stride, pointer);
		}

		void SetAttributeDivisor(GLuint index,
			GLuint divisor) {
			Bind();
			glVertexAttribDivisor(index, divisor);
		}

	};
}


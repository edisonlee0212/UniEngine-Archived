#pragma once
#include "GLObject.h"
namespace UniEngine {
	class GLBuffer : public GLObject
	{
	public:
		GLBuffer() {
			glGenBuffers(1, &_ID);
		}
		~GLBuffer() {
			glDeleteBuffers(1, &_ID);
		}
	};

	class GLEBO : public GLBuffer {
	public:
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, data, usage);
		}
	};

	class GLVBO : public GLBuffer {
	public:
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			glBindBuffer(GL_ARRAY_BUFFER, _ID);
			glBufferData(GL_ARRAY_BUFFER, length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			glBindBuffer(GL_ARRAY_BUFFER, _ID);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}
	};

	class GLUBO : public GLBuffer {
		void SetData() {
			glBindBuffer(GL_UNIFORM_BUFFER, _ID);
		}
	};

	class GLVAO : public GLObject {
	protected:
		GLVBO* _VBO;
		GLEBO* _EBO;
	public:
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

		void Bind() {
			glBindVertexArray(_ID);
		}

		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			glBindVertexArray(_ID);
			_VBO->SetData(length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			glBindVertexArray(_ID);
			_VBO->SubData(offset, size, data);
		}

		void EnableAttributeArray(GLuint index)
		{
			glEnableVertexAttribArray(index);
		}
		void SetAttributePointer(GLuint index,
			GLint size,
			GLenum type,
			GLboolean normalized,
			GLsizei stride,
			const void* pointer) {
			glBindVertexArray(_ID);
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		}

		~GLVAO() {
			glDeleteVertexArrays(1, &_ID);
		}
	};
}


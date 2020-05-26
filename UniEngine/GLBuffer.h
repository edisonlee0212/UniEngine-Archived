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
		void Load() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
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
	public:
		static void BindDefault() {
			glBindVertexArray(0);
		}
		GLVAO() {
			glGenVertexArrays(1, &_ID);
			_VBO = new GLVBO();
		}
		GLVBO* VBO() {
			return _VBO;
		}
		void Bind() {
			glBindVertexArray(_ID);
		}

		void SetData(GLsizei length, GLvoid* data, GLenum usage, size_t attributeSize) {
			glBindVertexArray(_ID);
			_VBO->SetData(length, data, usage);
			for (size_t i = 0; i < attributeSize; i++) {
				glEnableVertexAttribArray(i);
			}
			glBindVertexArray(0);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			glBindVertexArray(_ID);
			_VBO->SubData(offset, size, data);
			glBindVertexArray(0);
		}

		void SetAttributePointer(GLuint index,
			GLint size,
			GLenum type,
			GLboolean normalized,
			GLsizei stride,
			const void* pointer) {
			glBindVertexArray(_ID);
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
			glBindVertexArray(0);
		}

		~GLVAO() {
			glDeleteVertexArrays(1, &_ID);
		}
	};
}


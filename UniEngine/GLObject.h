#pragma once
#include "Misc.h"
#include "Math.h"
namespace UniEngine {
	class GLObject
	{
	protected:
		GLuint name;
		GLObject() : name(0){}
	public:
		GLuint GetName() {
			return name;
		}
	};

	class GLBO : public GLObject {
	public:
		GLBO() : GLObject() {
			glGenBuffers(1, &name);
		}
		~GLBO() {
			glDeleteBuffers(1, &name);
		}
	};

	class GLEBO : public GLBO {
	public:
		void Load() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, name);
		}
	};

	class GLVBO : public GLBO {
	public:
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			glBindBuffer(GL_ARRAY_BUFFER, name);
			glBufferData(GL_ARRAY_BUFFER, length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			glBindBuffer(GL_ARRAY_BUFFER, name);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}
	};

	class GLUBO : public GLBO {
		void SetData() {
			glBindBuffer(GL_UNIFORM_BUFFER, name);
		}
	};

	class GLVAO : public GLObject {
	protected:
		GLVBO* _VBO;
	public:
		GLVAO() : GLObject() {
			glGenVertexArrays(1, &name);
			_VBO = new GLVBO();
		}
		void SetData(GLsizei length, GLvoid* data, GLenum usage, size_t attributeSize) {
			glBindVertexArray(name);
			_VBO->SetData(length, data, usage);
			for (size_t i = 0; i < attributeSize; i++) {
				glEnableVertexAttribArray(i);
			}
			glBindVertexArray(0);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			glBindVertexArray(name);
			_VBO->SubData(offset, size, data);
			glBindVertexArray(0);
		}

		void SetAttributePointer(GLuint index,
			GLint size,
			GLenum type,
			GLboolean normalized,
			GLsizei stride,
			const void* pointer) {
			glBindVertexArray(name);
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
			glBindVertexArray(0);
		}

		~GLVAO() {
			glDeleteVertexArrays(1, &name);
		}
	};

	class GLTexture : public GLObject {

	};

	class GLFBO : public GLObject {

	};

	

	
}
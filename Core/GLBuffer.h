#pragma once
#include "GLObject.h"
namespace UniEngine {
	class CORE_API GLBuffer : public GLObject
	{
	public:
		GLBuffer() {
			glGenBuffers(1, &_ID);
		}
		~GLBuffer() {
			glDeleteBuffers(1, &_ID);
		}
	};

	class CORE_API GLEBO : public GLBuffer {
		static GLuint _CurrentBinding;
	public:
		void Bind() {
			if (_ID == _CurrentBinding) return;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
			_CurrentBinding = _ID;
		}
		static void BindDefault() {
			if (_CurrentBinding == 0) return;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			_CurrentBinding = 0;
		}
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, data, usage);
		}
		~GLEBO() {
			BindDefault();
		}
	};

	class CORE_API GLVBO : public GLBuffer {
		static GLuint _CurrentBinding;
	public:
		void Bind() {
			if (_ID == _CurrentBinding) return;
			glBindBuffer(GL_ARRAY_BUFFER, _ID);
			_CurrentBinding = _ID;
		}
		static void BindDefault() {
			if (_CurrentBinding == 0) return;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			_CurrentBinding = 0;
		}
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			Bind();
			glBufferData(GL_ARRAY_BUFFER, length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			Bind();
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}
		~GLVBO() {
			BindDefault();
		}
	};

	class CORE_API GLUBO : public GLBuffer {
		static GLuint _CurrentBinding;
	public:
		~GLUBO() {
			BindDefault();
		}

		void Bind() {
			if (_ID == _CurrentBinding) return;
			glBindBuffer(GL_UNIFORM_BUFFER, _ID);
			_CurrentBinding = _ID;
		}
		static void BindDefault() {
			if (_CurrentBinding == 0) return;
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			_CurrentBinding = 0;
		}
		void SetData(GLsizei length, GLvoid* data, GLenum usage) {
			Bind();
			glBufferData(GL_UNIFORM_BUFFER, length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			Bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
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
		static GLuint _CurrentBinding;
	public:
		~GLVAO() {
			delete _VBO;
			delete _EBO;
			BindDefault();
			glDeleteVertexArrays(1, &_ID);
		}

		void Bind() {
			if (_ID == _CurrentBinding) return;
			glBindVertexArray(_ID);
			_CurrentBinding = _ID;
		}

		static void BindDefault() {
			if (_CurrentBinding == 0) return;
			glBindVertexArray(0);
			_CurrentBinding = 0;
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

		void SetAttributeDivisor(GLuint index,
			GLuint divisor) {
			Bind();
			glVertexAttribDivisor(index, divisor);
		}

	};
}


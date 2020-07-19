#pragma once
#include "GLObject.h"
namespace UniEngine {
	class CORE_API GLBuffer : public GLObject
	{
	public:
		GLBuffer() {
			glCreateBuffers(1, &_ID);
		}
		~GLBuffer() {
			glDeleteBuffers(1, &_ID);
		}
		void SetData(GLsizei length, GLvoid* data, GLbitfield flags) {
			glNamedBufferStorage(_ID, length, data, flags);
			//glNamedBufferData(_ID, length, data, usage);
		}
		void SubData(GLintptr offset, GLsizeiptr size, GLvoid* data) {
			glNamedBufferSubData(_ID, offset, size, data);
		}
	};

	class CORE_API GLEBO : public GLBuffer {
	public:
		GLEBO() : GLBuffer() {
			Bind();
		}
		void Bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
		}
		static void BindDefault() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		~GLEBO() {
			BindDefault();
		}
	};

	class CORE_API GLVBO : public GLBuffer {
		GLuint _BindingIndex;
	public:
		GLVBO(GLuint bindingIndex) : GLBuffer() {
			Bind();
			_BindingIndex = bindingIndex;
		}
		void Bind() {
			glBindBuffer(GL_ARRAY_BUFFER, _ID);
		}
		static void BindDefault() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		GLuint BindingIndex() {
			return _BindingIndex;
		}
		~GLVBO() {
			BindDefault();
		}
	};

	class CORE_API GLUBO : public GLBuffer {
	public:
		GLUBO() : GLBuffer() {
			Bind();
		}
		~GLUBO() {
			BindDefault();
		}

		void Bind() {
			glBindBuffer(GL_UNIFORM_BUFFER, _ID);
		}
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
		friend class GLCore;
		static GLint _MaxAllowedVBO;
	protected:
		std::vector<GLVBO*> _VBOs;
		GLEBO _EBO;
	public:
		~GLVAO() {
			BindDefault();
			for (auto vbo : _VBOs) delete vbo;
			glDeleteVertexArrays(1, &_ID);
		}

		void Bind() {
			glBindVertexArray(_ID);
		}

		static void BindDefault() {
			glBindVertexArray(0);
		}

		GLVAO() {
			_VBOs = std::vector<GLVBO*>();
			glCreateVertexArrays(1, &_ID);
			glVertexArrayElementBuffer(_ID, _EBO.ID());
		}

		GLVBO* AddVBO(GLsizei stride) {
			if (_VBOs.size() >= _MaxAllowedVBO) {
				Debug::Error("Too many VBO!");
			}
			auto vbo = new GLVBO(_VBOs.size());
			glVertexArrayVertexBuffer(_ID, _VBOs.size(), vbo->ID(), 0, stride);
			_VBOs.push_back(vbo);
			return vbo;
		}

		GLVBO* VBO(size_t index) {
			return _VBOs[index];
		}

		GLEBO* EBO() {
			return &_EBO;
		}

		void EnableAttributeArray(GLuint index)
		{
			glEnableVertexArrayAttrib(_ID, index);
		}

		void DisableAttributeArray(GLuint index)
		{
			glDisableVertexArrayAttrib(_ID, index);
		}

		void SetAttributePointer(GLuint attribindex,
			GLint size,
			GLenum type,
			GLboolean normalized,
			GLuint relativeoffset,
			GLuint bindingindex
			) {
			glEnableVertexArrayAttrib(_ID, attribindex);
			glVertexArrayAttribFormat(_ID, attribindex, size, type, normalized, relativeoffset);
			glVertexArrayAttribBinding(_ID, attribindex, bindingindex);
		}

		void SetAttributeDivisor(GLuint index,
			GLuint divisor) {
			Bind();
			glVertexAttribDivisor(index, divisor);
		}

	};
}


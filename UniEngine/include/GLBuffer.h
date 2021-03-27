#pragma once
#include "GLObject.h"
namespace UniEngine {
	class UNIENGINE_API GLBuffer : public GLObject
	{
		friend class GLCore;
		GLenum m_target;
		static std::map<GLenum, GLuint> m_currentBoundGLBuffer;
	public:
		GLBuffer(GLenum target);
		void Bind() const;
		void SetData(const GLsizei& length, const GLvoid* data, const GLenum& usage) const;
		void SubData(const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data) const;
		~GLBuffer() override;
	};

	class UNIENGINE_API GLPPBO : public GLBuffer {
	public:
		GLPPBO();
		static void BindDefault();
	};

	class UNIENGINE_API GLPUBO : public GLBuffer {
	public:
		GLPUBO();
		static void BindDefault();
	};

	class UNIENGINE_API GLEBO : public GLBuffer {
	public:
		GLEBO();
		static void BindDefault();
	};

	class UNIENGINE_API GLVBO : public GLBuffer {
	public:
		GLVBO();
		static void BindDefault();
	};

	class UNIENGINE_API GLUBO : public GLBuffer {
	public:
		GLUBO();
		void SetBase(const GLuint& index) const;
		void SetRange(const GLuint& index,
		              const GLintptr& offset,
		              const GLsizeiptr& size) const;
	};

	class UNIENGINE_API GLVAO : public GLObject {
	protected:
		GLVBO m_vbo;
		GLEBO m_ebo;
	public:
		~GLVAO() override;
		void Bind() const;
		GLVAO();
		GLVBO* Vbo();
		GLEBO* Ebo();
		void SetData(const GLsizei& length, const GLvoid* data, const GLenum& usage) const;
		void SubData(const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data) const;
		void EnableAttributeArray(const GLuint& index) const;
		void DisableAttributeArray(const GLuint& index) const;
		void SetAttributePointer(const GLuint& index,
		                         const GLint& size,
		                         const GLenum& type,
		                         const GLboolean& normalized,
		                         const GLsizei& stride,
		                         const void* pointer) const;

		void SetAttributeIntPointer(const GLuint& index,
		                            const GLint& size,
		                            const GLenum& type,
		                            const GLsizei& stride,
		                            const void* pointer) const;

		void SetAttributeDivisor(const GLuint& index,
		                         const GLuint& divisor) const;
	};
}


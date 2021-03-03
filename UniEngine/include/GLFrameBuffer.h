#pragma once
#include "GLObject.h"
#include "GLRenderBuffer.h"
#include "GLTexture.h"

namespace UniEngine {
	class UNIENGINE_API GLFrameBuffer : public GLObject
	{
		bool m_color;
		bool m_depth;
		bool m_stencil;
	public:
		static void Enable(const GLenum& cap);
		static void Disable(const GLenum& cap);
		void Bind() const;
		void ClearColor(const glm::vec4& value) const;
		void ViewPort(const glm::ivec4& value) const;
		void Check() const;
		void DrawBuffer(const GLenum& buffer) const;
		void DrawBuffers(const GLsizei& n,
		                 const GLenum* buffers) const;
		static void BindDefault();
		GLFrameBuffer();
		~GLFrameBuffer() override;
		bool Color() const;
		bool Depth() const;
		bool Stencil() const;
		void AttachRenderBuffer(const GLRenderBuffer* buffer, const GLenum& attachPoint);
		void AttachTexture(const GLTexture* texture, const GLenum& attachPoint);
		void AttachTextureLayer(const GLTexture* texture, const GLenum& attachPoint, const GLint& layer);
		void Clear();
	};
}

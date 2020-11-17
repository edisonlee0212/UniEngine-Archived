#pragma once
#include "GLObject.h"
#include "GLRenderBuffer.h"
#include "GLTexture.h"

namespace UniEngine {
	class UNIENGINE_API GLFrameBuffer : public GLObject
	{
		bool _Color;
		bool _Depth;
		bool _Stencil;
	public:
		static void Enable(GLenum cap)
		{
			glEnable(cap);
		}
		static void Disable(GLenum cap)
		{
			glDisable(cap);
		}
		void Bind();
		void ClearColor(glm::vec4 value)
		{
			Bind();
			glClearColor(value.r, value.g, value.b, value.a);
		}
		void ViewPort(glm::ivec4 value)
		{
			Bind();
			glViewport(value[0], value[1], value[2], value[3]);
		}
		void Check()
		{
			Bind();
			auto status = glCheckNamedFramebufferStatus(_ID, GL_FRAMEBUFFER);
			if (status != GL_FRAMEBUFFER_COMPLETE)
				Debug::Error("GLFrameBuffer: Not Complete!");
		}
		void DrawBuffer(GLenum buffer)
		{
			Bind();
			glNamedFramebufferDrawBuffer(_ID, buffer);
		}
		void DrawBuffers(GLsizei n,
			const GLenum* bufs)
		{
			Bind();
			glNamedFramebufferDrawBuffers(_ID, n, bufs);
		}
		static void BindDefault();
		GLFrameBuffer();
		~GLFrameBuffer();
		bool Color();
		bool Depth();
		bool Stencil();
		void AttachRenderBuffer(GLRenderBuffer* buffer, GLenum attachPoint);
		void AttachTexture(GLTexture* texture, GLenum attachPoint);
		void AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer);
		void Clear();
	};
}

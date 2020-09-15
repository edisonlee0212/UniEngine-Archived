#pragma once
#include "GLObject.h"
#include "GLRenderBuffer.h"
#include "GLTexture.h"

namespace UniEngine {
	class CORE_API GLFrameBuffer : public GLObject
	{
		bool _Color;
		bool _Depth;
		bool _Stencil;
	public:
		void Bind();
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

#pragma once
#include "GLObject.h"
#include "GLRenderBuffer.h"
#include "GLTexture.h"
#include "Math.h"
namespace UniEngine {
	class GLFrameBuffer : public GLObject
	{
		bool _Color;
		bool _Depth;
		bool _Stencil;
	public:
		GLFrameBuffer();
		~GLFrameBuffer();
		bool Color();
		bool Depth();
		bool Stencil();
		void AttachRenderBuffer(GLRenderBuffer* buffer, GLint attachPoint);
		void AttachTexture(GLTexture* texture, GLint attachPoint);
	};
}

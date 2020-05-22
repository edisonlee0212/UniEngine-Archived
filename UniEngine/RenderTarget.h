#pragma once
#include "Misc.h"
#include "GLFrameBuffer.h"
#include "GLRenderBuffer.h"
namespace UniEngine {
	class RenderTarget
	{
		GLFrameBuffer* _FrameBuffer;
		bool _Bound;
	public:
		RenderTarget();
		void AttachTexture(GLTexture* texture, GLint attachPoint);
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLint attachPoint);
		void Bind();
		static void BindDefault();
	};

}
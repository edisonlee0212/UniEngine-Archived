#pragma once
#include "Misc.h"
#include "GLFrameBuffer.h"
#include "GLRenderBuffer.h"
namespace UniEngine {
	class RenderTarget
	{
		GLFrameBuffer* _FrameBuffer;
		uint _Width;
		uint _Height;
		bool _Bound;
	public:
		RenderTarget(uint width, uint height);
		void AttachTexture(GLTexture* texture, GLint attachPoint);
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLint attachPoint);
		void Bind();
		void Unbind();
	};

}
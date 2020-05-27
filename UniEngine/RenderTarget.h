#pragma once
#include "Misc.h"
#include "Core.h"
namespace UniEngine {
	class RenderTarget
	{
		GLFrameBuffer* _FrameBuffer;
		bool _Bound;
	protected:
		unsigned _ResolutionX;
		unsigned _ResolutionY;
		void AttachTexture(GLTexture* texture, GLint attachPoint);
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLint attachPoint);
	public:
		RenderTarget();
		glm::vec2 GetResolution();
		void Bind();
		static void BindDefault();
	};

}
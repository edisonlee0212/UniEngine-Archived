#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API RenderTarget
	{
		bool _Bound;
	protected:
		GLFrameBuffer* _FrameBuffer;
		size_t _ResolutionX;
		size_t _ResolutionY;
	public:
		void AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer);
		void AttachTexture(GLTexture* texture, GLenum attachPoint);
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLenum attachPoint);
		RenderTarget();
		RenderTarget(size_t width, size_t height);
		glm::vec2 GetResolution();
		void SetResolution(size_t width, size_t height);
		float GetResolutionRatio();
		void Bind();
		void Clear();

		GLFrameBuffer* GetFrameBuffer() const
		{
			return _FrameBuffer;
		}

		static void BindDefault();
	};

}
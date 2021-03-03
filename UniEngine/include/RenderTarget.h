#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API RenderTarget
	{
		bool m_bound;
	protected:
		std::unique_ptr<GLFrameBuffer> m_frameBuffer;
		size_t m_resolutionX;
		size_t m_resolutionY;
	public:
		void AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer) const;
		void AttachTexture(GLTexture* texture, GLenum attachPoint) const;
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLenum attachPoint) const;
		RenderTarget();
		RenderTarget(size_t width, size_t height);
		glm::vec2 GetResolution() const;
		void SetResolution(size_t width, size_t height);
		float GetResolutionRatio() const;
		void Bind() const;
		void Clear() const;
		std::unique_ptr<GLFrameBuffer>& GetFrameBuffer();
		static void BindDefault();
	};

}
#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API RenderTarget
	{
		
		bool _Bound;
	protected:
		GLFrameBuffer* _FrameBuffer;
		unsigned _ResolutionX;
		unsigned _ResolutionY;
	public:
		void AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer);
		void AttachTexture2D(GLTexture* texture, GLenum attachPoint);
		void AttachTexture(GLTexture* texture, GLenum attachPoint);
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLenum attachPoint);
		GLTexture* SetTexture2D(GLenum attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type = GL_FLOAT, const void* data = nullptr);
		GLTexture* SetCubeMap(GLenum attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type = GL_FLOAT, const void* data = nullptr);
		GLRenderBuffer* SetRenderBuffer(GLenum attachPoint, GLenum internalformat​);
		RenderTarget();
		RenderTarget(float width, float height);
		glm::vec2 GetResolution();
		float GetResolutionRatio();
		void Bind();
		static void BindDefault();
	};

}
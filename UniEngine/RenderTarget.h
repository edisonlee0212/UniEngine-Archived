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
		void AttachTexture2D(GLTexture* texture, GLint attachPoint);
		void AttachTexture(GLTexture* texture, GLint attachPoint);
		void AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLint attachPoint);
		GLTexture* SetTexture2D(GLint attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type = GL_FLOAT, const void* data = nullptr);
		GLTexture* SetCubeMap(GLint attachPoint, GLint level, GLint internalformat, GLint border, GLenum format, GLenum type = GL_FLOAT, const void* data = nullptr);
		GLRenderBuffer* SetRenderBuffer(GLint attachPoint, GLenum internalformat​);
	public:
		RenderTarget();
		glm::vec2 GetResolution();
		float GetResolutionRatio();
		void Bind();
		static void BindDefault();
	};

}
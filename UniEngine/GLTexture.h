#pragma once
#include "GLObject.h"
namespace UniEngine {
	enum class CubeMapIndex {
		PositiveX,
		NegativeX,
		PositiveY,
		NegativeY,
		PositiveZ,
		NegativeZ,
	};
	class GLTexture : public GLObject
	{
	public:
		GLTexture();
		~GLTexture();
		void SetImage1D(GLint level,
			GLint internalformat,
			GLsizei width,
			GLint border,
			GLenum format,
			GLenum type,
			const void* data);
		void SetImage2D(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height,
			GLint border,
			GLenum format,
			GLenum type,
			const void* data);
		void SetImage3D(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height,
			GLsizei depth,
			GLint border,
			GLenum format,
			GLenum type,
			const void* data);
		void SetFloatParameter(GLenum target, GLenum pname, GLfloat param);
		void Activate(GLenum texture);
		void Bind(GLenum target);
		void SetIntParameter(GLenum target, GLenum pname, GLint param);
		void SetCubeMap(CubeMapIndex index, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* data);
	};
}

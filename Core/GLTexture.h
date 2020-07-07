#pragma once
#include "GLObject.h"
namespace UniEngine {
	enum class CORE_API CubeMapIndex {
		PositiveX,
		NegativeX,
		PositiveY,
		NegativeY,
		PositiveZ,
		NegativeZ,
	};
	class CORE_API GLTexture : public GLObject
	{
	public:
		static GLuint _CurrentBinding;
		static void BindDefault();
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

		void SetStorage2D(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height
		);

		void SetImage3D(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height,
			GLsizei depth,
			GLint border,
			GLenum format,
			GLenum type,
			const void* data);

		void SetStorage2DArray(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height,
			GLsizei layer);

		void SetImage2DArray(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height,
			GLsizei layer,
			GLint border,
			GLenum format,
			GLenum type,
			const void* data);

		void SetCubeMapArray(GLint level,
			GLint internalformat,
			GLsizei width,
			GLsizei height,
			GLsizei layer,
			GLint border,
			GLenum format,
			GLenum type,
			const void* data);

		void SetFloatParameter(GLenum target, GLenum pname, GLfloat param);
		void SetFloat4Parameter(GLenum target, GLenum pname, GLfloat* param);
		static void Activate(GLenum texture);
		void Bind(GLenum target);
		void SetIntParameter(GLenum target, GLenum pname, GLint param);
		void SetCubeMap(CubeMapIndex index, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data);
		void GenerateMipMap(GLenum target);
	};
}

#pragma once
#include "Debug.h"
#include "GLObject.h"
namespace UniEngine {
	enum class UNIENGINE_API CubeMapIndex {
		PositiveX,
		NegativeX,
		PositiveY,
		NegativeY,
		PositiveZ,
		NegativeZ,
	};

	struct UNIENGINE_API TextureBinding {
		GLuint m_1d;
		GLuint m_2d;
		GLuint m_3d;
		GLuint m_rectangle;
		GLuint m_buffer;
		GLuint m_cubeMap;
		GLuint m_1dArray;
		GLuint m_2dArray;
		GLuint m_cubeMapArray;
		GLuint m_2dMS;
		GLuint m_2dMSArray;
		TextureBinding();
	};

	class UNIENGINE_API GLTexture : public GLObject
	{
		friend class GLCore;
		static GLint m_maxAllowedTexture;
		static std::list<GLTexture*> m_currentlyResidentTexture;
	protected:
		bool m_resident = false;
		GLuint64 m_handle = 0;
		GLenum m_type;
		GLenum m_format;
		void MakeResidentInternal();
		void MakeNonResidentInternal();
	public:
		static GLint GetMaxAllowedTexture();
		GLuint64 GetHandle();
		[[nodiscard]] bool IsResident() const;
		void MakeResident();
		void MakeNonResident();
		void Clear(const GLint& level) const;
		void SetInt(const GLenum& paramName, const GLint& param);
		void SetFloat(const GLenum& paramName, const GLfloat& param);
		void SetFloat4(const GLenum& paramName, const GLfloat* params);
		void GenerateMipMap() const;
		void Bind(const GLenum& activate) const;
		GLTexture(const GLenum& target, const GLenum& format);
		~GLTexture() override;
	};

	class UNIENGINE_API GLTexture1D : public GLTexture {
		GLsizei m_width = 0;
	public:
		GLTexture1D(const GLsizei& levels,
		            const GLenum& internalFormat,
		            const GLsizei& width, const bool& immutable = true);
		void SetData(const GLint& level,
		             const GLenum& type,
		             const void* pixels) const;
		void SubData(const GLint& level,
		             const GLint& xOffset,
		             const GLenum& type,
		             const GLsizei& width,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTexture2D : public GLTexture {
		GLsizei m_width = 0;
		GLsizei m_height = 0;
		bool m_immutable;
		friend class Texture2D;
	public:
		GLTexture2D(const GLsizei& levels,
		            const GLenum& internalFormat,
		            const GLsizei& width,
		            const GLsizei& height, const bool& immutable = true);

		void SetData(const GLint& level,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void ReSize(const GLint& level,
		            const GLenum& internalFormat,
		            const GLenum& format,
		            const GLenum& type,
		            const void* pixels,
		            const GLsizei& width,
		            const GLsizei& height);

		void SetData(const GLint& level,
		             const GLenum& internalFormat,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SubData(const GLint& level,
		             const GLenum& format,
		             const GLint& xOffset,
		             const GLint& yOffset,
		             const GLsizei& width,
		             const GLsizei& height,
		             const GLenum& type,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTexture3D : public GLTexture {
		GLsizei m_width = 0;
		GLsizei m_height = 0;
		GLsizei m_depth = 0;
	public:
		GLTexture3D(const GLsizei& levels,
		            const GLenum& internalFormat,
		            const GLsizei& width,
		            const GLsizei& height,
		            const GLsizei& depth, const bool& immutable = true);;

		void SetData(const GLint& level,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SubData(const GLint& level,
		             const GLint& xOffset,
		             const GLint& yOffset,
		             const GLint& zOffset,
		             const GLsizei& width,
		             const GLsizei& height,
		             const GLsizei& depth,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTextureRectangle : public GLTexture {
	public:
	};

	class UNIENGINE_API GLTextureBuffer : public GLTexture {
	public:
	};

	class UNIENGINE_API GLTextureCubeMap : public GLTexture {
		GLsizei m_width = 0;
		GLsizei m_height = 0;
	public:
		GLTextureCubeMap(const GLsizei& levels,
		                 const GLenum& internalFormat,
		                 const GLsizei& width,
		                 const GLsizei& height, const bool& immutable = true);

		void SetData(const CubeMapIndex& index,
		             const GLint& level,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SetData(const CubeMapIndex& index,
		             const GLint& level,
		             const GLenum& internalFormat,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SubData(const CubeMapIndex& index,
		             const GLint& level,
		             const GLint& xOffset,
		             const GLint& yOffset,
		             const GLsizei& width,
		             const GLsizei& height,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTexture1DArray : public GLTexture {
		GLsizei m_width = 0;
		GLsizei m_layers = 0;
	public:
		GLTexture1DArray(const GLsizei& levels,
		                 const GLenum& internalFormat,
		                 const GLsizei& width,
		                 const GLsizei& layers);

		void SetData(const GLint& level,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SubData(const GLint& level,
		             const GLint& xOffset,
		             const GLint& layer,
		             const GLsizei& width,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTexture2DArray : public GLTexture {
		GLsizei m_width = 0;
		GLsizei m_height = 0;
		GLsizei m_layers = 0;
	public:
		GLTexture2DArray(const GLsizei& levels,
		                 const GLenum& internalFormat,
		                 const GLsizei& width,
		                 const GLsizei& height,
		                 const GLsizei& layers);;

		void SetData(const GLint& level,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SubData(const GLint& level,
		             const GLint& xOffset,
		             const GLint& yOffset,
		             const GLsizei& layer,
		             const GLsizei& width,
		             const GLsizei& height,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTextureCubeMapArray : public GLTexture {
		GLsizei m_width = 0;
		GLsizei m_height = 0;
		GLsizei m_layers = 0;
	public:
		GLTextureCubeMapArray(const GLsizei& levels,
		                      const GLenum& internalFormat,
		                      const GLsizei& width,
		                      const GLsizei& height,
		                      const GLsizei& layers);;

		void SetData(const CubeMapIndex& index,
		             const GLint& level,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;

		void SubData(const CubeMapIndex& index,
		             const GLint& level,
		             const GLint& xOffset,
		             const GLint& yOffset,
		             const GLsizei& layer,
		             const GLsizei& width,
		             const GLsizei& height,
		             const GLenum& format,
		             const GLenum& type,
		             const void* pixels) const;
	};

	class UNIENGINE_API GLTexture2DMultiSample : public GLTexture {
	public:
	};

	class UNIENGINE_API GLTexture2DMultiSampleArray : public GLTexture {
	public:
	};

}

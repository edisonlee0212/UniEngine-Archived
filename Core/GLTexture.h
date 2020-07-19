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

	struct CORE_API TextureBinding {
		GLuint _1D;
		GLuint _2D;
		GLuint _3D;
		GLuint _Rectangle;
		GLuint _Buffer;
		GLuint _CubeMap;
		GLuint _1DArray;
		GLuint _2DArray;
		GLuint _CubeMapArray;
		GLuint _2DMS;
		GLuint _2DMSArray;
		TextureBinding() {
			 _1D = 0;
			 _2D = 0;
			 _3D = 0;
			 _Rectangle = 0;
			 _Buffer = 0;
			 _CubeMap = 0;
			 _1DArray = 0;
			 _2DArray = 0;
			 _CubeMapArray = 0;
			 _2DMS = 0;
			 _2DMSArray = 0;
		}
	};

	class CORE_API GLTexture : public GLObject
	{
		friend class GLCore;
		static GLint _MaxAllowedTexture;
	protected:
		GLenum _Type;
		GLenum _Format;
	public:
		static GLint GetMaxAllowedTexture() {
			return _MaxAllowedTexture;
		}

		void SetInt(GLenum pname, GLint param) {
			glTextureParameteri(_ID, pname, param);
		}

		void SetFloat(GLenum pname, GLfloat param) {
			glTextureParameterf(_ID, pname, param);
		}

		void SetFloat4(GLenum pname, GLfloat* params) {
			glTextureParameterfv(_ID, pname, params);
		}

		void GenerateMipMap() {
			glGenerateTextureMipmap(_ID);
		}

		void Bind(GLenum activate) {
			if (activate >= _MaxAllowedTexture) {
				Debug::Error("Max allowed texture exceeded!");
			}
			glBindTextureUnit(activate, _ID);
			/*
			switch (_Type)
			{
			case GL_TEXTURE_1D:
				if (_Bindings[activate]._1D != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._1D = _ID;
				}
				break;
			case GL_TEXTURE_2D:
				if (_Bindings[activate]._2D != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._2D = _ID;
				}
				break;
			case GL_TEXTURE_3D:
				if (_Bindings[activate]._3D != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._3D = _ID;
				}
				break;
			case GL_TEXTURE_RECTANGLE:
				if (_Bindings[activate]._Rectangle != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._Rectangle = _ID;
				}
				break;
			case GL_TEXTURE_BUFFER:
				if (_Bindings[activate]._Buffer != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._Buffer = _ID;
				}
				break;
			case GL_TEXTURE_CUBE_MAP:
				if (_Bindings[activate]._CubeMap != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._CubeMap = _ID;
				}
				break;
			case GL_TEXTURE_1D_ARRAY:
				if (_Bindings[activate]._1DArray != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._1DArray = _ID;
				}
				break;
			case GL_TEXTURE_2D_ARRAY:
				if (_Bindings[activate]._2DArray != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._2DArray = _ID;
				}
				break;
			case GL_TEXTURE_CUBE_MAP_ARRAY:
				if (_Bindings[activate]._CubeMapArray != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._CubeMapArray = _ID;
				}
				break;
			case GL_TEXTURE_2D_MULTISAMPLE:
				if (_Bindings[activate]._2DMS != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._2DMS = _ID;
				}
				break;
			case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
				if (_Bindings[activate]._2DMSArray != _ID) {
					glBindTextureUnit(activate, _ID);
					_Bindings[activate]._2DMSArray = _ID;
				}
				break;
			default:
				break;
			}*/
		}
		GLTexture(GLenum target, GLenum format) {
			glCreateTextures(target, 1, &_ID);
			_Type = target;
			_Format = format;
		}
		~GLTexture() {
			glDeleteTextures(1, &_ID);
		}
	};

	class CORE_API GLTexture1D : public GLTexture {
		GLsizei _Width = 0;
	public:
		GLTexture1D(GLsizei levels,
			GLenum internalFormat,
			GLsizei width) : GLTexture(GL_TEXTURE_1D, internalFormat) {
			_Width = width;
			glTextureStorage1D(_ID, levels, internalFormat, width);
		};

		void SetData(GLint level,
			GLenum type,
			const void* pixels) {
			glTextureSubImage1D(_ID, level, 0, _Width, _Format, type, pixels);
		}

		void SubData(GLint level,
			GLint xoffset,
			GLenum type,
			GLsizei width,
			const void* pixels) {
			if ((xoffset + width) > _Width) {
				Debug::Error("Error!");
			}
			glTextureSubImage1D(_ID, level, xoffset, width, _Format, type, pixels);
		}
	};

	class CORE_API GLTexture2D : public GLTexture {
		GLsizei _Width = 0;
		GLsizei _Height = 0;
	public:
		GLTexture2D(GLsizei levels,
			GLenum internalFormat,
			GLsizei width,
			GLsizei height) : GLTexture(GL_TEXTURE_2D, internalFormat) {
			_Width = width;
			_Height = height;
			glTextureStorage2D(_ID, levels, internalFormat, width, height);
		};

		void SetData(GLint level,
			GLenum format,
			GLenum type,
			const void* pixels) {
			glTextureSubImage2D(_ID, level, 0, 0, _Width, _Height, format, type, pixels);
		}

		void SubData(GLint level,
			GLenum format,
			GLint xoffset,
			GLint yoffset,
			GLsizei width,
			GLsizei height,
			GLenum type,
			const void* pixels) {
			if ((xoffset + width) > _Width || (yoffset + height) > _Height) {
				Debug::Error("Error!");
			}
			glTextureSubImage2D(_ID, level, xoffset, yoffset, width, height, format, type, pixels);
		}
	};

	class CORE_API GLTexture3D : public GLTexture {
		GLsizei _Width = 0;
		GLsizei _Height = 0;
		GLsizei _Depth = 0;
	public:
		GLTexture3D(GLsizei levels,
			GLenum internalFormat,
			GLsizei width,
			GLsizei height,
			GLsizei depth) : GLTexture(GL_TEXTURE_3D, internalFormat) {
			_Width = width;
			_Height = height;
			_Depth = depth;
			glTextureStorage3D(_ID, levels, internalFormat, width, height, depth);
		};

		void SetData(GLint level,
			GLenum format,
			GLenum type,
			const void* pixels) {
			glTextureSubImage3D(_ID, level, 0, 0, 0, _Width, _Height, _Depth, format, type, pixels);
		}

		void SubData(GLint level,
			GLint xoffset,
			GLint yoffset,
			GLint zoffset,
			GLsizei width,
			GLsizei height,
			GLsizei depth,
			GLenum format,
			GLenum type,
			const void* pixels) {
			if ((xoffset + width) > _Width || (yoffset + height) > _Height || (zoffset + depth) > _Depth) {
				Debug::Error("Error!");
			}
			glTextureSubImage3D(_ID, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		}
	};

	class CORE_API GLTextureRectangle : public GLTexture {
	public:
	};

	class CORE_API GLTextureBuffer : public GLTexture {
	public:
	};

	class CORE_API GLTextureCubeMap : public GLTexture {
		GLsizei _Width = 0;
		GLsizei _Height = 0;
	public:
		GLTextureCubeMap(GLsizei levels,
			GLenum internalFormat,
			GLsizei width,
			GLsizei height) : GLTexture(GL_TEXTURE_CUBE_MAP, internalFormat) {
			_Width = width;
			_Height = height;
			glTextureStorage2D(_ID, levels, internalFormat, width, height);
		};

		void SetData(CubeMapIndex index,
			GLint level,
			GLenum format,
			GLenum type,
			const void* pixels) {
			if ((size_t)index > 5) {
				Debug::Error("Error!");
			}
			glTextureSubImage3D(_ID, level, 0, 0, (size_t)index, _Width, _Height, 1, format, type, pixels);
		}

		void SubData(CubeMapIndex index,
			GLint level,
			GLint xoffset,
			GLint yoffset, 
			GLsizei width,
			GLsizei height,
			GLenum format,
			GLenum type,
			const void* pixels) {
			if ((xoffset + width) > _Width || (yoffset + height) > _Height || (size_t)index > 5) {
				Debug::Error("Error!");
			}
			glTextureSubImage3D(_ID, level, xoffset, yoffset, (size_t)index, width, height, 1, format, type, pixels);
		}
	};

	class CORE_API GLTexture1DArray : public GLTexture {
		GLsizei _Width = 0;
		GLsizei _Layers = 0;
	public:
		GLTexture1DArray(GLsizei levels,
			GLenum internalFormat,
			GLsizei width,
			GLsizei layers) : GLTexture(GL_TEXTURE_1D_ARRAY, internalFormat) {
			_Width = width;
			_Layers = layers;
			glTextureStorage2D(_ID, levels, internalFormat, width, layers);
		};

		void SetData(GLint level,
			GLenum format,
			GLenum type,
			const void* pixels) {
			glTextureSubImage2D(_ID, level, 0, 0, _Width, _Layers, format, type, pixels);
		}

		void SubData(GLint level,
			GLint xoffset,
			GLint layer,
			GLsizei width,
			GLenum format,
			GLenum type,
			const void* pixels) {
			glTextureSubImage2D(_ID, level, xoffset, layer, _Width, 1, format, type, pixels);
		}
	};

	class CORE_API GLTexture2DArray : public GLTexture {
		GLsizei _Width = 0;
		GLsizei _Height = 0;
		GLsizei _Layers = 0;
	public:
		GLTexture2DArray(GLsizei levels,
			GLenum internalFormat,
			GLsizei width,
			GLsizei height,
			GLsizei layers) : GLTexture(GL_TEXTURE_2D_ARRAY, internalFormat) {
			_Width = width;
			_Height = height;
			_Layers = layers;
			glTextureStorage3D(_ID, levels, internalFormat, width, height, layers);
		};

		void SetData(GLint level,
			GLenum format,
			GLenum type,
			const void* pixels) {
			glTextureSubImage3D(_ID, level, 0, 0, 0, _Width, _Height, _Layers, format, type, pixels);
		}

		void SubData(GLint level,
			GLint xoffset,
			GLint yoffset,
			GLsizei layer,
			GLsizei width,
			GLsizei height,
			GLenum format,
			GLenum type,
			const void* pixels) {
			if ((xoffset + width) > _Width || (yoffset + height) > _Height || layer >= _Layers) {
				Debug::Error("Error!");
			}
			glTextureSubImage3D(_ID, level, xoffset, yoffset, layer , width, height, 1, format, type, pixels);
		}

	};

	class CORE_API GLTextureCubeMapArray : public GLTexture {
		GLsizei _Width = 0;
		GLsizei _Height = 0;
		GLsizei _Layers = 0;
	public:
		GLTextureCubeMapArray(GLsizei levels,
			GLenum internalFormat,
			GLsizei width,
			GLsizei height,
			GLsizei layers) : GLTexture(GL_TEXTURE_CUBE_MAP_ARRAY, internalFormat) {
			_Width = width;
			_Height = height;
			_Layers = layers;
			glTextureStorage3D(_ID, levels, internalFormat, width, height, layers * 6);
		};

		void SetData(CubeMapIndex index,
			GLint level,
			GLenum format,
			GLenum type,
			const void* pixels) {
			if ((size_t)index > 5) {
				Debug::Error("Error!");
			}
			glTextureSubImage3D(_ID, level, 0, 0, 0, _Width, _Height, _Layers * 6, format, type, pixels);
		}

		void SubData(CubeMapIndex index,
			GLint level,
			GLint xoffset,
			GLint yoffset,
			GLsizei layer,
			GLsizei width,
			GLsizei height,
			GLenum format,
			GLenum type,
			const void* pixels) {
			if ((xoffset + width) > _Width || (yoffset + height) > _Height || (size_t)index > 5) {
				Debug::Error("Error!");
			}
			glTextureSubImage3D(_ID, level, xoffset, yoffset, layer * 6 + (size_t)index, width, height, 1, format, type, pixels);
		}
	};

	class CORE_API GLTexture2DMultiSample : public GLTexture {
	public:
	};

	class CORE_API GLTexture2DMultiSampleArray : public GLTexture {
	public:
	};

}

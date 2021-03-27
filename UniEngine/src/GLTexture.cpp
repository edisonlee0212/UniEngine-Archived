#include "pch.h"
#include "GLTexture.h"
using namespace UniEngine;

GLint GLTexture::m_maxAllowedTexture = 0;
std::list<GLTexture*> GLTexture::m_currentlyResidentTexture;
TextureBinding::TextureBinding()
{
	m_1d = 0;
	m_2d = 0;
	m_3d = 0;
	m_rectangle = 0;
	m_buffer = 0;
	m_cubeMap = 0;
	m_1dArray = 0;
	m_2dArray = 0;
	m_cubeMapArray = 0;
	m_2dMS = 0;
	m_2dMSArray = 0;
}

void GLTexture::MakeResidentInternal()
{
	Bind(0);
	m_handle = glGetTextureHandleARB(m_id);
	glMakeTextureHandleResidentARB(m_handle);
	m_resident = true;
}

void GLTexture::MakeNonResidentInternal()
{
	Bind(0);
	if (m_resident)
	{
		glMakeTextureHandleNonResidentARB(m_handle);
		m_resident = false;
	}
}

GLint GLTexture::GetMaxAllowedTexture()
{
	return m_maxAllowedTexture;
}

GLuint64 GLTexture::GetHandle()
{
	Bind(0);
	if (!m_resident) MakeResident();
	return m_handle;
}

bool GLTexture::IsResident() const
{
	return m_resident;
}

void GLTexture::MakeResident()
{
	if(!m_resident)
	{
		if(m_currentlyResidentTexture.size() > 1024)
		{
			auto* textureToRelease = m_currentlyResidentTexture.front();
			textureToRelease->MakeNonResidentInternal();
			m_currentlyResidentTexture.pop_front();
		}
		MakeResidentInternal();
		m_currentlyResidentTexture.push_back(this);
	}
}

void GLTexture::MakeNonResident()
{
	for(auto i = m_currentlyResidentTexture.begin(); i != m_currentlyResidentTexture.end(); ++i)
	{
		if(*i == this)
		{
			m_currentlyResidentTexture.erase(i);
			break;
		}
	}
	MakeNonResidentInternal();
}

void GLTexture::Clear(const GLint& level) const
{
	Bind(0);
	glClearTexImage(m_id, level, m_format, m_type, nullptr);
}

void GLTexture::SetInt(const GLenum& paramName, const GLint& param)
{
	if (m_resident)
	{
		MakeNonResident();
		m_resident = true;
	}
	Bind(0);
	glTextureParameteri(m_id, paramName, param);
	if (m_resident) MakeResident();
}

void GLTexture::SetFloat(const GLenum& paramName, const GLfloat& param)
{
	if (m_resident)
	{
		MakeNonResident();
		m_resident = true;
	}
	Bind(0);
	glTextureParameterf(m_id, paramName, param);
	if (m_resident) MakeResident();
}

void GLTexture::SetFloat4(const GLenum& paramName, const GLfloat* params)
{
	if (m_resident)
	{
		MakeNonResident();
		m_resident = true;
	}
	Bind(0);
	glTextureParameterfv(m_id, paramName, params);
	if (m_resident) MakeResident();
}

void GLTexture::GenerateMipMap() const
{
	Bind(0);
	glGenerateTextureMipmap(m_id);
}

void GLTexture::Bind(const GLenum& activate) const
{
	if ((GLint)activate >= m_maxAllowedTexture)
	{
		Debug::Error("Max allowed texture exceeded!");
	}
	glActiveTexture(GL_TEXTURE0 + activate);
	glBindTexture(m_type, m_id);
}

GLTexture::GLTexture(const GLenum& target, const GLenum& format)
{
	glGenTextures(1, &m_id);
	m_type = target;
	m_format = format;
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &m_id);
}

GLTexture1D::GLTexture1D(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                         const bool& immutable): GLTexture(GL_TEXTURE_1D, internalFormat)
{
	m_width = width;
	Bind(0);
	if (immutable)
		glTexStorage1D(m_type, levels, internalFormat, width);
}

void GLTexture1D::SetData(const GLint& level, const GLenum& type, const void* pixels) const
{
	Bind(0);
	glTexSubImage1D(m_type, level, 0, m_width, m_format, type, pixels);
}

void GLTexture1D::SubData(const GLint& level, const GLint& xOffset, const GLenum& type, const GLsizei& width,
                          const void* pixels) const
{
	if (xOffset + width > m_width)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage1D(m_type, level, xOffset, width, m_format, type, pixels);
}

GLTexture2D::GLTexture2D(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                         const GLsizei& height, const bool& immutable): GLTexture(GL_TEXTURE_2D, internalFormat),
                                                                        m_height(height)
{
	m_width = width;
	m_height = height;
	m_immutable = immutable;
	Bind(0);
	if (immutable)
		glTextureStorage2D(m_id, levels, internalFormat, width, height);
}

void GLTexture2D::SetData(const GLint& level, const GLenum& format, const GLenum& type, const void* pixels) const
{
	if (!m_immutable)
	{
		Debug::Error("GLTexture2D: Not Immutable!");
		return;
	}
	Bind(0);
	glTextureSubImage2D(m_id, level, 0, 0, m_width, m_height, format, type, pixels);
}

void GLTexture2D::ReSize(const GLint& level, const GLenum& internalFormat, const GLenum& format, const GLenum& type,
                         const void* pixels, const GLsizei& width, const GLsizei& height)
{
	if (m_immutable)
	{
		Debug::Error("GLTexture2D: Immutable!");
		return;
	}
	m_width = width;
	m_height = height;
	SetData(level, internalFormat,
	        format,
	        type,
	        pixels);
}

void GLTexture2D::SetData(const GLint& level, const GLenum& internalFormat, const GLenum& format, const GLenum& type,
                          const void* pixels) const
{
	if (m_immutable)
	{
		Debug::Error("GLTexture2D: Immutable!");
		return;
	}
	Bind(0);
	glTexImage2D(m_type, level, internalFormat, m_width, m_height, 0, format, type, pixels);
}

void GLTexture2D::SubData(const GLint& level, const GLenum& format, const GLint& xOffset, const GLint& yOffset,
                          const GLsizei& width, const GLsizei& height, const GLenum& type, const void* pixels) const
{
	if ((xOffset + width) > m_width || (yOffset + height) > m_height)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage2D(m_type, level, xOffset, yOffset, width, height, format, type, pixels);
}

GLTexture3D::GLTexture3D(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                         const GLsizei& height, const GLsizei& depth, const bool& immutable): GLTexture(
	GL_TEXTURE_3D, internalFormat)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	Bind(0);
	if (immutable)
		glTexStorage3D(m_type, levels, internalFormat, width, height, depth);
}

void GLTexture3D::SetData(const GLint& level, const GLenum& format, const GLenum& type, const void* pixels) const
{
	Bind(0);
	glTexSubImage3D(m_type, level, 0, 0, 0, m_width, m_height, m_depth, format, type, pixels);
}

void GLTexture3D::SubData(const GLint& level, const GLint& xOffset, const GLint& yOffset, const GLint& zOffset,
                          const GLsizei& width, const GLsizei& height, const GLsizei& depth, const GLenum& format,
                          const GLenum& type,
                          const void* pixels) const
{
	if ((xOffset + width) > m_width || (yOffset + height) > m_height || (zOffset + depth) > m_depth)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage3D(m_type, level, xOffset, yOffset, zOffset, width, height, depth, format, type, pixels);
}

GLTextureCubeMap::GLTextureCubeMap(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                                   const GLsizei& height, const bool& immutable): GLTexture(
	GL_TEXTURE_CUBE_MAP, internalFormat)
{
	m_width = width;
	m_height = height;
	Bind(0);
	if (immutable)
		glTexStorage2D(m_type, levels, internalFormat, width, height);
}

void GLTextureCubeMap::SetData(const CubeMapIndex& index, const GLint& level, const GLenum& format, const GLenum& type,
                               const void* pixels) const
{
	if ((size_t)index > 5)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTextureSubImage3D(m_id, level, 0, 0, (size_t)index, m_width, m_height, 1, format, type, pixels);
}

void GLTextureCubeMap::SetData(const CubeMapIndex& index, const GLint& level, const GLenum& internalFormat,
                               const GLenum& format, const GLenum& type, const void* pixels) const
{
	if ((size_t)index > 5)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (int)index, level, internalFormat, m_width, m_height, 0, format, type,
	             pixels);
}

void GLTextureCubeMap::SubData(const CubeMapIndex& index, const GLint& level, const GLint& xOffset,
                               const GLint& yOffset, const GLsizei& width, const GLsizei& height, const GLenum& format,
                               const GLenum& type,
                               const void* pixels) const
{
	if ((xOffset + width) > m_width || (yOffset + height) > m_height || (size_t)index > 5)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage3D(m_type, level, xOffset, yOffset, (size_t)index, width, height, 1, format, type, pixels);
}

GLTexture1DArray::GLTexture1DArray(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                                   const GLsizei& layers): GLTexture(GL_TEXTURE_1D_ARRAY, internalFormat)
{
	m_width = width;
	m_layers = layers;
	Bind(0);
	glTexStorage2D(m_type, levels, internalFormat, width, layers);
}

void GLTexture1DArray::SetData(const GLint& level, const GLenum& format, const GLenum& type, const void* pixels) const
{
	Bind(0);
	glTexSubImage2D(m_type, level, 0, 0, m_width, m_layers, format, type, pixels);
}

void GLTexture1DArray::SubData(const GLint& level, const GLint& xOffset, const GLint& layer, const GLsizei& width,
                               const GLenum& format, const GLenum& type, const void* pixels) const
{
	Bind(0);
	glTexSubImage2D(m_type, level, xOffset, layer, m_width, 1, format, type, pixels);
}

GLTexture2DArray::GLTexture2DArray(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                                   const GLsizei& height, const GLsizei& layers): GLTexture(
	GL_TEXTURE_2D_ARRAY, internalFormat)
{
	m_width = width;
	m_height = height;
	m_layers = layers;
	Bind(0);
	glTexStorage3D(m_type, levels, internalFormat, width, height, layers);
}

void GLTexture2DArray::SetData(const GLint& level, const GLenum& format, const GLenum& type, const void* pixels) const
{
	Bind(0);
	glTexSubImage3D(m_type, level, 0, 0, 0, m_width, m_height, m_layers, format, type, pixels);
}

void GLTexture2DArray::SubData(const GLint& level, const GLint& xOffset, const GLint& yOffset, const GLsizei& layer,
                               const GLsizei& width, const GLsizei& height, const GLenum& format, const GLenum& type,
                               const void* pixels) const
{
	if ((xOffset + width) > m_width || (yOffset + height) > m_height || layer >= m_layers)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage3D(m_type, level, xOffset, yOffset, layer, width, height, 1, format, type, pixels);
}

GLTextureCubeMapArray::GLTextureCubeMapArray(const GLsizei& levels, const GLenum& internalFormat, const GLsizei& width,
                                             const GLsizei& height, const GLsizei& layers): GLTexture(
	GL_TEXTURE_CUBE_MAP_ARRAY, internalFormat)
{
	m_width = width;
	m_height = height;
	m_layers = layers;
	Bind(0);
	glTexStorage3D(m_type, levels, internalFormat, width, height, layers * 6);
}

void GLTextureCubeMapArray::SetData(const CubeMapIndex& index, const GLint& level, const GLenum& format,
                                    const GLenum& type, const void* pixels) const
{
	if ((size_t)index > 5)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage3D(m_type, level, 0, 0, 0, m_width, m_height, m_layers * 6, format, type, pixels);
}

void GLTextureCubeMapArray::SubData(const CubeMapIndex& index, const GLint& level, const GLint& xOffset,
                                    const GLint& yOffset, const GLsizei& layer, const GLsizei& width,
                                    const GLsizei& height, const GLenum& format,
                                    const GLenum& type, const void* pixels) const
{
	if ((xOffset + width) > m_width || (yOffset + height) > m_height || (size_t)index > 5)
	{
		Debug::Error("Error!");
	}
	Bind(0);
	glTexSubImage3D(m_type, level, xOffset, yOffset, layer * 6 + (size_t)index, width, height, 1, format, type, pixels);
}

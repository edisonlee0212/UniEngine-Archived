#include "pch.h"
#include "GLCore.h"
#include "GLBuffer.h"
#include "GLProgram.h"
inline void UniEngine::GLCore::Init()
{
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &GLTexture::m_maxAllowedTexture);
	GLTexture::m_currentBoundTextures.resize(GLTexture::m_maxAllowedTexture);
}
void UniEngine::GLCore::PreUpdate()
{
	for (auto& i : GLTexture::m_currentBoundTextures) i.clear();
}
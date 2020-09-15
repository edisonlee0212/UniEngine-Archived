#include "pch.h"
#include "GLCore.h"
inline void UniEngine::GLCore::Init()
{
	int max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
	GLTexture::_MaxAllowedTexture = max;
}

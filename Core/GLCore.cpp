#include "pch.h"
#include "GLCore.h"
void UniEngine::GLCore::Init()
{
	int max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
	GLTexture::_MaxAllowedTexture = max;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max);
	GLVAO::_MaxAllowedVBO = max;
}

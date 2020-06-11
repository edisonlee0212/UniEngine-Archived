#include "pch.h"
#include "PointLightShadowMap.h"
using namespace UniEngine;

UniEngine::PointLightShadowMap::PointLightShadowMap(size_t amount, float resolutionX, float resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_DepthCubeMapArray = new GLTexture();
	_DepthCubeMapArray->SetCubeMapArray(0, GL_DEPTH_COMPONENT, _ResolutionX, _ResolutionY, amount, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	_DepthCubeMapArray->SetIntParameter(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_GREATER);
}

GLTexture* UniEngine::PointLightShadowMap::DepthCubeMapArray()
{
	return _DepthCubeMapArray;
}

void UniEngine::PointLightShadowMap::Bind(GLint layer)
{
	AttachTexture(_DepthCubeMapArray, GL_DEPTH_ATTACHMENT);
	RenderTarget::Bind();
}

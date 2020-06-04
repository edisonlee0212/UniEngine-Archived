#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t amount, float resolutionX, float resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	//_DepthMap = SetTexture2D(GL_DEPTH_ATTACHMENT, 0, GL_DEPTH_COMPONENT, 0, GL_DEPTH_COMPONENT);
	_DepthMap = new GLTexture();
	_DepthMap->SetImage2DArray(0, GL_DEPTH_COMPONENT, _ResolutionX, _ResolutionY, amount, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DepthMap->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
}

GLTexture* UniEngine::DirectionalLightShadowMap::DepthMap()
{
	return _DepthMap;
}

void UniEngine::DirectionalLightShadowMap::Bind(GLint layer)
{
	AttachTextureLayer(_DepthMap, GL_DEPTH_ATTACHMENT, layer);
	RenderTarget::Bind();
}



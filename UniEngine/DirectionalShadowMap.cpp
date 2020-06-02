#include "DirectionalShadowMap.h"
using namespace UniEngine;
UniEngine::DirectionalShadowMap::DirectionalShadowMap(float resolutionX, float resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_DepthMap = SetTexture2D(GL_DEPTH_ATTACHMENT, 0, GL_DEPTH_COMPONENT, 0, GL_DEPTH_COMPONENT);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMap->SetIntParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DepthMap->SetFloat4Parameter(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}

GLTexture* UniEngine::DirectionalShadowMap::DepthMap()
{
	return _DepthMap;
}



#include "PointShadowMap.h"
using namespace UniEngine;

UniEngine::PointShadowMap::PointShadowMap(float resolutionX, float resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_DepthCubeMap = SetCubeMap(GL_DEPTH_ATTACHMENT, 0, GL_DEPTH_COMPONENT, 0, GL_DEPTH_COMPONENT);
	_DepthCubeMap->SetIntParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_DepthCubeMap->SetIntParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_DepthCubeMap->SetIntParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthCubeMap->SetIntParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_DepthCubeMap->SetIntParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

GLTexture* UniEngine::PointShadowMap::DepthMap()
{
	return _DepthCubeMap;
}

#include "pch.h"
#include "SpotLightShadowMap.h"

void UniEngine::SpotLightShadowMap::Allocate()
{
	_DepthMap = std::make_unique<GLTexture2D>(1, GL_DEPTH_COMPONENT32, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY);
	_DepthMap->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMap->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMap->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_DepthMap->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_DepthMap->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	_DepthMap->MakeResident();
	AttachTexture(_DepthMap.get(), GL_DEPTH_ATTACHMENT);
}

UniEngine::SpotLightShadowMap::SpotLightShadowMap(size_t resolution)
{
	SetResolution(resolution);
}

void UniEngine::SpotLightShadowMap::SetResolution(size_t resolution)
{
	_ResolutionX = _ResolutionY = resolution;
	Allocate();
}

std::unique_ptr<UniEngine::GLTexture2D>& UniEngine::SpotLightShadowMap::DepthMap()
{
	return _DepthMap;
}

void UniEngine::SpotLightShadowMap::Bind()
{
	RenderTarget::Bind();
}

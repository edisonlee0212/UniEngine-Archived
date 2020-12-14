#include "pch.h"
#include "PointLightShadowMap.h"
using namespace UniEngine;

void PointLightShadowMap::Allocate()
{
	_DepthMapArray = std::make_unique<GLTexture2DArray>(1, GL_DEPTH_COMPONENT32, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY, (GLsizei)6);
	_DepthMapArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_DepthMapArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_DepthMapArray->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	_DepthMapArray->MakeResident();
	AttachTexture(_DepthMapArray.get(), GL_DEPTH_ATTACHMENT);
}

UniEngine::PointLightShadowMap::PointLightShadowMap(size_t resolution)
{
	SetResolution(resolution);
}

void PointLightShadowMap::SetResolution(size_t resolution)
{
	_ResolutionX = _ResolutionY = resolution;
	Allocate();
}

std::unique_ptr<GLTexture2DArray>& UniEngine::PointLightShadowMap::DepthMapArray()
{
	return _DepthMapArray;
}

void UniEngine::PointLightShadowMap::Bind()
{
	RenderTarget::Bind();
}

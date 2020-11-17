#include "pch.h"
#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
void UniEngine::DirectionalLightShadowMap::Allocate()
{

	
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	_DepthMapDepthArray = std::make_unique<GLTexture2DArray>(1, GL_DEPTH_COMPONENT32, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY, (GLsizei)4);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DepthMapDepthArray->SetFloat4(GL_TEXTURE_BORDER_COLOR, borderColor);
	_DepthMapDepthArray->MakeResident();
	AttachTexture(_DepthMapDepthArray.get(), GL_DEPTH_ATTACHMENT);
}
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t resolution)
{
	_ResolutionX = _ResolutionY = resolution;
	Allocate();
	
}

void DirectionalLightShadowMap::SetResolution(size_t resolution)
{
	_ResolutionX = _ResolutionY = resolution;
	Allocate();
	
}


std::unique_ptr<GLTexture2DArray>& DirectionalLightShadowMap::DepthMapDepthArray()
{
	return _DepthMapDepthArray;
}

void UniEngine::DirectionalLightShadowMap::Bind()
{
	RenderTarget::Bind();
}



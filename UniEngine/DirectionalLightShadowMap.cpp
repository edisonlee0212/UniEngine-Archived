#include "pch.h"
#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
void UniEngine::DirectionalLightShadowMap::Allocate()
{
	if (_DepthMapArray != nullptr) delete _DepthMapArray;
	if (_EnableVSM) {
		_DepthMapArray = new GLTexture2DArray(1, GL_RG32F, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY, (GLsizei)_LightAmount * 4);
	}
	else
	{
		_DepthMapArray = new GLTexture2DArray(1, GL_R32F, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY, (GLsizei)_LightAmount * 4);
	}
	_DepthMapArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DepthMapArray->SetFloat4(GL_TEXTURE_BORDER_COLOR, borderColor);

	if (_DepthMapDepthArray != nullptr) delete _DepthMapDepthArray;
	_DepthMapDepthArray = new GLTexture2DArray(1, GL_DEPTH_COMPONENT32, (GLsizei)_ResolutionX, (GLsizei)_ResolutionY, (GLsizei)_LightAmount * 4);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapDepthArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DepthMapDepthArray->SetFloat4(GL_TEXTURE_BORDER_COLOR, borderColor);

	AttachTexture(_DepthMapArray, GL_COLOR_ATTACHMENT0);
	AttachTexture(_DepthMapDepthArray, GL_DEPTH_ATTACHMENT);
}
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t amount, size_t resolutionX, size_t resolutionY, bool enableVSM)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_LightAmount = amount;
	_EnableVSM = enableVSM;
	Allocate();
}

void UniEngine::DirectionalLightShadowMap::SetVSM(bool enabled)
{
	if (enabled == _EnableVSM) return;
	_EnableVSM = enabled;
	Allocate();
}



void UniEngine::DirectionalLightShadowMap::SetLightAmount(size_t value)
{
	if (_LightAmount == value) return;
	_LightAmount = value;
	Allocate(); 
}


GLTexture2DArray* UniEngine::DirectionalLightShadowMap::DepthMapArray()
{
	return _DepthMapArray;
}

void UniEngine::DirectionalLightShadowMap::Bind()
{

	RenderTarget::Bind();
}



#include "pch.h"
#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t amount, float resolutionX, float resolutionY, bool enableVSM, bool enableEVSM)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_LightAmount = amount;
	_EnableVSM = enableVSM;
	_EnableEVSM = enableEVSM;
	_DepthMapArray = new GLTexture();
	if (enableVSM) {
		if (enableEVSM) {
			_DepthMapArray->SetImage2DArray(0, GL_RGBA32F_ARB, _ResolutionX, _ResolutionY, amount * 4, 0, GL_RGBA, GL_FLOAT, NULL);
		}
		else _DepthMapArray->SetImage2DArray(0, GL_RG32F, _ResolutionX, _ResolutionY, amount * 4, 0, GL_RG, GL_FLOAT, NULL);
	}
	else
	{
		_DepthMapArray->SetImage2DArray(0, GL_R32F, _ResolutionX, _ResolutionY, amount * 4, 0, GL_RED, GL_FLOAT, NULL);
	}
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DepthMapArray->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

	_DepthMapDepthArray = new GLTexture();
	_DepthMapDepthArray->SetImage2DArray(0, GL_DEPTH_COMPONENT32, _ResolutionX, _ResolutionY, amount * 4, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

	AttachTexture(_DepthMapArray, GL_COLOR_ATTACHMENT0);
	AttachTexture(_DepthMapDepthArray, GL_DEPTH_ATTACHMENT);
}

void UniEngine::DirectionalLightShadowMap::SetVSM(bool enabled)
{
	if (enabled == _EnableVSM) return;
	_EnableVSM = enabled;
	if (enabled) {
		if (_EnableEVSM) {
			_DepthMapArray->SetImage2DArray(0, GL_RGBA32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RGBA, GL_FLOAT, NULL);
		}
		else {
			_DepthMapArray->SetImage2DArray(0, GL_RG32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RG, GL_FLOAT, NULL);
		}
	}
	else {
		_DepthMapArray->SetImage2DArray(0, GL_R32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RED, GL_FLOAT, NULL);
	}
	AttachTexture(_DepthMapArray, GL_COLOR_ATTACHMENT0);
}

void UniEngine::DirectionalLightShadowMap::SetEVSM(bool enabled)
{
	if (enabled == _EnableEVSM) return;
	_EnableEVSM = enabled;
	if (_EnableVSM) {
		if (enabled) {
			_DepthMapArray->SetImage2DArray(0, GL_RGBA32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RGBA, GL_FLOAT, NULL);
		}
		else {
			_DepthMapArray->SetImage2DArray(0, GL_RG32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RG, GL_FLOAT, NULL);
		}
	}
	else {
		_DepthMapArray->SetImage2DArray(0, GL_R32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RED, GL_FLOAT, NULL);
	}
	AttachTexture(_DepthMapArray, GL_COLOR_ATTACHMENT0);
}

void UniEngine::DirectionalLightShadowMap::SetLightAmount(size_t value)
{
	if (_LightAmount == value) return;
	_LightAmount = value;
	if (_EnableVSM) {
		if (_EnableEVSM) {
			_DepthMapArray->SetImage2DArray(0, GL_RGBA32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RGBA, GL_FLOAT, NULL);
		}
		else {
			_DepthMapArray->SetImage2DArray(0, GL_RG32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RG, GL_FLOAT, NULL);
		}
	}
	else {
		_DepthMapArray->SetImage2DArray(0, GL_R32F, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_RED, GL_FLOAT, NULL);
	}
	_DepthMapDepthArray->SetImage2DArray(0, GL_DEPTH_COMPONENT32, _ResolutionX, _ResolutionY, _LightAmount * 4, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	AttachTexture(_DepthMapArray, GL_COLOR_ATTACHMENT0);
	AttachTexture(_DepthMapDepthArray, GL_DEPTH_ATTACHMENT);

}


GLTexture* UniEngine::DirectionalLightShadowMap::DepthMapArray()
{
	return _DepthMapArray;
}

void UniEngine::DirectionalLightShadowMap::Bind()
{
	
	RenderTarget::Bind();
}



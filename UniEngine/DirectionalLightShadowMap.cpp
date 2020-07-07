#include "pch.h"
#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t amount, float resolutionX, float resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_DepthMapArray = new GLTexture();
	_DepthMapArray->SetImage2DArray(0, GL_RGBA32F, _ResolutionX, _ResolutionY, amount, 0, GL_RGBA, GL_FLOAT, NULL);

	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DepthMapArray->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

	_DepthMapDepthArray = new GLTexture();
	_DepthMapDepthArray->SetImage2DArray(0, GL_DEPTH_COMPONENT32, _ResolutionX, _ResolutionY, amount, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapDepthArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

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



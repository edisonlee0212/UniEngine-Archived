#include "pch.h"
#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t amount, float resolutionX, float resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	//_DepthMap = SetTexture2D(GL_DEPTH_ATTACHMENT, 0, GL_DEPTH_COMPONENT, 0, GL_DEPTH_COMPONENT);
	_DepthMapArray = new GLTexture();
	_DepthMapArray->SetImage2DArray(0, GL_DEPTH_COMPONENT, _ResolutionX, _ResolutionY, amount, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	_DepthMapArray->SetIntParameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_GEQUAL);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_DepthMapArray->SetFloat4Parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
}

GLTexture* UniEngine::DirectionalLightShadowMap::DepthCubeMapArray()
{
	return _DepthMapArray;
}

void UniEngine::DirectionalLightShadowMap::Bind(GLint layer)
{
	AttachTextureLayer(_DepthMapArray, GL_DEPTH_ATTACHMENT, layer);
	RenderTarget::Bind();
}



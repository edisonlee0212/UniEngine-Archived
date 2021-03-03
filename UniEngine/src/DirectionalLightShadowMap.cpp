#include "pch.h"
#include "DirectionalLightShadowMap.h"
using namespace UniEngine;
void UniEngine::DirectionalLightShadowMap::Allocate()
{
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_depthMapArray = std::make_unique<GLTexture2DArray>(1, GL_DEPTH_COMPONENT32, (GLsizei)m_resolutionX, (GLsizei)m_resolutionY, (GLsizei)4);
	m_depthMapArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_depthMapArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_depthMapArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	m_depthMapArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	m_depthMapArray->SetFloat4(GL_TEXTURE_BORDER_COLOR, borderColor);
	m_depthMapArray->MakeResident();
	AttachTexture(m_depthMapArray.get(), GL_DEPTH_ATTACHMENT);
}
UniEngine::DirectionalLightShadowMap::DirectionalLightShadowMap(size_t resolution)
{
	SetResolution(resolution);
}

void DirectionalLightShadowMap::SetResolution(size_t resolution)
{
	m_resolutionX = m_resolutionY = resolution;
	Allocate();
}


std::unique_ptr<GLTexture2DArray>& DirectionalLightShadowMap::DepthMapArray()
{
	return m_depthMapArray;
}

void UniEngine::DirectionalLightShadowMap::Bind()
{
	RenderTarget::Bind();
}



#include "pch.h"
#include "SpotLightShadowMap.h"

void UniEngine::SpotLightShadowMap::Allocate()
{
	m_depthMap = std::make_unique<GLTexture2D>(1, GL_DEPTH_COMPONENT32, (GLsizei)m_resolutionX, (GLsizei)m_resolutionY);
	m_depthMap->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_depthMap->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_depthMap->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_depthMap->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_depthMap->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	m_depthMap->MakeResident();
	AttachTexture(m_depthMap.get(), GL_DEPTH_ATTACHMENT);
}

UniEngine::SpotLightShadowMap::SpotLightShadowMap(size_t resolution)
{
	SetResolution(resolution);
}

void UniEngine::SpotLightShadowMap::SetResolution(size_t resolution)
{
	m_resolutionX = m_resolutionY = resolution;
	Allocate();
}

std::unique_ptr<UniEngine::GLTexture2D>& UniEngine::SpotLightShadowMap::DepthMap()
{
	return m_depthMap;
}

void UniEngine::SpotLightShadowMap::Bind()
{
	RenderTarget::Bind();
}

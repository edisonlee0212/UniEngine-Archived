#include "pch.h"
#include "PointLightShadowMap.h"
using namespace UniEngine;

void PointLightShadowMap::Allocate()
{
	m_depthMapArray = std::make_unique<GLTexture2DArray>(1, GL_DEPTH_COMPONENT32, (GLsizei)m_resolutionX, (GLsizei)m_resolutionY, (GLsizei)6);
	m_depthMapArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_depthMapArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_depthMapArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_depthMapArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_depthMapArray->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	m_depthMapArray->MakeResident();
	AttachTexture(m_depthMapArray.get(), GL_DEPTH_ATTACHMENT);
}

UniEngine::PointLightShadowMap::PointLightShadowMap(size_t resolution)
{
	SetResolution(resolution);
}

void PointLightShadowMap::SetResolution(size_t resolution)
{
	m_resolutionX = m_resolutionY = resolution;
	Allocate();
}

std::unique_ptr<GLTexture2DArray>& UniEngine::PointLightShadowMap::DepthMapArray()
{
	return m_depthMapArray;
}

void UniEngine::PointLightShadowMap::Bind()
{
	RenderTarget::Bind();
}

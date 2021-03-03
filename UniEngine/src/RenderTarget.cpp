#include "pch.h"
#include "RenderTarget.h"
#include "RenderManager.h"
using namespace UniEngine;

UniEngine::RenderTarget::RenderTarget()
{
	m_bound = false;
	m_frameBuffer = std::make_unique<GLFrameBuffer>();
	m_resolutionX = 0;
	m_resolutionY = 0;
}

UniEngine::RenderTarget::RenderTarget(size_t width, size_t height)
{
	m_bound = false;
	m_frameBuffer = std::make_unique<GLFrameBuffer>();
	m_resolutionX = width;
	m_resolutionY = height;
}

glm::vec2 UniEngine::RenderTarget::GetResolution() const
{
	return glm::vec2(m_resolutionX, m_resolutionY);
}

void RenderTarget::SetResolution(size_t width, size_t height)
{
	m_resolutionX = width;
	m_resolutionY = height;
}

float UniEngine::RenderTarget::GetResolutionRatio() const
{
	if (m_resolutionX == 0 || m_resolutionY == 0) return 0;
	return (float)m_resolutionX / (float)m_resolutionY;
}

void UniEngine::RenderTarget::AttachTextureLayer(GLTexture* texture, GLenum attachPoint, GLint layer) const
{
	if (m_bound) {
		Debug::Error("Error");
		return;
	}
	m_frameBuffer->AttachTextureLayer(texture, attachPoint, layer);
}

void UniEngine::RenderTarget::AttachTexture(GLTexture* texture, GLenum attachPoint) const
{
	if (m_bound) {
		Debug::Error("Error");
		return;
	}
	m_frameBuffer->AttachTexture(texture, attachPoint);
}

void UniEngine::RenderTarget::AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLenum attachPoint) const
{
	if (m_bound) {
		Debug::Error("Error");
		return;
	}
	m_frameBuffer->AttachRenderBuffer(renderBuffer, attachPoint);
}

void UniEngine::RenderTarget::Bind() const
{
	if (m_bound) {
		Debug::Error("Error");
		return;
	}
	m_frameBuffer->Bind();
	m_frameBuffer->Check();
	m_frameBuffer->ViewPort(glm::vec4(0, 0, m_resolutionX, m_resolutionY));
}

void UniEngine::RenderTarget::Clear() const
{
	m_frameBuffer->Clear();
}

std::unique_ptr<GLFrameBuffer>& RenderTarget::GetFrameBuffer()
{
	return m_frameBuffer;
}

void UniEngine::RenderTarget::BindDefault()
{
	GLFrameBuffer::BindDefault();
}

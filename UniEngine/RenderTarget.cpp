#include "RenderTarget.h"
#include "Debug.h"
using namespace UniEngine;

UniEngine::RenderTarget::RenderTarget(uint width, uint height) : _Width(width), _Height(height)
{
	_Bound = false;
	_FrameBuffer = new GLFrameBuffer();
}

void UniEngine::RenderTarget::AttachTexture(GLTexture* texture, GLint attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachTexture(texture, attachPoint);
}

void UniEngine::RenderTarget::AttachRenderBuffer(GLRenderBuffer* renderBuffer, GLint attachPoint)
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	_FrameBuffer->AttachRenderBuffer(renderBuffer, attachPoint);
}

void UniEngine::RenderTarget::Bind()
{
	if (_Bound) {
		Debug::Error("Error");
		return;
	}
	if (_FrameBuffer->Color()) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer->ID());
}

void UniEngine::RenderTarget::Unbind()
{
	if (!_Bound) {
		Debug::Error("Error");
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

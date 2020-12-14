#include "pch.h"
#include "CameraComponent.h"
#include "RenderManager.h"
void UniEngine::CameraComponent::ResizeResolution(int x, int y)
{
	const auto originalResolution = _GBuffer->GetResolution();
	if (static_cast<int>(originalResolution.x) == x && static_cast<int>(originalResolution.y) == y) return;
	_ResolutionX = x > 0 ? x : 1;
	_ResolutionY = y > 0 ? y : 1;
	_GBuffer->SetResolution(_ResolutionX, _ResolutionY);
	_GPositionBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GNormalBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GColorSpecularBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GDepthBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, _ResolutionX, _ResolutionY);

	_GBuffer->AttachRenderBuffer(_GDepthBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	_GBuffer->AttachTexture(_GPositionBuffer.get(), GL_COLOR_ATTACHMENT0);
	_GBuffer->AttachTexture(_GNormalBuffer.get(), GL_COLOR_ATTACHMENT1);
	_GBuffer->AttachTexture(_GColorSpecularBuffer.get(), GL_COLOR_ATTACHMENT2);

	_SSAO->SetResolution(_ResolutionX, _ResolutionY);
	_SSAOBlurFilter->SetResolution(_ResolutionX, _ResolutionY);
	_SSAOColor->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_SSAOBlur->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_SSAO->AttachTexture(_SSAOColor.get(), GL_COLOR_ATTACHMENT0);
	_SSAOBlurFilter->AttachTexture(_SSAOBlur.get(), GL_COLOR_ATTACHMENT0);

	_Camera->SetResolution(_ResolutionX, _ResolutionY);
}

UniEngine::CameraComponent::CameraComponent()
{
	_ResolutionX = 1;
	_ResolutionY = 1;
	_Camera = std::make_unique<Camera>(_ResolutionX, _ResolutionY, 0.1f, 500.0f);
	
	_GBuffer = std::make_unique<RenderTarget>(0, 0);

	_GDepthBuffer = std::make_unique<GLRenderBuffer>();

	_GPositionBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_GPositionBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GPositionBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_GNormalBuffer = std::make_unique <GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_GNormalBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GNormalBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_GColorSpecularBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_SSAO = std::make_unique<RenderTarget>(0, 0);
	_SSAOColor = std::make_unique<GLTexture2D>(0, GL_R32F, 0, 0, false);
	_SSAOColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_SSAOBlurFilter = std::make_unique<RenderTarget>();
	_SSAOBlur = std::make_unique<GLTexture2D>(0, GL_R32F, 0, 0, false);
	_SSAOBlur->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOBlur->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// generate noise texture
	// ----------------------
	std::vector<glm::vec3> ssaoNoise;
	for (unsigned int i = 0; i < 16; i++)
	{
		glm::vec3 noise(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), 0.0f); // rotate around z-axis (in tangent space)
		ssaoNoise.push_back(noise);
	}
	_SSAONoise = std::make_unique<GLTexture2D>(0, GL_RGBA32F, 0, 0, false);
	_SSAONoise->ReSize(0, GL_RGBA32F, GL_RGB, GL_FLOAT, ssaoNoise.data(), 4, 4);
	_SSAONoise->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAONoise->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//#pragma endregion
	ResizeResolution(_ResolutionX, _ResolutionY);
	SetEnabled(true);
}

UniEngine::CameraComponent::~CameraComponent()
{
	if (RenderManager::GetMainCamera() == this) {
		RenderManager::SetMainCamera(nullptr);
	}
}

void UniEngine::CameraComponent::OnGui()
{
	ImGui::Checkbox("Skybox", &DrawSkyBox);
	bool savedState = _IsMainCamera;
	ImGui::Checkbox("Main Camera", &_IsMainCamera);
	if(savedState != _IsMainCamera)
	{
		if(_IsMainCamera)
		{
			RenderManager::SetMainCamera(this);
		}else
		{
			RenderManager::SetMainCamera(nullptr);
		}
	}
	if(!DrawSkyBox)
	{
		ImGui::ColorEdit3("Clear Color", (float*)(void*)&ClearColor);
	}
	_Camera->OnGui();
}

std::unique_ptr<UniEngine::Camera>& UniEngine::CameraComponent::GetCamera()
{
	return _Camera;
}

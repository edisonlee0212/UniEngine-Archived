#include "pch.h"
#include "SSAO.h"

#include "Default.h"
#include "Texture2D.h"

UniEngine::SSAO::SSAO()
{
	/*
	 * _SSAO = std::make_unique<RenderTarget>(_ResolutionX, _ResolutionY);
	_SSAOColor = std::make_unique<GLTexture2D>(0, GL_R32F, _ResolutionX, _ResolutionY, false);
	_SSAOColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SSAOColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_SSAOColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_SSAO->AttachTexture(_SSAOColor.get(), GL_COLOR_ATTACHMENT0);
	
	_SSAOBlurFilter = std::make_unique<RenderTarget>();
	_SSAOBlur = std::make_unique<GLTexture2D>(0, GL_R32F, _ResolutionX, _ResolutionY, false);
	_SSAOBlur->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOBlur->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SSAOBlur->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_SSAOBlur->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_SSAOBlurFilter->AttachTexture(_SSAOBlur.get(), GL_COLOR_ATTACHMENT0);
	 */
	/*
	 * _SSAOGeometryPass = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOBlur.frag"));

	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);

	_SSAOBlurPass = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	 */
}

void UniEngine::SSAO::ResizeResolution(int x, int y)
{
	/*
	 * _SSAO->SetResolution(_ResolutionX, _ResolutionY);
	_SSAOBlurFilter->SetResolution(_ResolutionX, _ResolutionY);
	_SSAOColor->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_SSAOBlur->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	 */
}

void UniEngine::SSAO::Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const
{
	/*
	 *
	 * if (_EnableSSAO) {
		cameraComponent->_SSAO->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_SSAOGeometryPass->Bind();
		cameraComponent->_GPositionBuffer->Bind(3);
		cameraComponent->_GNormalBuffer->Bind(4);
		cameraComponent->_SSAONoise->Bind(5);
		_SSAOGeometryPass->SetFloat("radius", _SSAOKernelRadius);
		_SSAOGeometryPass->SetFloat("bias", _SSAOKernelBias);
		_SSAOGeometryPass->SetFloat("factor", _SSAOFactor);
		_SSAOGeometryPass->SetInt("kernelSize", _SSAOSampleSize);
		_SSAOGeometryPass->SetInt("gPositionShadow", 3);
		_SSAOGeometryPass->SetInt("gNormalShininess", 4);
		_SSAOGeometryPass->SetInt("texNoise", 5);
		_SSAOGeometryPass->SetFloat2("noiseScale", cameraComponent->GetResolution() / _SSAOScale);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		cameraComponent->_SSAOBlurFilter->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		cameraComponent->_SSAOColor->Bind(3);
		_SSAOBlurPass->SetInt("ssaoInput", 3);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	 */
}

void UniEngine::SSAO::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
	/*
	 * ImGui::Checkbox("Enable SSAO", &_EnableSSAO);
		if (_EnableSSAO && ImGui::TreeNode("SSAO")) {
			ImGui::DragFloat("Radius", &_SSAOKernelRadius, 0.01f, 0.1f, 5.0f);
			ImGui::DragFloat("Bias", &_SSAOKernelBias, 0.001f, 0.0f, 1.0f);
			ImGui::DragFloat("Factor", &_SSAOFactor, 0.01f, 1.0f, 10.0f);
			ImGui::DragInt("Sample Size", &_SSAOSampleSize, 1, 0, 64);
			ImGui::TreePop();
		}
	 */
}

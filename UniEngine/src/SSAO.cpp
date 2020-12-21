#include "pch.h"
#include "SSAO.h"

#include "Default.h"
#include "Texture2D.h"

UniEngine::SSAO::SSAO()
{
	_Bezier2D = { 1.0f, 0.0f, 0.9f, 1.0f };
	_Type = PostProcessingLayerType::SSAO;
	_OriginalColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	_OriginalColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_OriginalColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_OriginalColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_OriginalColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_OriginalColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	_SSAOPosition = std::make_unique<GLTexture2D>(0, GL_R32F, 1, 1, false);
	_SSAOPosition->SetData(0, GL_R32F, GL_RED, GL_FLOAT, 0);
	_SSAOPosition->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOPosition->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SSAOPosition->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_SSAOPosition->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	_SSAOBlur = std::make_unique<GLTexture2D>(0, GL_R32F, 1, 1, false);
	_SSAOBlur->SetData(0, GL_R32F, GL_RED, GL_FLOAT, 0);
	_SSAOBlur->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SSAOBlur->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SSAOBlur->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_SSAOBlur->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));

	std::string fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOGeometry.frag"));

	_GeometryProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BlurFilter.frag"));

	_BlurProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOCombine.frag"));

	_CombineProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);
}

void UniEngine::SSAO::ResizeResolution(int x, int y)
{
	_OriginalColor->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	_SSAOPosition->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
	_SSAOBlur->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
}

void UniEngine::SSAO::Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	unsigned int enums[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	Default::GLPrograms::ScreenVAO->Bind();

	_GeometryProgram->Bind();
	renderTarget.AttachTexture(_OriginalColor.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.AttachTexture(_SSAOPosition.get(), GL_COLOR_ATTACHMENT1);
	renderTarget.Bind();
	glDrawBuffers(2, enums);
	cameraComponent->_ColorTexture->Texture()->Bind(0);
	cameraComponent->_GPositionBuffer->Bind(1);
	cameraComponent->_GNormalBuffer->Bind(2);
	_GeometryProgram->SetInt("image", 0);
	_GeometryProgram->SetInt("gPositionShadow", 1);
	_GeometryProgram->SetInt("gNormalShininess", 2);
	_GeometryProgram->SetFloat("radius", _SSAOKernelRadius);
	_GeometryProgram->SetFloat("bias", _SSAOKernelBias);
	_GeometryProgram->SetFloat("noiseScale", _SSAOScale);
	_GeometryProgram->SetInt("kernelSize", _SSAOSampleSize);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	_BlurProgram->Bind();
	renderTarget.AttachTexture(_SSAOBlur.get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_SSAOPosition->Bind(0);
	_BlurProgram->SetInt("image", 0);
	_BlurProgram->SetFloat("sampleScale", _BlurScale);
	_BlurProgram->SetBool("horizontal", false);
	_BlurProgram->SetFloat4("bezier", _Bezier2D.ControlPoints[0], _Bezier2D.ControlPoints[1], _Bezier2D.ControlPoints[2], _Bezier2D.ControlPoints[3]);
	_BlurProgram->SetInt("diffusion", _Diffusion);
	_BlurProgram->SetFloat("intensity", _Intensity);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	renderTarget.AttachTexture(_SSAOPosition.get(), GL_COLOR_ATTACHMENT0);
	_SSAOBlur->Bind(0);
	_BlurProgram->SetBool("horizontal", true);
	glDrawArrays(GL_TRIANGLES, 0, 6);


	_CombineProgram->Bind();
	renderTarget.AttachTexture(cameraComponent->_ColorTexture->Texture().get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_OriginalColor->Bind(0);
	_SSAOPosition->Bind(1);
	_CombineProgram->SetInt("originalColor", 0);
	_CombineProgram->SetInt("ao", 1);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UniEngine::SSAO::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
	ImGui::Checkbox("Enabled", &_Enabled);
	if (_Enabled) {
		if (ImGui::TreeNode("SSAO")) {
			ImGui::DragFloat("Radius##SSAO", &_SSAOKernelRadius, 0.01f, 0.1f, 5.0f);
			ImGui::DragFloat("Bias##SSAO", &_SSAOKernelBias, 0.001f, 0.0f, 1.0f);
			ImGui::DragInt("Sample Size##SSAO", &_SSAOSampleSize, 1, 0, 64);
			ImGui::DragFloat("Sample Scale##SSAO", &_BlurScale, 0.001f, 0.0f, 1.0f);
			ImGui::TreePop();

			ImGui::Separator();
			ImGui::DragFloat("Intensity##SSAO", &_Intensity, 0.001f, 0.001f, 1.0f);
			ImGui::DragInt("Diffusion##SSAO", &_Diffusion, 1, 1.0f, 64.0f);
			_Bezier2D.Graph("Bezier##SSAO");
			ImGui::Separator();
			ImGui::DragFloat("Threshold##SSAO", &_Threshold, 0.01f, 0.0f, 5.0f);
			ImGui::DragFloat("Clamp##SSAO", &_Clamp, 0.01f, 0.0f, 5.0f);

			ImGui::Image((ImTextureID)_OriginalColor->ID(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Image((ImTextureID)_SSAOPosition->ID(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Image((ImTextureID)_SSAOBlur->ID(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		}
	}
}

#include "pch.h"
#include "SSAO.h"

#include "Default.h"
#include "Texture2D.h"

void UniEngine::SSAO::Init()
{
	_Name = "SSAO";
	Graph = BezierCubic2D();
	Graph.ControlPoints[1] = glm::vec2(1, 0);
	Graph.ControlPoints[2] = glm::vec2(0.9, 1.0);
	_OriginalColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	_OriginalColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_OriginalColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_OriginalColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_OriginalColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_OriginalColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	_Position = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	_Position->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_Position->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_Position->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_Position->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_Position->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
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
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThroughViewRay.vert"));

	std::string fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/PositionReconstruct.frag"));

	_PositionReconstructProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOGeometry.frag"));

	_GeometryProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));
	
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
	_Position->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
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

	_PositionReconstructProgram->Bind();
	renderTarget.AttachTexture(_Position.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	cameraComponent->_DepthStencilBuffer->Bind(0);
	_PositionReconstructProgram->SetInt("inputTex", 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	_GeometryProgram->Bind();
	renderTarget.AttachTexture(_OriginalColor.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.AttachTexture(_SSAOPosition.get(), GL_COLOR_ATTACHMENT1);
	glDrawBuffers(2, enums);
	cameraComponent->_ColorTexture->Texture()->Bind(0);
	//_Position->Bind(1);
	cameraComponent->_GPositionBuffer->Bind(1);
	cameraComponent->_GNormalBuffer->Bind(2);
	_GeometryProgram->SetInt("image", 0);
	_GeometryProgram->SetInt("gPositionShadow", 1);
	_GeometryProgram->SetInt("gNormalShininess", 2);
	_GeometryProgram->SetFloat("radius", SSAOKernelRadius);
	_GeometryProgram->SetFloat("bias", SSAOKernelBias);
	_GeometryProgram->SetFloat("noiseScale", SSAOScale);
	_GeometryProgram->SetInt("kernelSize", SSAOSampleSize);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	_BlurProgram->Bind();
	renderTarget.AttachTexture(_SSAOBlur.get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_SSAOPosition->Bind(0);
	_BlurProgram->SetInt("image", 0);
	_BlurProgram->SetFloat("sampleScale", BlurScale);
	_BlurProgram->SetBool("horizontal", false);
	_BlurProgram->SetFloat4("bezier", Graph.ControlPoints[1][0], Graph.ControlPoints[1][1], Graph.ControlPoints[2][0], Graph.ControlPoints[2][1]);
	_BlurProgram->SetInt("diffusion", Diffusion);
	_BlurProgram->SetFloat("intensity", Intensity);
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
	if (ImGui::TreeNode("SSAO Settings")) {
		ImGui::DragFloat("Radius##SSAO", &SSAOKernelRadius, 0.01f, 0.1f, 5.0f);
		ImGui::DragFloat("Bias##SSAO", &SSAOKernelBias, 0.001f, 0.0f, 1.0f);
		ImGui::DragInt("Sample Size##SSAO", &SSAOSampleSize, 1, 1, 64);
		ImGui::DragFloat("Blur Scale##SSAO", &BlurScale, 0.001f, 0.01f, 1.0f);
		ImGui::DragFloat("Intensity##SSAO", &Intensity, 0.001f, 0.001f, 1.0f);
		ImGui::DragInt("Diffusion##SSAO", &Diffusion, 1.0f, 1, 64);
		Graph.Graph("Bezier##SSAO");
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Debug##SSAO"))
	{
		ImGui::Image((ImTextureID)cameraComponent->_GPositionBuffer->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)_Position->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)_OriginalColor->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)_SSAOPosition->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)_SSAOBlur->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::TreePop();
	}
}

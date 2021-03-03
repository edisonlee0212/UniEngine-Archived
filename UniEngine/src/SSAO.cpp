#include "pch.h"
#include "SSAO.h"

#include "Default.h"
#include "Texture2D.h"

void UniEngine::SSAO::Init()
{
	m_name = "SSAO";
	m_graph = BezierCubic2D();
	m_graph.m_controlPoints[1] = glm::vec2(1, 0);
	m_graph.m_controlPoints[2] = glm::vec2(0.9, 1.0);
	m_originalColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	m_originalColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	m_originalColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_originalColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_originalColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_originalColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_position = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	m_position->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	m_position->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_position->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_position->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_position->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	m_ssaoPosition = std::make_unique<GLTexture2D>(0, GL_R32F, 1, 1, false);
	m_ssaoPosition->SetData(0, GL_R32F, GL_RED, GL_FLOAT, 0);
	m_ssaoPosition->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_ssaoPosition->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_ssaoPosition->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_ssaoPosition->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	m_ssaoBlur = std::make_unique<GLTexture2D>(0, GL_R32F, 1, 1, false);
	m_ssaoBlur->SetData(0, GL_R32F, GL_RED, GL_FLOAT, 0);
	m_ssaoBlur->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_ssaoBlur->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_ssaoBlur->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_ssaoBlur->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	std::string vertShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThroughViewRay.vert"));

	std::string fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/PositionReconstruct.frag"));

	m_positionReconstructProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOGeometry.frag"));

	m_geometryProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));
	
	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BlurFilter.frag"));

	m_blurProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/SSAOCombine.frag"));

	m_combineProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);
}

void UniEngine::SSAO::ResizeResolution(int x, int y)
{
	m_originalColor->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	m_position->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	m_ssaoPosition->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
	m_ssaoBlur->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
}

void UniEngine::SSAO::Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	unsigned int enums[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	Default::GLPrograms::ScreenVAO->Bind();

	m_positionReconstructProgram->Bind();
	renderTarget.AttachTexture(m_position.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	cameraComponent->m_depthStencilBuffer->Bind(0);
	m_positionReconstructProgram->SetInt("inputTex", 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	m_geometryProgram->Bind();
	renderTarget.AttachTexture(m_originalColor.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.AttachTexture(m_ssaoPosition.get(), GL_COLOR_ATTACHMENT1);
	glDrawBuffers(2, enums);
	cameraComponent->m_colorTexture->Texture()->Bind(0);
	//_Position->Bind(1);
	cameraComponent->m_gPositionBuffer->Bind(1);
	cameraComponent->m_gNormalBuffer->Bind(2);
	m_geometryProgram->SetInt("image", 0);
	m_geometryProgram->SetInt("gPositionShadow", 1);
	m_geometryProgram->SetInt("gNormalShininess", 2);
	m_geometryProgram->SetFloat("radius", m_ssaoKernelRadius);
	m_geometryProgram->SetFloat("bias", m_ssaoKernelBias);
	m_geometryProgram->SetFloat("noiseScale", m_ssaoScale);
	m_geometryProgram->SetInt("kernelSize", m_ssaoSampleSize);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_blurProgram->Bind();
	renderTarget.AttachTexture(m_ssaoBlur.get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	m_ssaoPosition->Bind(0);
	m_blurProgram->SetInt("image", 0);
	m_blurProgram->SetFloat("sampleScale", m_blurScale);
	m_blurProgram->SetBool("horizontal", false);
	m_blurProgram->SetFloat4("bezier", m_graph.m_controlPoints[1][0], m_graph.m_controlPoints[1][1], m_graph.m_controlPoints[2][0], m_graph.m_controlPoints[2][1]);
	m_blurProgram->SetInt("diffusion", m_diffusion);
	m_blurProgram->SetFloat("intensity", m_intensity);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	renderTarget.AttachTexture(m_ssaoPosition.get(), GL_COLOR_ATTACHMENT0);
	m_ssaoBlur->Bind(0);
	m_blurProgram->SetBool("horizontal", true);
	glDrawArrays(GL_TRIANGLES, 0, 6);


	m_combineProgram->Bind();
	renderTarget.AttachTexture(cameraComponent->m_colorTexture->Texture().get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	m_originalColor->Bind(0);
	m_ssaoPosition->Bind(1);
	m_combineProgram->SetInt("originalColor", 0);
	m_combineProgram->SetInt("ao", 1);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UniEngine::SSAO::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
	if (ImGui::TreeNode("SSAO Settings")) {
		ImGui::DragFloat("Radius##SSAO", &m_ssaoKernelRadius, 0.01f, 0.1f, 5.0f);
		ImGui::DragFloat("Bias##SSAO", &m_ssaoKernelBias, 0.001f, 0.0f, 1.0f);
		ImGui::DragInt("Sample Size##SSAO", &m_ssaoSampleSize, 1, 1, 64);
		ImGui::DragFloat("Blur Scale##SSAO", &m_blurScale, 0.001f, 0.01f, 1.0f);
		ImGui::DragFloat("Intensity##SSAO", &m_intensity, 0.001f, 0.001f, 1.0f);
		ImGui::DragInt("Diffusion##SSAO", &m_diffusion, 1.0f, 1, 64);
		m_graph.Graph("Bezier##SSAO");
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Debug##SSAO"))
	{
		ImGui::Image((ImTextureID)cameraComponent->m_gPositionBuffer->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)m_position->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)m_originalColor->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)m_ssaoPosition->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)m_ssaoBlur->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::TreePop();
	}
}

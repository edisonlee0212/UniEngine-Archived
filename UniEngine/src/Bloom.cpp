#include "pch.h"
#include "Bloom.h"

#include "Default.h"
#include "Texture2D.h"
void UniEngine::Bloom::Init()
{
	m_name = "Bloom";
	m_bezierGraph = BezierCubic2D();
	m_bezierGraph.m_controlPoints[1] = glm::vec2(1, 0);
	m_bezierGraph.m_controlPoints[2] = glm::vec2(0.9, 1.0);
	m_brightColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	m_brightColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	m_brightColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_brightColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_brightColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_brightColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_result = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	m_result->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	m_result->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_result->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_result->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_result->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_flatColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	m_flatColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	m_flatColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_flatColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_flatColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_flatColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_separateProgram = std::make_unique<GLProgram>(std::make_shared<GLShader>(ShaderType::Vertex,
		std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"))),
		std::make_shared<GLShader>(ShaderType::Fragment,
			std::string("#version 460 core\n") +
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BloomSeparator.frag"))));

	m_filterProgram = std::make_unique<GLProgram>(std::make_shared<GLShader>(ShaderType::Vertex,
		std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"))),
		std::make_shared<GLShader>(ShaderType::Fragment,
			std::string("#version 460 core\n") +
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BlurFilter.frag"))));
	m_combineProgram = std::make_unique<GLProgram>(std::make_shared<GLShader>(ShaderType::Vertex,
		std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"))),
		std::make_shared<GLShader>(ShaderType::Fragment,
			std::string("#version 460 core\n") +
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BloomCombine.frag"))));

}

void UniEngine::Bloom::ResizeResolution(int x, int y)
{
	m_brightColor->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	m_result->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	m_flatColor->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
}

void UniEngine::Bloom::Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	unsigned int enums[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	Default::GLPrograms::ScreenVAO->Bind();

	m_separateProgram->Bind();

	renderTarget.AttachTexture(m_flatColor.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.AttachTexture(m_brightColor.get(), GL_COLOR_ATTACHMENT1);
	renderTarget.Bind();
	glDrawBuffers(2, enums);
	cameraComponent->m_colorTexture->m_texture->Bind(0);
	m_separateProgram->SetInt("image", 0);
	m_separateProgram->SetFloat("threshold", m_threshold);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_filterProgram->Bind();
	renderTarget.AttachTexture(m_result.get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	m_brightColor->Bind(0);
	m_filterProgram->SetInt("image", 0);
	m_filterProgram->SetBool("horizontal", false);
	m_filterProgram->SetFloat("sampleScale", 1.0f);
	m_filterProgram->SetFloat4("bezier", m_bezierGraph.m_controlPoints[1][0], m_bezierGraph.m_controlPoints[1][1], m_bezierGraph.m_controlPoints[2][0], m_bezierGraph.m_controlPoints[2][1]);
	m_filterProgram->SetInt("diffusion", m_diffusion);
	m_filterProgram->SetFloat("clamp", m_clamp);
	m_filterProgram->SetFloat("intensity", m_intensity);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	renderTarget.AttachTexture(m_brightColor.get(), GL_COLOR_ATTACHMENT0);
	m_result->Bind(0);
	m_filterProgram->SetBool("horizontal", true);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_combineProgram->Bind();
	renderTarget.AttachTexture(cameraComponent->m_colorTexture->Texture().get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	m_flatColor->Bind(0);
	m_brightColor->Bind(1);
	m_combineProgram->SetInt("flatColor", 0);
	m_combineProgram->SetInt("brightColor", 1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void UniEngine::Bloom::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
	if (ImGui::TreeNode("Bloom Settings")) {
		ImGui::DragFloat("Intensity##Bloom", &m_intensity, 0.001f, 0.001f, 1.0f);
		ImGui::DragInt("Diffusion##Bloom", &m_diffusion, 1.0f, 1, 64);
		ImGui::DragFloat("Threshold##Bloom", &m_threshold, 0.01f, 0.0f, 5.0f);
		ImGui::DragFloat("Clamp##Bloom", &m_clamp, 0.01f, 0.0f, 5.0f);
		m_bezierGraph.Graph("Bezier##Bloom");
		if (ImGui::TreeNode("Debug##Bloom"))
		{
			ImGui::Image((ImTextureID)m_flatColor->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Image((ImTextureID)m_result->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Image((ImTextureID)m_brightColor->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::TreePop();
	}

}

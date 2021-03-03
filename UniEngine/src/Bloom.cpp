#include "pch.h"
#include "Bloom.h"

#include "Default.h"
#include "Texture2D.h"
void UniEngine::Bloom::Init()
{
	_Name = "Bloom";
	BezierGraph = BezierCubic2D();
	BezierGraph.ControlPoints[1] = glm::vec2(1, 0);
	BezierGraph.ControlPoints[2] = glm::vec2(0.9, 1.0);
	_BrightColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	_BrightColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_BrightColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_BrightColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_BrightColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_BrightColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	_Result = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	_Result->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_Result->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_Result->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_Result->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_Result->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	_FlatColor = std::make_unique<GLTexture2D>(0, GL_RGB32F, 1, 1, false);
	_FlatColor->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_FlatColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_FlatColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_FlatColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_FlatColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	_SeparateProgram = std::make_unique<GLProgram>(std::make_shared<GLShader>(ShaderType::Vertex,
		std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"))),
		std::make_shared<GLShader>(ShaderType::Fragment,
			std::string("#version 460 core\n") +
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BloomSeparator.frag"))));

	_FilterProgram = std::make_unique<GLProgram>(std::make_shared<GLShader>(ShaderType::Vertex,
		std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"))),
		std::make_shared<GLShader>(ShaderType::Fragment,
			std::string("#version 460 core\n") +
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BlurFilter.frag"))));
	_CombineProgram = std::make_unique<GLProgram>(std::make_shared<GLShader>(ShaderType::Vertex,
		std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"))),
		std::make_shared<GLShader>(ShaderType::Fragment,
			std::string("#version 460 core\n") +
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BloomCombine.frag"))));

}

void UniEngine::Bloom::ResizeResolution(int x, int y)
{
	_BrightColor->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	_Result->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	_FlatColor->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
}

void UniEngine::Bloom::Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	unsigned int enums[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	Default::GLPrograms::ScreenVAO->Bind();

	_SeparateProgram->Bind();

	renderTarget.AttachTexture(_FlatColor.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.AttachTexture(_BrightColor.get(), GL_COLOR_ATTACHMENT1);
	renderTarget.Bind();
	glDrawBuffers(2, enums);
	cameraComponent->m_colorTexture->_Texture->Bind(0);
	_SeparateProgram->SetInt("image", 0);
	_SeparateProgram->SetFloat("threshold", Threshold);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	_FilterProgram->Bind();
	renderTarget.AttachTexture(_Result.get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_BrightColor->Bind(0);
	_FilterProgram->SetInt("image", 0);
	_FilterProgram->SetBool("horizontal", false);
	_FilterProgram->SetFloat("sampleScale", 1.0f);
	_FilterProgram->SetFloat4("bezier", BezierGraph.ControlPoints[1][0], BezierGraph.ControlPoints[1][1], BezierGraph.ControlPoints[2][0], BezierGraph.ControlPoints[2][1]);
	_FilterProgram->SetInt("diffusion", Diffusion);
	_FilterProgram->SetFloat("clamp", Clamp);
	_FilterProgram->SetFloat("intensity", Intensity);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	renderTarget.AttachTexture(_BrightColor.get(), GL_COLOR_ATTACHMENT0);
	_Result->Bind(0);
	_FilterProgram->SetBool("horizontal", true);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	_CombineProgram->Bind();
	renderTarget.AttachTexture(cameraComponent->m_colorTexture->Texture().get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_FlatColor->Bind(0);
	_BrightColor->Bind(1);
	_CombineProgram->SetInt("flatColor", 0);
	_CombineProgram->SetInt("brightColor", 1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void UniEngine::Bloom::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
	if (ImGui::TreeNode("Bloom Settings")) {
		ImGui::DragFloat("Intensity##Bloom", &Intensity, 0.001f, 0.001f, 1.0f);
		ImGui::DragInt("Diffusion##Bloom", &Diffusion, 1.0f, 1, 64);
		ImGui::DragFloat("Threshold##Bloom", &Threshold, 0.01f, 0.0f, 5.0f);
		ImGui::DragFloat("Clamp##Bloom", &Clamp, 0.01f, 0.0f, 5.0f);
		BezierGraph.Graph("Bezier##Bloom");
		if (ImGui::TreeNode("Debug##Bloom"))
		{
			ImGui::Image((ImTextureID)_FlatColor->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Image((ImTextureID)_Result->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Image((ImTextureID)_BrightColor->Id(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::TreePop();
	}

}

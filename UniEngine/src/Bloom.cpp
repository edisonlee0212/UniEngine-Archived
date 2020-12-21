#include "pch.h"
#include "Bloom.h"

#include "Default.h"
#include "Texture2D.h"
UniEngine::Bloom::Bloom()
{
	_Bezier2D = { 1.0f, 0.0f, 0.9f, 1.0f };
	_Type = PostProcessingLayerType::Bloom;
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
			FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BlurFilter.frag"))) );
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
	cameraComponent->_ColorTexture->_Texture->Bind(0);
	_SeparateProgram->SetInt("image", 0);
	_SeparateProgram->SetFloat("threshold", _Threshold);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	_FilterProgram->Bind();
	renderTarget.AttachTexture(_Result.get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_BrightColor->Bind(0);
	_FilterProgram->SetInt("image", 0);
	_FilterProgram->SetBool("horizontal", false);
	_FilterProgram->SetFloat("sampleScale", 1.0f);
	_FilterProgram->SetFloat4("bezier", _Bezier2D.ControlPoints[0], _Bezier2D.ControlPoints[1], _Bezier2D.ControlPoints[2], _Bezier2D.ControlPoints[3]);
	_FilterProgram->SetInt("diffusion", _Diffusion);
	_FilterProgram->SetFloat("clamp", _Clamp);
	_FilterProgram->SetFloat("intensity", _Intensity);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	renderTarget.AttachTexture(_BrightColor.get(), GL_COLOR_ATTACHMENT0);
	_Result->Bind(0);
	_FilterProgram->SetBool("horizontal", true);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	_CombineProgram->Bind();
	renderTarget.AttachTexture(cameraComponent->_ColorTexture->Texture().get(), GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_FlatColor->Bind(0);
	_BrightColor->Bind(1);
	_CombineProgram->SetInt("flatColor", 0);
	_CombineProgram->SetInt("brightColor", 1);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}

void UniEngine::Bloom::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
	ImGui::Checkbox("Enabled", &_Enabled);
	if (_Enabled) {
		if (ImGui::TreeNode("Bloom")) {
			ImGui::DragFloat("Intensity##Bloom", &_Intensity, 0.001f, 0.001f, 1.0f);
			ImGui::DragInt("Diffusion##Bloom", &_Diffusion, 1.0f, 1, 64);
			ImGui::Separator();
			ImGui::DragFloat("Threshold##Bloom", &_Threshold, 0.01f, 0.0f, 5.0f);
			ImGui::DragFloat("Clamp##Bloom", &_Clamp, 0.01f, 0.0f, 5.0f);
			_Bezier2D.Graph("Bezier##Bloom");
			ImGui::TreePop();
		}
	}
}

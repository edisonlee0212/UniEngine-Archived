#include "pch.h"
#include "GreyScale.h"

#include "Default.h"

void UniEngine::GreyScale::Init()
{
	_Name = "GreyScale";
	_GreyColor = std::make_unique<GLTexture2D>(0, GL_R32F, 1, 1, false);
	_GreyColor->SetData(0, GL_R32F, GL_RED, GL_FLOAT, 0);
	_GreyColor->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GreyColor->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GreyColor->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_GreyColor->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	std::string vertShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));

	std::string fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/GreyScale.frag"));

	_TransferProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/TexturePassThrough.vert"));

	fragShaderCode = std::string("#version 460 core\n") +
		*Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/GreyScaleCopy.frag"));

	_CopyProgram = std::make_unique<GLProgram>(
		std::make_shared<GLShader>(ShaderType::Vertex, vertShaderCode),
		std::make_shared<GLShader>(ShaderType::Fragment, fragShaderCode)
		);
}

void UniEngine::GreyScale::ResizeResolution(int x, int y)
{
	_GreyColor->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, x, y);
}

void UniEngine::GreyScale::Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	
	Default::GLPrograms::ScreenVAO->Bind();

	_TransferProgram->Bind();
	renderTarget.AttachTexture(_GreyColor.get(), GL_COLOR_ATTACHMENT0);
	renderTarget.Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	cameraComponent->_ColorTexture->Texture()->Bind(0);
	_TransferProgram->SetInt("inputTex", 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	_CopyProgram->Bind();
	renderTarget.AttachTexture(cameraComponent->_ColorTexture->Texture().get(), GL_COLOR_ATTACHMENT0);
	renderTarget.Bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	_GreyColor->Bind(0);
	_CopyProgram->SetInt("inputTex", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);	
}

void UniEngine::GreyScale::OnGui(std::unique_ptr<CameraComponent>& cameraComponent)
{
}

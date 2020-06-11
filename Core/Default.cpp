#include "pch.h"
#include "Default.h"
#include "World.h"
#include "MeshMaterialComponent.h"

using namespace UniEngine;

GLProgram* Default::GLPrograms::ScreenProgram;
GLProgram* Default::GLPrograms::StandardProgram;
GLProgram* Default::GLPrograms::StandardInstancedProgram;
GLVAO* Default::GLPrograms::ScreenVAO;
std::string* Default::ShaderIncludes::Uniform;
std::string* Default::ShaderIncludes::Lights;
std::string* Default::ShaderIncludes::Shadow;


void UniEngine::Default::Load(World* world)
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	GLPrograms::ScreenVAO = new GLVAO();
	auto quadVBO = GLPrograms::ScreenVAO->VBO()->ID();
	GLPrograms::ScreenVAO->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	GLShader* screenvert = new GLShader(ShaderType::Vertex);
	std::string vertShaderCode = std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Vertex/screen.vert")));
	screenvert->SetCode(&vertShaderCode);
	GLShader* screenfrag = new GLShader(ShaderType::Fragment);
	std::string fragShaderCode = std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Fragment/screen.frag")));
	screenfrag->SetCode(&fragShaderCode);
	GLPrograms::ScreenProgram = new GLProgram();
	GLPrograms::ScreenProgram->Attach(ShaderType::Vertex, screenvert);
	GLPrograms::ScreenProgram->Attach(ShaderType::Fragment, screenfrag);
	GLPrograms::ScreenProgram->Link();
	GLPrograms::ScreenProgram->SetInt("screenTexture", 0);
	delete screenvert;
	delete screenfrag;

	std::string add = 
		"#define MAX_TEXTURES_AMOUNT " + std::to_string(ShaderIncludes::MaxMaterialsAmount) +
		"\n#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxDirectionalLightAmount) +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxPointLightAmount) +
		"\n#define SPOT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxSpotLightAmount) + "\n";

	ShaderIncludes::Uniform = new std::string(add + FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Include/Uniform.inc")));
	ShaderIncludes::Shadow = new std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Include/Shadow.frag")));
	ShaderIncludes::Lights = new std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Include/Lights.frag")));

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString("Resources/Shaders/Vertex/Standard.vert");


	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform
		+ "\n"
		+ *Default::ShaderIncludes::Shadow
		+ "\n"
		+ *Default::ShaderIncludes::Lights
		+ "\n"
		+ FileIO::LoadFileAsString("Resources/Shaders/Fragment/Standard.frag");

	GLShader* standardvert = new GLShader(ShaderType::Vertex);
	standardvert->SetCode(&vertShaderCode);
	GLShader* standardfrag = new GLShader(ShaderType::Fragment);
	standardfrag->SetCode(&fragShaderCode);
	GLPrograms::StandardProgram = new GLProgram();
	GLPrograms::StandardProgram->Attach(ShaderType::Vertex, standardvert);
	GLPrograms::StandardProgram->Attach(ShaderType::Fragment, standardfrag);
	GLPrograms::StandardProgram->Link();
	delete standardvert;
	delete standardfrag;

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString("Resources/Shaders/Vertex/StandardInstanced.vert");

	standardvert = new GLShader(ShaderType::Vertex);
	standardvert->SetCode(&vertShaderCode);
	standardfrag = new GLShader(ShaderType::Fragment);
	standardfrag->SetCode(&fragShaderCode);
	GLPrograms::StandardInstancedProgram = new GLProgram();
	GLPrograms::StandardInstancedProgram->Attach(ShaderType::Vertex, standardvert);
	GLPrograms::StandardInstancedProgram->Attach(ShaderType::Fragment, standardfrag);
	GLPrograms::StandardInstancedProgram->Link();
	delete standardvert;
	delete standardfrag;
}

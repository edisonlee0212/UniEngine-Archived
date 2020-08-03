#include "pch.h"
#include "Default.h"
#include "World.h"
#include "MeshMaterialComponent.h"
#include "ModelManager.h"
using namespace UniEngine;

GLProgram* Default::GLPrograms::ScreenProgram;
GLProgram* Default::GLPrograms::StandardProgram;
GLProgram* Default::GLPrograms::StandardInstancedProgram;
GLProgram* Default::GLPrograms::GizmoProgram;
GLProgram* Default::GLPrograms::GizmoInstancedProgram;

GLVAO* Default::GLPrograms::ScreenVAO;
std::string* Default::ShaderIncludes::Uniform;
std::string* Default::ShaderIncludes::Lights;
std::string* Default::ShaderIncludes::Shadow;

Texture2D* Default::Textures::MissingTexture;
Texture2D* Default::Textures::UV;
Texture2D* Default::Textures::StandardTexture;

Mesh* Default::Primitives::Sphere;
Mesh* Default::Primitives::Cube;
Mesh* Default::Primitives::Quad;
Mesh* Default::Primitives::Cone;
Mesh* Default::Primitives::Ring;
Mesh* Default::Primitives::Cylinder;
Mesh* Default::Primitives::Monkey;

Material* Default::Materials::StandardMaterial;
Material* Default::Materials::StandardInstancedMaterial;


void UniEngine::Default::Load(World* world)
{
#pragma region Screen Shader
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
	auto quadVBO = GLPrograms::ScreenVAO->VBO();
	GLPrograms::ScreenVAO->SetData(sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	GLPrograms::ScreenVAO->EnableAttributeArray(0);
	GLPrograms::ScreenVAO->SetAttributePointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	GLPrograms::ScreenVAO->EnableAttributeArray(1);
	GLPrograms::ScreenVAO->SetAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	GLShader* screenvert = new GLShader(ShaderType::Vertex);
	std::string vertShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString("Shaders/Vertex/Screen.vert"));
	screenvert->SetCode(&vertShaderCode);
	GLShader* screenfrag = new GLShader(ShaderType::Fragment);
	std::string fragShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString("Shaders/Fragment/Screen.frag"));
	screenfrag->SetCode(&fragShaderCode);
	GLPrograms::ScreenProgram = new GLProgram();
	GLPrograms::ScreenProgram->Attach(ShaderType::Vertex, screenvert);
	GLPrograms::ScreenProgram->Attach(ShaderType::Fragment, screenfrag);
	GLPrograms::ScreenProgram->Link();
	delete screenvert;
	delete screenfrag;
#pragma endregion
#pragma region Shader Includes
	std::string add =
		"#define MAX_TEXTURES_AMOUNT " + std::to_string(ShaderIncludes::MaxMaterialsAmount) +
		"\n#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxDirectionalLightAmount) +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxPointLightAmount) +
		"\n#define SHADOW_CASCADE_AMOUNT " + std::to_string(ShaderIncludes::ShadowCascadeAmount) +
		"\n#define SPOT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxSpotLightAmount) + "\n";

	ShaderIncludes::Uniform = new std::string(add + FileIO::LoadFileAsString("Shaders/Include/Uniform.inc"));
	ShaderIncludes::Shadow = new std::string(FileIO::LoadFileAsString("Shaders/Include/Shadow.frag"));
	ShaderIncludes::Lights = new std::string(FileIO::LoadFileAsString("Shaders/Include/Lights.frag"));
#pragma endregion
#pragma region Textures
	Textures::MissingTexture = new Texture2D(TextureType::DIFFUSE);
	Textures::MissingTexture->LoadTexture(FileIO::GetPath("Textures/texture-missing.png"), "");
	Textures::UV = new Texture2D(TextureType::DIFFUSE);
	Textures::UV->LoadTexture(FileIO::GetPath("Textures/uv-test.png"), "");
	Textures::StandardTexture = new Texture2D(TextureType::DIFFUSE);
	Textures::StandardTexture->LoadTexture(FileIO::GetPath("Textures/white.png"), "");
#pragma endregion
#pragma region Standard Shader
	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString("Shaders/Vertex/Standard.vert");


	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform
		+ "\n"
		+ *Default::ShaderIncludes::Shadow
		+ "\n"
		+ *Default::ShaderIncludes::Lights
		+ "\n"
		+ FileIO::LoadFileAsString("Shaders/Fragment/Standard.frag");

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
		+ FileIO::LoadFileAsString("Shaders/Vertex/StandardInstanced.vert");

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

#pragma endregion
#pragma region Gizmo Shader
	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform
		+ "\n"
		+ FileIO::LoadFileAsString("Shaders/Fragment/Gizmo.frag");

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString("Shaders/Vertex/Gizmo.vert");

	standardvert = new GLShader(ShaderType::Vertex);
	standardvert->SetCode(&vertShaderCode);
	standardfrag = new GLShader(ShaderType::Fragment);
	standardfrag->SetCode(&fragShaderCode);
	GLPrograms::GizmoProgram = new GLProgram();
	GLPrograms::GizmoProgram->Attach(ShaderType::Vertex, standardvert);
	GLPrograms::GizmoProgram->Attach(ShaderType::Fragment, standardfrag);
	GLPrograms::GizmoProgram->Link();
	delete standardvert;
	delete standardfrag;


	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString("Shaders/Vertex/GizmoInstanced.vert");

	standardvert = new GLShader(ShaderType::Vertex);
	standardvert->SetCode(&vertShaderCode);
	standardfrag = new GLShader(ShaderType::Fragment);
	standardfrag->SetCode(&fragShaderCode);
	GLPrograms::GizmoInstancedProgram = new GLProgram();
	GLPrograms::GizmoInstancedProgram->Attach(ShaderType::Vertex, standardvert);
	GLPrograms::GizmoInstancedProgram->Attach(ShaderType::Fragment, standardfrag);
	GLPrograms::GizmoInstancedProgram->Link();
	delete standardvert;
	delete standardfrag;
#pragma endregion
#pragma region Standard Material
	Materials::StandardMaterial = new Material();
	Materials::StandardMaterial->Programs()->push_back(Default::GLPrograms::StandardProgram);
	Materials::StandardMaterial->Textures2Ds()->push_back(Textures::StandardTexture);
	Materials::StandardMaterial->SetMaterialProperty("material.shininess", 32.0f);

	Materials::StandardInstancedMaterial = new Material();
	Materials::StandardInstancedMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	Materials::StandardInstancedMaterial->Textures2Ds()->push_back(Textures::StandardTexture);
	Materials::StandardInstancedMaterial->SetMaterialProperty("material.shininess", 32.0f);
#pragma endregion
#pragma region Models & Primitives
	Model* model = ModelManager::LoadModel(FileIO::GetPath("Primitives/quad.obj"));
	Primitives::Quad = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetPath("Primitives/sphere.obj"));
	Primitives::Sphere = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetPath("Primitives/cube.obj"));
	Primitives::Cube = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetPath("Primitives/cone.obj"));
	Primitives::Cone = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetPath("Primitives/cylinder.obj"));
	Primitives::Cylinder = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetPath("Primitives/ring.obj"));
	Primitives::Ring = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetPath("Primitives/monkey.obj"));
	Primitives::Monkey = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->_Mesh;
	//delete model;
#pragma endregion
}

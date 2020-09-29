#include "pch.h"
#include "Default.h"
#include "World.h"
#include "MeshMaterialComponent.h"
#include "ModelManager.h"
using namespace UniEngine;

std::shared_ptr<GLProgram> Default::GLPrograms::SkyboxProgram;

GLProgram* Default::GLPrograms::ScreenProgram;
GLProgram* Default::GLPrograms::StandardProgram;
GLProgram* Default::GLPrograms::StandardInstancedProgram;
GLProgram* Default::GLPrograms::GizmoProgram;
GLProgram* Default::GLPrograms::GizmoInstancedProgram;

GLVAO* Default::GLPrograms::ScreenVAO;
std::shared_ptr<GLVAO> Default::GLPrograms::SkyboxVAO;
std::string* Default::ShaderIncludes::Uniform;
std::string* Default::ShaderIncludes::Lights;
std::string* Default::ShaderIncludes::Shadow;

Texture2D* Default::Textures::MissingTexture;
Texture2D* Default::Textures::UV;
Texture2D* Default::Textures::StandardTexture;
std::shared_ptr<Cubemap> Default::Textures::DefaultSkybox;

std::shared_ptr<Mesh> Default::Primitives::Sphere;
std::shared_ptr<Mesh> Default::Primitives::Cube;
std::shared_ptr<Mesh> Default::Primitives::Quad;
std::shared_ptr<Mesh> Default::Primitives::FrontBackQuad;
std::shared_ptr<Mesh> Default::Primitives::Cone;
std::shared_ptr<Mesh> Default::Primitives::Ring;
std::shared_ptr<Mesh> Default::Primitives::Cylinder;
std::shared_ptr<Mesh> Default::Primitives::Monkey;

std::shared_ptr<Material> Default::Materials::StandardMaterial;
std::shared_ptr<Material> Default::Materials::StandardInstancedMaterial;


void UniEngine::Default::Load(World* world)
{
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
#pragma region Skybox
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	GLPrograms::SkyboxVAO = std::make_shared<GLVAO>();
	GLPrograms::SkyboxVAO->SetData(sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	GLPrograms::SkyboxVAO->EnableAttributeArray(0);
	GLPrograms::SkyboxVAO->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	Textures::DefaultSkybox = std::make_shared<Cubemap>();
	const std::vector<std::string> facesPath
	{
		FileIO::GetResourcePath("Textures/Skyboxes/Default/right.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/left.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/top.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/bottom.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/front.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/back.jpg"),
	};
	Textures::DefaultSkybox->LoadCubeMap(facesPath);
	
	GLShader* skyboxvert = new GLShader(ShaderType::Vertex);
	std::string vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString("Shaders/Vertex/Skybox.vert"));
	skyboxvert->SetCode(&vertShaderCode);
	GLShader* skyboxfrag = new GLShader(ShaderType::Fragment);
	std::string fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString("Shaders/Fragment/Skybox.frag"));
	skyboxfrag->SetCode(&fragShaderCode);
	GLPrograms::SkyboxProgram = std::make_shared<GLProgram>();
	GLPrograms::SkyboxProgram->Attach(ShaderType::Vertex, skyboxvert);
	GLPrograms::SkyboxProgram->Attach(ShaderType::Fragment, skyboxfrag);
	GLPrograms::SkyboxProgram->Link();
	GLPrograms::SkyboxProgram->SetInt("skybox", 0);
	delete skyboxvert;
	delete skyboxfrag;
#pragma endregion

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
	GLPrograms::ScreenVAO->SetData(sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	GLPrograms::ScreenVAO->EnableAttributeArray(0);
	GLPrograms::ScreenVAO->SetAttributePointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	GLPrograms::ScreenVAO->EnableAttributeArray(1);
	GLPrograms::ScreenVAO->SetAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	GLShader* screenvert = new GLShader(ShaderType::Vertex);
	vertShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString("Shaders/Vertex/Screen.vert"));
	screenvert->SetCode(&vertShaderCode);
	GLShader* screenfrag = new GLShader(ShaderType::Fragment);
	fragShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString("Shaders/Fragment/Screen.frag"));
	screenfrag->SetCode(&fragShaderCode);
	GLPrograms::ScreenProgram = new GLProgram();
	GLPrograms::ScreenProgram->Attach(ShaderType::Vertex, screenvert);
	GLPrograms::ScreenProgram->Attach(ShaderType::Fragment, screenfrag);
	GLPrograms::ScreenProgram->Link();
	delete screenvert;
	delete screenfrag;
#pragma endregion

#pragma region Textures
	Textures::MissingTexture = new Texture2D(TextureType::DIFFUSE);
	Textures::MissingTexture->LoadTexture(FileIO::GetResourcePath("Textures/texture-missing.png"), "");
	Textures::UV = new Texture2D(TextureType::DIFFUSE);
	Textures::UV->LoadTexture(FileIO::GetResourcePath("Textures/uv-test.png"), "");
	Textures::StandardTexture = new Texture2D(TextureType::DIFFUSE);
	Textures::StandardTexture->LoadTexture(FileIO::GetResourcePath("Textures/white.png"), "");
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
	Materials::StandardMaterial = std::make_shared<Material>();
	Materials::StandardMaterial->Programs()->push_back(Default::GLPrograms::StandardProgram);
	Materials::StandardMaterial->Textures2Ds()->push_back(Textures::StandardTexture);
	Materials::StandardMaterial->SetMaterialProperty("material.shininess", 32.0f);

	Materials::StandardInstancedMaterial = std::make_shared<Material>();
	Materials::StandardInstancedMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	Materials::StandardInstancedMaterial->Textures2Ds()->push_back(Textures::StandardTexture);
	Materials::StandardInstancedMaterial->SetMaterialProperty("material.shininess", 32.0f);
#pragma endregion
#pragma region Models & Primitives
	Model* model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/quad.obj"));
	Primitives::Quad = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/frontbackquad.obj"));
	Primitives::FrontBackQuad = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;
	
	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/sphere.obj"));
	Primitives::Sphere = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/cube.obj"));
	Primitives::Cube = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/cone.obj"));
	Primitives::Cone = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/cylinder.obj"));
	Primitives::Cylinder = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/ring.obj"));
	Primitives::Ring = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;

	model = ModelManager::LoadModel(FileIO::GetResourcePath("Primitives/monkey.obj"));
	Primitives::Monkey = model->RootNode()->Children[0]->_MeshMaterialComponents[0]->Mesh;
	//delete model;
#pragma endregion
}

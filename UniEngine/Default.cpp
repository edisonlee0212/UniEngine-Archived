#include "pch.h"
#include "Default.h"
#include "World.h"
#include "MeshRenderer.h"
#include "AssetManager.h"
#include "RenderManager.h"
using namespace UniEngine;

std::shared_ptr<GLProgram> Default::GLPrograms::SkyboxProgram;
std::shared_ptr<GLProgram> Default::GLPrograms::BackGroundProgram;
std::shared_ptr<GLProgram> Default::GLPrograms::ScreenProgram;
std::shared_ptr<GLProgram> Default::GLPrograms::StandardProgram;
std::shared_ptr<GLProgram> Default::GLPrograms::StandardInstancedProgram;
std::shared_ptr<GLProgram> Default::GLPrograms::GizmoProgram;
std::shared_ptr<GLProgram> Default::GLPrograms::GizmoInstancedProgram;

GLVAO* Default::GLPrograms::ScreenVAO;
std::shared_ptr<GLVAO> Default::GLPrograms::SkyboxVAO;
std::string* Default::ShaderIncludes::Uniform;


std::shared_ptr<Texture2D> Default::Textures::MissingTexture;
std::shared_ptr<Texture2D> Default::Textures::UV;
std::shared_ptr<Texture2D> Default::Textures::ObjectIcon;
std::shared_ptr<Texture2D> Default::Textures::StandardTexture;
std::shared_ptr<Cubemap> Default::Textures::DefaultSkybox;

std::shared_ptr<Mesh> Default::Primitives::Sphere;
std::shared_ptr<Mesh> Default::Primitives::Cube;
std::shared_ptr<Mesh> Default::Primitives::Quad;
std::shared_ptr<Mesh> Default::Primitives::Cone;
std::shared_ptr<Mesh> Default::Primitives::Ring;
std::shared_ptr<Mesh> Default::Primitives::Cylinder;
std::shared_ptr<Mesh> Default::Primitives::Monkey;

void UniEngine::Default::Load(World* world)
{
#pragma region Shader Includes
	std::string add =
		"#define MAX_TEXTURES_AMOUNT " + std::to_string(ShaderIncludes::MaxMaterialsAmount) +
		"\n#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxDirectionalLightAmount) +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxPointLightAmount) +
		"\n#define SHADOW_CASCADE_AMOUNT " + std::to_string(ShaderIncludes::ShadowCascadeAmount) +
		"\n#define MAX_KERNEL_AMOUNT " + std::to_string(ShaderIncludes::MaxKernelAmount) +
		"\n#define SPOT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxSpotLightAmount) + "\n";

	ShaderIncludes::Uniform = new std::string(add + FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Include/Uniform.inc")));

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
		FileIO::GetResourcePath("Textures/Skyboxes/Default/posx.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/negx.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/posy.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/negy.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/posz.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/negz.jpg"),
	};
	Textures::DefaultSkybox->LoadCubeMap(facesPath);
	
	GLShader* skyboxvert = new GLShader(ShaderType::Vertex);
	std::string vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Skybox.vert")));
	skyboxvert->SetCode(&vertShaderCode);
	GLShader* skyboxfrag = new GLShader(ShaderType::Fragment);
	std::string fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Skybox.frag")));
	skyboxfrag->SetCode(&fragShaderCode);
	GLPrograms::SkyboxProgram = std::make_shared<GLProgram>();
	GLPrograms::SkyboxProgram->Attach(ShaderType::Vertex, skyboxvert);
	GLPrograms::SkyboxProgram->Attach(ShaderType::Fragment, skyboxfrag);
	GLPrograms::SkyboxProgram->Link();
	GLPrograms::SkyboxProgram->SetInt("skybox", 0);
	delete skyboxfrag;
	
	skyboxfrag = new GLShader(ShaderType::Fragment);
	fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BackGround.frag")));
	skyboxfrag->SetCode(&fragShaderCode);
	GLPrograms::BackGroundProgram = std::make_shared<GLProgram>();
	GLPrograms::BackGroundProgram->Attach(ShaderType::Vertex, skyboxvert);
	GLPrograms::BackGroundProgram->Attach(ShaderType::Fragment, skyboxfrag);
	GLPrograms::BackGroundProgram->Link();
	
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
	vertShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Screen.vert")));
	screenvert->SetCode(&vertShaderCode);
	GLShader* screenfrag = new GLShader(ShaderType::Fragment);
	fragShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Screen.frag")));
	screenfrag->SetCode(&fragShaderCode);
	GLPrograms::ScreenProgram = std::make_shared<GLProgram>();
	GLPrograms::ScreenProgram->Attach(ShaderType::Vertex, screenvert);
	GLPrograms::ScreenProgram->Attach(ShaderType::Fragment, screenfrag);
	GLPrograms::ScreenProgram->Link();
	delete screenvert;
	delete screenfrag;
#pragma endregion

#pragma region Textures
	Textures::MissingTexture = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/texture-missing.png"));
	Textures::MissingTexture->Name = "Missing";
	Textures::UV = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/uv-test.png"));
	Textures::UV->Name = "UV";
	Textures::StandardTexture = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/white.png"));
	Textures::StandardTexture->Name = "Default";
	Textures::ObjectIcon = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/object.png"));
	Textures::ObjectIcon->Name = "Icon";
#pragma endregion
#pragma region Standard Shader
	
	vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Standard.vert"));
	fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform
		+ "\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/StandardForward.frag"));

	GLShader* standardVert = new GLShader(ShaderType::Vertex);
	standardVert->SetCode(&vertShaderCode);
	GLShader* standardFrag = new GLShader(ShaderType::Fragment);
	standardFrag->SetCode(&fragShaderCode);
	GLPrograms::StandardProgram = std::make_shared<GLProgram>();
	GLPrograms::StandardProgram->Attach(ShaderType::Vertex, standardVert);
	GLPrograms::StandardProgram->Attach(ShaderType::Fragment, standardFrag);
	GLPrograms::StandardProgram->Link();
	delete standardVert;
	delete standardFrag;

	vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/StandardInstanced.vert"));

	standardVert = new GLShader(ShaderType::Vertex);
	standardVert->SetCode(&vertShaderCode);
	standardFrag = new GLShader(ShaderType::Fragment);
	standardFrag->SetCode(&fragShaderCode);
	GLPrograms::StandardInstancedProgram = std::make_shared<GLProgram>();
	GLPrograms::StandardInstancedProgram->Attach(ShaderType::Vertex, standardVert);
	GLPrograms::StandardInstancedProgram->Attach(ShaderType::Fragment, standardFrag);
	GLPrograms::StandardInstancedProgram->Link();
	delete standardVert;
	delete standardFrag;

#pragma endregion
#pragma region Gizmo Shader
	fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform
		+ "\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Gizmo.frag"));

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Gizmo.vert"));

	standardVert = new GLShader(ShaderType::Vertex);
	standardVert->SetCode(&vertShaderCode);
	standardFrag = new GLShader(ShaderType::Fragment);
	standardFrag->SetCode(&fragShaderCode);
	GLPrograms::GizmoProgram = std::make_shared<GLProgram>();
	GLPrograms::GizmoProgram->Attach(ShaderType::Vertex, standardVert);
	GLPrograms::GizmoProgram->Attach(ShaderType::Fragment, standardFrag);
	GLPrograms::GizmoProgram->Link();
	delete standardVert;
	delete standardFrag;


	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/GizmoInstanced.vert"));

	standardVert = new GLShader(ShaderType::Vertex);
	standardVert->SetCode(&vertShaderCode);
	standardFrag = new GLShader(ShaderType::Fragment);
	standardFrag->SetCode(&fragShaderCode);
	GLPrograms::GizmoInstancedProgram = std::make_shared<GLProgram>();
	GLPrograms::GizmoInstancedProgram->Attach(ShaderType::Vertex, standardVert);
	GLPrograms::GizmoInstancedProgram->Attach(ShaderType::Fragment, standardFrag);
	GLPrograms::GizmoInstancedProgram->Link();
	delete standardVert;
	delete standardFrag;
#pragma endregion

#pragma region Models & Primitives
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/quad.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Quad = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Quad";
	}
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/sphere.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Sphere = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Sphere";
	}
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/cube.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Cube = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Cube";
	}
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/cone.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Cone = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Cone";
	}
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/cylinder.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Cylinder = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Cylinder";
	}
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/ring.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Ring = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Ring";
	}	
	{
		auto model = AssetManager::LoadModel(FileIO::GetResourcePath("Primitives/monkey.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Monkey = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		model->Name = "Monkey";
	}
#pragma endregion
}

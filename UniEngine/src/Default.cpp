#include "pch.h"
#include "Default.h"
#include "World.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
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
std::shared_ptr<Texture2D> Default::Textures::Border;
std::shared_ptr<Texture2D> Default::Textures::StandardTexture;
std::shared_ptr<Cubemap> Default::Textures::DefaultSkybox;

std::shared_ptr<Mesh> Default::Primitives::Sphere;
std::shared_ptr<Mesh> Default::Primitives::Cube;
std::shared_ptr<Mesh> Default::Primitives::Quad;
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

	const std::vector<std::string> facesPath
	{
		FileIO::GetResourcePath("Textures/Skyboxes/Default/posx.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/negx.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/posy.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/negy.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/posz.jpg"),
		FileIO::GetResourcePath("Textures/Skyboxes/Default/negz.jpg"),
	};

	Textures::DefaultSkybox = ResourceManager::LoadCubemap(facesPath);
	
	auto skyboxvert = std::make_shared<GLShader>(ShaderType::Vertex);
	std::string vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Skybox.vert")));
	skyboxvert->Compile(vertShaderCode);
	auto skyboxfrag = std::make_shared<GLShader>(ShaderType::Fragment);
	std::string fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Skybox.frag")));
	skyboxfrag->Compile(fragShaderCode);
	GLPrograms::SkyboxProgram = ResourceManager::LoadProgram(skyboxvert, skyboxfrag);
	GLPrograms::SkyboxProgram->SetInt("skybox", 0);
	GLPrograms::SkyboxProgram->Name = "Skybox";
	skyboxfrag = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n" + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/BackGround.frag")));
	skyboxfrag->Compile(fragShaderCode);
	GLPrograms::BackGroundProgram = ResourceManager::LoadProgram(skyboxvert, skyboxfrag);
	GLPrograms::BackGroundProgram->Name = "Background";
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

	auto screenvert = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Screen.vert")));
	screenvert->Compile(vertShaderCode);
	auto screenfrag = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShaderCode = std::string("#version 460 core\n") + std::string(FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Screen.frag")));
	screenfrag->Compile(fragShaderCode);
	GLPrograms::ScreenProgram = ResourceManager::LoadProgram(screenvert, screenfrag);
	GLPrograms::ScreenProgram->Name = "Screen";
#pragma endregion

#pragma region Textures
	Textures::MissingTexture = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/texture-missing.png"));
	Textures::MissingTexture->Name = "Missing";
	Textures::UV = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/uv-test.png"));
	Textures::UV->Name = "UV";
	Textures::StandardTexture = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/white.png"));
	Textures::StandardTexture->Name = "Default";
	Textures::ObjectIcon = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/object.png"));
	Textures::ObjectIcon->Name = "Icon";
	Textures::Border = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/border.png"));
	Textures::Border->Name = "Border";
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

	auto standardVert = std::make_shared<GLShader>(ShaderType::Vertex);
	standardVert->Compile(vertShaderCode);
	auto standardFrag = std::make_shared<GLShader>(ShaderType::Fragment);
	standardFrag->Compile(fragShaderCode);
	GLPrograms::StandardProgram = ResourceManager::LoadProgram(standardVert, standardFrag);
	GLPrograms::StandardProgram->Name = "Standard";
	vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/StandardInstanced.vert"));

	standardVert = std::make_shared<GLShader>(ShaderType::Vertex);
	standardVert->Compile(vertShaderCode);
	standardFrag = std::make_shared<GLShader>(ShaderType::Fragment);
	standardFrag->Compile(fragShaderCode);
	GLPrograms::StandardInstancedProgram = ResourceManager::LoadProgram(standardVert, standardFrag);
	GLPrograms::StandardInstancedProgram->Name = "Standard Instanced";
#pragma endregion
#pragma region Gizmo Shader
	fragShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform
		+ "\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Gizmo.frag"));

	vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Gizmo.vert"));

	standardVert = std::make_shared<GLShader>(ShaderType::Vertex);
	standardVert->Compile(vertShaderCode);
	standardFrag = std::make_shared<GLShader>(ShaderType::Fragment);
	standardFrag->Compile(fragShaderCode);
	GLPrograms::GizmoProgram = ResourceManager::LoadProgram(standardVert, standardFrag);
	GLPrograms::GizmoProgram->Name = "Gizmo";
	vertShaderCode = std::string("#version 460 core\n")
		+ *ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/GizmoInstanced.vert"));

	standardVert = std::make_shared<GLShader>(ShaderType::Vertex);
	standardVert->Compile(vertShaderCode);
	standardFrag = std::make_shared<GLShader>(ShaderType::Fragment);
	standardFrag->Compile(fragShaderCode);
	GLPrograms::GizmoInstancedProgram = ResourceManager::LoadProgram(standardVert, standardFrag);
	GLPrograms::GizmoInstancedProgram->Name = "Gizmo Instanced";
#pragma endregion

#pragma region Models & Primitives
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/quad.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Quad = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Quad);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Quad->Name = "Quad";
	}
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/sphere.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Sphere = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Sphere);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Sphere->Name = "Sphere";
	}
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/cube.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Cube = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Cube);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Cube->Name = "Cube";
	}
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/cone.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Cone = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Cone);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Cone->Name = "Cone";
	}
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/cylinder.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Cylinder = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Cylinder);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Cylinder->Name = "Cylinder";
	}
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/ring.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Ring = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Ring);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Ring->Name = "Ring";
	}	
	{
		auto model = ResourceManager::LoadModel(FileIO::GetResourcePath("Primitives/monkey.obj"), GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		Primitives::Monkey = model->RootNode()->Children[0]->_MeshMaterials[0].second;
		ResourceManager::Push(Primitives::Monkey);
		ResourceManager::Remove<Model>(model->GetHashCode());
		Primitives::Monkey->Name = "Monkey";
	}
#pragma endregion

	Materials::StandardMaterial = ResourceManager::LoadMaterial(GLPrograms::StandardProgram);
	Materials::StandardMaterial->Name = "Standard";
	Materials::StandardMaterial->SetTexture(Textures::StandardTexture);

	Materials::StandardInstancedMaterial = ResourceManager::LoadMaterial(GLPrograms::StandardInstancedProgram);
	Materials::StandardInstancedMaterial->SetTexture(Textures::StandardTexture);
	Materials::StandardMaterial->Name = "Standard Instanced";
}

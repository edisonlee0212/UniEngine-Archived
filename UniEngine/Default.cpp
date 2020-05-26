#include "Default.h"
#include "Core.h"
#include "AssimpImporter.h"
#include "Scene.h"
using namespace UniEngine;

GLProgram* Default::Screen::ScreenProgram;
GLVAO* Default::Screen::ScreenVAO;
std::string* Default::ShaderIncludes::MainCamera;
std::string* Default::ShaderIncludes::Lights;
std::string* Default::ShaderIncludes::Material;

Texture2D* Default::Textures::MissingTexture;
Texture2D* Default::Textures::UV;

Mesh* Default::Primitives::Sphere;
Mesh* Default::Primitives::Cube;
Mesh* Default::Primitives::Quad;
Mesh* Default::Primitives::Cone;
Mesh* Default::Primitives::Cylinder;

void UniEngine::Default::Load()
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

	Screen::ScreenVAO = new GLVAO();
	auto quadVBO = Screen::ScreenVAO->VBO()->ID();
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	GLShader* screenvert = new GLShader(ShaderType::Vertex);
	screenvert->SetCode(new std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Vertex/screen.vert"))));
	GLShader* screenfrag = new GLShader(ShaderType::Fragment);
	screenfrag->SetCode(new std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Fragment/screen.frag"))));
	Screen::ScreenProgram = new GLProgram();
	Screen::ScreenProgram->Attach(ShaderType::Vertex, screenvert);
	Screen::ScreenProgram->Attach(ShaderType::Fragment, screenfrag);
	Screen::ScreenProgram->Link();
	Screen::ScreenProgram->SetInt("screenTexture", 0);


	ShaderIncludes::MainCamera = new std::string(FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Include/MainCamera.inc")));

	std::string add = "#define MAX_MATERIALS_AMOUNT " + std::to_string(ShaderIncludes::MaxMaterialsAmount) + "\n";
	ShaderIncludes::Material = new std::string(add + FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Include/Material.inc")));

	add =
		"#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxDirectionalLightAmount) +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxPointLightAmount) +
		"\n#define SPOT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxSpotLightAmount) + "\n";
	ShaderIncludes::Lights = new std::string(add + FileIO::LoadFileAsString(FileIO::GetPath("Shaders/Include/Lights.inc")));

	Textures::MissingTexture = new Texture2D(TextureType::DIFFUSE);
	Textures::MissingTexture->LoadTexture(FileIO::GetPath("Textures/texture-missing.png"), "");
	Textures::UV = new Texture2D(TextureType::DIFFUSE);
	Textures::UV->LoadTexture(FileIO::GetPath("Textures/uv-test.png"), "");

	Scene* scene = new Scene();
	AssimpImporter::LoadScene(scene, FileIO::GetPath("Primitives/sphere.obj"));
	Primitives::Sphere = scene->_Meshes[0];
	Primitives::Sphere->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileIO::GetPath("Primitives/cube.obj"));
	Primitives::Cube = scene->_Meshes[0];
	Primitives::Cube->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileIO::GetPath("Primitives/quad.obj"));
	Primitives::Quad = scene->_Meshes[0];
	Primitives::Quad->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileIO::GetPath("Primitives/cone.obj"));
	Primitives::Cone = scene->_Meshes[0];
	Primitives::Cone->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileIO::GetPath("Primitives/cylinder.obj"));
	Primitives::Cylinder = scene->_Meshes[0];
	Primitives::Cylinder->RecalculateNormal();
	delete scene;
}

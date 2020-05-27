#include "Default.h"
#include "World.h"
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

	Screen::ScreenVAO = new GLVAO();
	auto quadVBO = Screen::ScreenVAO->VBO()->ID();
	Screen::ScreenVAO->Bind();
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

	std::string add = "#define MAX_TEXTURES_AMOUNT " + std::to_string(ShaderIncludes::MaxMaterialsAmount) + "\n";
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

	Entity* entity = world->_EntityCollection->CreateEntity();
	
	
	ModelManager::LoadModel(entity, FileIO::GetPath("Primitives/quad.obj"));
	Primitives::Quad = entity->Children()->at(0)->GetSharedComponent<Mesh>();
	world->_EntityCollection->DeleteEntity(entity);

	entity = world->_EntityCollection->CreateEntity();
	ModelManager::LoadModel(entity, FileIO::GetPath("Primitives/sphere.obj"));
	Primitives::Sphere = entity->Children()->at(0)->GetSharedComponent<Mesh>();
	world->_EntityCollection->DeleteEntity(entity);

	entity = world->_EntityCollection->CreateEntity();
	ModelManager::LoadModel(entity, FileIO::GetPath("Primitives/cube.obj"));
	Primitives::Cube = entity->Children()->at(0)->GetSharedComponent<Mesh>();
	world->_EntityCollection->DeleteEntity(entity);

	

	entity = world->_EntityCollection->CreateEntity();
	ModelManager::LoadModel(entity, FileIO::GetPath("Primitives/cone.obj"));
	Primitives::Cone = entity->Children()->at(0)->GetSharedComponent<Mesh>();
	world->_EntityCollection->DeleteEntity(entity);

	entity = world->_EntityCollection->CreateEntity();
	ModelManager::LoadModel(entity, FileIO::GetPath("Primitives/cylinder.obj"));
	Primitives::Cylinder = entity->Children()->at(0)->GetSharedComponent<Mesh>();
	world->_EntityCollection->DeleteEntity(entity);
}

// Planet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
using namespace UniEngine;
void LoadModelAsEntity(EntityCollection* entityCollection, std::string path, glm::vec3 position, glm::vec3 scale);
void InitGround(EntityCollection* entityCollection);
int main()
{
	EngineDriver* engine = new EngineDriver();
	engine->Start();

#pragma region Preparations
	World* world = engine->GetWorld();
	EntityCollection* ec = world->GetEntityCollection();
	EngineTime* time = world->GetTime();
	bool enableSCTreeSystem = false;
	

	Camera* mainCamera = new Camera(WindowManager::CurrentWindow());
	auto cameraEntity = ec->CreateEntity();
	Position pos;
	pos.value = glm::vec3(0.0f, 5.0f, 0.0f);
	ec->SetFixedData<Position>(cameraEntity, pos);
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = mainCamera;
	ec->SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent);
	

#pragma endregion

#pragma region Models
	InitGround(ec);
	LoadModelAsEntity(ec, FileIO::GetPath("Models/nanosuit/nanosuit.obj"), glm::vec3(6.0f, 0.0f, -4.0f), glm::vec3(0.5f));
	LoadModelAsEntity(ec, FileIO::GetPath("Models/backpack/backpack.obj"), glm::vec3(6.0f, 3.0f, 0.0f), glm::vec3(1.0f));
#pragma endregion

#pragma region Lights
	MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
	dlmmc->_Mesh = Default::Primitives::Cylinder;
	dlmmc->_Material = Default::Materials::StandardMaterial;
	Scale scale;
	scale.value = glm::vec3(0.5f);

	DirectionalLightComponent* dlc = new DirectionalLightComponent();
	dlc->diffuse = glm::vec3(1.0f);
	dlc->specular = glm::vec3(0.5f);
	Entity* dle = ec->CreateEntity();
	ec->SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	ec->SetFixedData<Scale>(dle, scale);
	ec->SetSharedComponent<MeshMaterialComponent>(dle, dlmmc);

	MeshMaterialComponent* plmmc = new MeshMaterialComponent();
	plmmc->_Mesh = Default::Primitives::Sphere;
	plmmc->_Material = Default::Materials::StandardMaterial;
	scale.value = glm::vec3(0.5f);

	PointLightComponent* plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 70.0f;
	plc->diffuse = glm::vec3(2.0f);
	plc->specular = glm::vec3(5.0f);
	Entity* ple = ec->CreateEntity();
	ec->SetSharedComponent<PointLightComponent>(ple, plc);
	ec->SetFixedData<Scale>(ple, scale);
	ec->SetSharedComponent<MeshMaterialComponent>(ple, plmmc);

	plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 70.0f;
	plc->diffuse = glm::vec3(2.0f);
	plc->specular = glm::vec3(5.0f);
	Entity* ple2 = ec->CreateEntity();
	ec->SetSharedComponent<PointLightComponent>(ple2, plc);
	ec->SetFixedData<Scale>(ple2, scale);
	ec->SetSharedComponent<MeshMaterialComponent>(ple2, plmmc);
#pragma endregion

#pragma region EngineLoop
	bool loopable = true;


	while (loopable) {
		loopable = engine->LoopStart();
#pragma region LightsPosition
		Position p;
		p.value = glm::vec4(glm::vec3(0.0f, 20.0f * glm::abs(glm::sin(time->WorldTime() / 2.0f)), -20.0f * glm::cos(time->WorldTime() / 2.0f)), 0.0f);
		ec->SetFixedData<Position>(dle, p);
		p.value = glm::vec4(glm::vec3(-20.0f * glm::cos(time->WorldTime() / 2.0f), 20.0f * glm::abs(glm::sin(time->WorldTime() / 2.0f)), 0.0f), 0.0f);
		ec->SetFixedData<Position>(ple, p);
		p.value = glm::vec4(glm::vec3(20.0f * glm::cos(time->WorldTime() / 2.0f), 15.0f, 20.0f * glm::sin(time->WorldTime() / 2.0f)), 0.0f);
		ec->SetFixedData<Position>(ple2, p);
#pragma endregion
		loopable = engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
#pragma endregion
	return 0;
}
#pragma region ModelLoading
void LoadModelAsEntity(EntityCollection* entityCollection, std::string path, glm::vec3 position, glm::vec3 scale) {
	Entity* suit = entityCollection->CreateEntity();
	Position t;
	t.value = position;
	Scale s;
	s.value = scale;
	entityCollection->SetFixedData<Position>(suit, t);
	entityCollection->SetFixedData<Scale>(suit, s);

	ModelManager::LoadModelAsEntity(suit, path, Default::GLPrograms::StandardProgram);
}

void InitGround(EntityCollection* entityCollection) {
	auto entity = entityCollection->CreateEntity();
	Position translation = Position();
	translation.value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.value = glm::vec3(20.0f);
	entityCollection->SetFixedData<Position>(entity, translation);
	entityCollection->SetFixedData<Scale>(entity, scale);

	auto mat = new Material();
	mat->Programs()->push_back(Default::GLPrograms::StandardProgram);
	auto texture = new Texture2D(TextureType::DIFFUSE);
	texture->LoadTexture(FileIO::GetPath("Textures/floor.png"), "");
	mat->Textures2Ds()->push_back(texture);
	mat->SetMaterialProperty("material.shininess", 32.0f);
	MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
	meshMaterial->_Mesh = Default::Primitives::Quad;
	meshMaterial->_Material = mat;
	entityCollection->SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);
}
#pragma endregion
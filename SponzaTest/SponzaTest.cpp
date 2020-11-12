// SponzaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "UniEngine.h"
#include "CameraControlSystem.h"
using namespace UniEngine;
void LightSettingMenu();
void InitGround();


float lightAngle6 = 0;

enum TestScene {
	BACKPACK,
	SPONZA_TEST,
	PCSS,
};
int main()
{
	FileIO::SetResourcePath("../Resources/");
	RenderManager::SetEnableSSAO(true);
#pragma region Lighting and Shadow settings
	RenderManager::SetEnableShadow(true);
	RenderManager::SetDirectionalLightResolution(4096);
	RenderManager::SetStableFit(false);
	RenderManager::SetSeamFixRatio(0.05f);
	RenderManager::SetMaxShadowDistance(300);
	RenderManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
#pragma endregion
	Application::Init();
#pragma region Preparations
	auto world = Application::GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", LocalToWorld(), LocalToParent());
	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	LocalToWorld ltw;
	ltw.SetPosition(glm::vec3(-40, 25, 3));
	RenderManager::GetMainCamera()->GetOwner().SetComponentData(ltw);

	Entity newCam = EntityManager::CreateEntity(archetype, "Camera");
	newCam.SetPrivateComponent(std::make_unique<CameraComponent>());
	newCam.GetPrivateComponent<CameraComponent>()->get()->ResizeResolution(300, 300);
#pragma endregion
	auto sharedMat = std::make_shared<Material>();
	sharedMat->SetProgram(Default::GLPrograms::DeferredPrepass);
	sharedMat->SetTexture(Default::Textures::StandardTexture, TextureType::DIFFUSE);
	
	auto cylinder = std::make_unique<MeshRenderer>();
	cylinder->Mesh = Default::Primitives::Cylinder;
	cylinder->Material = sharedMat;
	TestScene testScene = BACKPACK;
#pragma region PCSS test
	if (testScene == BACKPACK) {
		auto backpack = AssetManager::LoadModel(FileIO::GetResourcePath("Models/backpack/backpack.obj"), Default::GLPrograms::DeferredPrepass);
		backpack->Name = "Backpack";
		Entity backpackEntity = AssetManager::ToEntity(archetype, backpack);
		backpackEntity.SetName("Backpack");
		ltw.SetPosition(glm::vec3(0, 10, 0));
		ltw.SetScale(glm::vec3(5.0f));
		EntityManager::SetComponentData(backpackEntity, ltw);
		backpackEntity.SetPrivateComponent(std::make_unique<RigidBody>());
	}
	else if (testScene == SPONZA_TEST) {
		//1. Load models using Assimp including textures and meshes and transforms.
		auto backpack = AssetManager::LoadModel(FileIO::GetResourcePath("Models/Sponza/sponza.obj"), Default::GLPrograms::DeferredPrepass);
		backpack->Name = "Sponza Scene";
		Entity backpackEntity = AssetManager::ToEntity(archetype, backpack);
		backpackEntity.SetName("Sponza");
		//2. Set overall transform of the entites. We set the root entity's transform and it will
		//	 automatically apply to the entire model by the parent hierarchy transform calculation. See TransformManager & ParentSystem
		ltw.SetPosition(glm::vec3(5, 5, 5));
		ltw.SetScale(glm::vec3(0.05f));
		EntityManager::SetComponentData(backpackEntity, ltw);
		backpackEntity.SetPrivateComponent(std::make_unique<RigidBody>());
	}
	else if (testScene == PCSS) {
		auto cmmc = std::make_unique<MeshRenderer>();
		cmmc->Mesh = Default::Primitives::Cube;
		cmmc->Material = sharedMat;

		Entity model1 = EntityManager::CreateEntity(archetype);
		ltw.SetPosition(glm::vec3(-6.0f, 7.0f, 0.0f));


		ltw.SetScale(glm::vec3(4.0f, 8.0f, 4.0f));
		EntityManager::SetComponentData(model1, ltw);
		EntityManager::SetPrivateComponent<MeshRenderer>(model1, std::move(cylinder));

		auto mmmc = std::make_unique<MeshRenderer>();
		mmmc->Mesh = Default::Primitives::Sphere;
		mmmc->Material = sharedMat;

		Entity model2 = EntityManager::CreateEntity(archetype);
		ltw.SetPosition(glm::vec3(6.0f, 7.0f, 0.0f));

		ltw.SetScale(glm::vec3(5.0f, 5.0f, 5.0f));
		EntityManager::SetComponentData(model2, ltw);
		EntityManager::SetPrivateComponent<MeshRenderer>(model2, std::move(mmmc));
	}
#pragma endregion
#pragma region Lights
	EntityArchetype dlarc = EntityManager::CreateEntityArchetype("Directional Light", LocalToWorld(), LocalToParent(), DirectionalLight());
	EntityArchetype plarc = EntityManager::CreateEntityArchetype("Point Light", LocalToWorld(), LocalToParent(), PointLight());
	ltw.SetEulerRotation(glm::vec3(70, 0, 0));
	
	DirectionalLight dlc;
	dlc.diffuseBrightness = 0.4f;
	dlc.lightSize = 1.0f;
	Entity dle = EntityManager::CreateEntity(dlarc);
	dle.SetName("Dir Light");
	EntityManager::SetComponentData(dle, dlc);
	EntityManager::SetComponentData(dle, ltw);


	DirectionalLight dlc2;
	dlc2.lightSize = 1.0f;
	Entity dle2 = EntityManager::CreateEntity(dlarc);
	dle2.SetName("Dir Light");
	EntityManager::SetComponentData<DirectionalLight>(dle2, dlc2);
	ltw.SetEulerRotation(glm::vec3(30, 60, 0));
	EntityManager::SetComponentData(dle2, ltw);


	auto plmmc = std::make_unique<MeshRenderer>();
	plmmc->Mesh = Default::Primitives::Sphere;
	plmmc->Material = sharedMat;
	ltw.SetScale(glm::vec3(0.5f));

	PointLight plc;
	plc.constant = 1.0f;
	plc.linear = 0.09f;
	plc.quadratic = 0.032f;
	plc.farPlane = 200.0f;
	plc.diffuse = glm::vec3(3.0f);
	plc.specular = glm::vec3(5.0f);
	Entity ple = EntityManager::CreateEntity(plarc);
	ple.SetName("Point Light");
	EntityManager::SetComponentData<PointLight>(ple, plc);
	EntityManager::SetComponentData(ple, ltw);
	EntityManager::SetPrivateComponent<MeshRenderer>(ple, std::move(plmmc));


#pragma endregion
	FileBrowser file_dialog;
	InitGround();
#pragma region EngineLoop
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	//Another way to run engine is to simply execute:
	//Application.Run();
	while (loopable) {
		Application::PreUpdate();
		LightSettingMenu();
		ImGui::ShowDemoWindow();

#pragma region LightsPosition		
		auto ltw = ple.GetComponentData<LocalToWorld>();
		ltw.SetPosition(glm::vec4(glm::vec3(-30.0f * glm::cos(glm::radians(lightAngle6)), 30.0f * glm::sin(glm::radians(lightAngle6)), 0.0f), 0.0f));
		EntityManager::SetComponentData(ple, ltw);
#pragma endregion
		Application::Update();
		loopable = Application::LateUpdate();
	}
	Application::End();
#pragma endregion
	return 0;
}

void LightSettingMenu() {
	ImGui::Begin("Light Angle Controller");
	ImGui::SliderFloat("Point Light", &lightAngle6, 0.0f, 180.0f);
	ImGui::End();
}

void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", LocalToParent(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	entity.SetName("Ground");
	LocalToWorld ltw;
	ltw.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	ltw.SetScale(glm::vec3(100.0f));
	EntityManager::SetComponentData(entity, ltw);
	/*
	auto entity1 = EntityManager::CreateEntity(archetype);
	translation.Value = glm::vec3(-100.0f, 0.0f, 0.0f);
	scale.Value = glm::vec3(100.0f, 1.0f, 20.0f);
	Rotation rotation;
	rotation.Value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
	EntityManager::SetComponentData<Translation>(entity1, translation);
	EntityManager::SetComponentData<Scale>(entity1, scale);
	EntityManager::SetComponentData<Rotation>(entity1, rotation);

	auto entity2 = EntityManager::CreateEntity(archetype);
	translation.Value = glm::vec3(100.0f, 0.0f, 0.0f);
	scale.Value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.Value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0));

	EntityManager::SetComponentData<Translation>(entity2, translation);
	EntityManager::SetComponentData<Scale>(entity2, scale);
	EntityManager::SetComponentData<Rotation>(entity2, rotation);


	auto entity3 = EntityManager::CreateEntity(archetype);
	translation.Value = glm::vec3(0.0f, 0.0f, -100.0f);
	scale.Value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.Value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));

	EntityManager::SetComponentData<Translation>(entity3, translation);
	EntityManager::SetComponentData<Scale>(entity3, scale);
	EntityManager::SetComponentData<Rotation>(entity3, rotation);

	auto entity4 = EntityManager::CreateEntity(archetype);
	translation.Value = glm::vec3(0.0f, 0.0f, 100.0f);
	scale.Value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.Value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));

	EntityManager::SetComponentData<Translation>(entity4, translation);
	EntityManager::SetComponentData<Scale>(entity4, scale);
	EntityManager::SetComponentData<Rotation>(entity4, rotation);

	*/
	auto mat = std::make_shared<Material>();
	mat->SetProgram(Default::GLPrograms::StandardProgram);
	
	auto texture = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/floor.png"));
	mat->SetTexture(texture, TextureType::DIFFUSE);
	/*
	auto textureD = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/bricks2.jpg"));
	mat->SetTexture(textureD, TextureType::DIFFUSE);
	auto textureN = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/bricks2_normal.jpg"));
	mat->SetTexture(textureN, TextureType::NORMAL);
	auto textureH = AssetManager::LoadTexture(FileIO::GetResourcePath("Textures/bricks2_disp.jpg"));
	mat->SetTexture(textureH, TextureType::DISPLACEMENT);
	*/
	
	mat->SetShininess(32.0f);
	auto meshMaterial = std::make_unique<MeshRenderer>();
	meshMaterial->Mesh = Default::Primitives::Quad;
	meshMaterial->Material = mat;
	EntityManager::SetPrivateComponent<MeshRenderer>(entity, std::move(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity1, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity2, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity3, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity4, std::shared_ptr<MeshRenderer>(meshMaterial));
}

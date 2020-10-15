// SponzaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "UniEngine.h"
#include "CameraControlSystem.h"
using namespace UniEngine;
void LightSettingMenu();
void InitGround();
void SplitDisplay();
float lightAngle0 = 25;
float lightAngle1 = 0;
float lightAngle2 = 0;
float lightAngle3 = 0;
float lightAngle4 = 0.8f;
float lightAngle5 = 0.0f;
float lightAngle6 = 0;
float lightAngle7 = 0;
float lightAngle8 = 0;
float lightSize = 0.5;
float lightBleedControl = 0.0;
float pcssScale = 1.0f;
bool enableNormalMapping = true;

float ssaobias = 0.025f;
float ssaoradius = 3.0f;
float ssaoscale = 4.0f;
float ssaofactor = 1.0f;
int ssaoSampleSize = 4;
enum TestScene {
	NANOSUIT,
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
	RenderManager::SetMaxShadowDistance(500);
	RenderManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
#pragma endregion
	Application::Init();
	Application::SetEnableSkybox(true);
#pragma region Preparations
	World* world = Application::GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	ccs->EnableWindowControl(true);
	ccs->SetPosition(glm::vec3(-40, 25, 3));
	EntityArchetype backpackArchetype = EntityManager::CreateEntityArchetype("Model",
		LocalToParent(),
		Translation(),
		Scale(),
		LocalToWorld());



#pragma endregion
	auto sharedMat = std::make_shared<Material>();
	sharedMat->SetProgram(Default::GLPrograms::DeferredPrepass);
	sharedMat->SetTexture(Default::Textures::StandardTexture);
	
	MeshRenderer* cylinder = new MeshRenderer();
	cylinder->Mesh = Default::Primitives::Cylinder;
	cylinder->Material = sharedMat;
	Scale scale;
	scale.Value = glm::vec3(0.5f);
	TestScene testScene = BACKPACK;
#pragma region PCSS test
	if (testScene == NANOSUIT) {
		auto backpack = ModelManager::LoadModel(FileIO::GetResourcePath("Models/nanosuit/nanosuit.obj"), Default::GLPrograms::DeferredPrepass);
		Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
		backpackEntity.SetName("Nanosuit");
		Translation bpp;
		bpp.Value = glm::vec3(0, 5, 0);
		Scale bps;
		bps.Value = glm::vec3(2.0f);
		EntityManager::SetComponentData<Translation>(backpackEntity, bpp);
		EntityManager::SetComponentData<Scale>(backpackEntity, bps);
	}
	else if (testScene == BACKPACK) {
		auto backpack = ModelManager::LoadModel(FileIO::GetResourcePath("Models/backpack/backpack.obj"), Default::GLPrograms::DeferredPrepass);
		Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
		backpackEntity.SetName("Backpack");
		Translation bpp;
		bpp.Value = glm::vec3(0, 10, 0);
		Scale bps;
		bps.Value = glm::vec3(5.0f);
		EntityManager::SetComponentData<Translation>(backpackEntity, bpp);
		EntityManager::SetComponentData<Scale>(backpackEntity, bps);
	}
	else if (testScene == SPONZA_TEST) {
		//1. Load models using Assimp including textures and meshes and transforms.
		auto backpack = ModelManager::LoadModel(FileIO::GetResourcePath("Models/Sponza/sponza.obj"), Default::GLPrograms::DeferredPrepass);
		Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
		backpackEntity.SetName("Sponza");
		//2. Set overall transform of the entites. We set the root entity's transform and it will
		//	 automatically apply to the entire model by the parent hierarchy transform calculation. See TransformSystem & ParentSystem
		Translation bpp;
		bpp.Value = glm::vec3(5, 5, 5);
		Scale bps;
		bps.Value = glm::vec3(0.05f);
		EntityManager::SetComponentData<Translation>(backpackEntity, bpp);
		EntityManager::SetComponentData<Scale>(backpackEntity, bps);
	}
	else if (testScene == PCSS) {
		MeshRenderer* cmmc = new MeshRenderer();
		cmmc->Mesh = Default::Primitives::Cube;
		cmmc->Material = sharedMat;
		Translation pos;

		Entity model1 = EntityManager::CreateEntity(archetype);
		pos.Value = glm::vec3(-6.0f, 7.0f, 0.0f);


		scale.Value = glm::vec3(4.0f, 8.0f, 4.0f);
		EntityManager::SetComponentData<Translation>(model1, pos);
		EntityManager::SetComponentData<Scale>(model1, scale);
		EntityManager::SetSharedComponent<MeshRenderer>(model1, std::shared_ptr<MeshRenderer>(cylinder));

		MeshRenderer* mmmc = new MeshRenderer();
		mmmc->Mesh = Default::Primitives::Sphere;
		mmmc->Material = sharedMat;

		Entity model2 = EntityManager::CreateEntity(archetype);
		pos.Value = glm::vec3(6.0f, 7.0f, 0.0f);

		scale.Value = glm::vec3(5.0f, 5.0f, 5.0f);
		EntityManager::SetComponentData<Translation>(model2, pos);
		EntityManager::SetComponentData<Scale>(model2, scale);
		EntityManager::SetSharedComponent<MeshRenderer>(model2, std::shared_ptr<MeshRenderer>(mmmc));
	}
#pragma endregion
#pragma region Lights

	MeshRenderer* dlmmc = new MeshRenderer();
	cylinder->Mesh = Default::Primitives::Ring;
	cylinder->Material = sharedMat;
	scale.Value = glm::vec3(0.5f);

	DirectionalLightComponent* dlc = new DirectionalLightComponent();

	Entity dle = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, std::shared_ptr<DirectionalLightComponent>(dlc));
	EntityManager::SetComponentData<Scale>(dle, scale);


	DirectionalLightComponent* dlc2 = new DirectionalLightComponent();
	Entity dle2 = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle2, std::shared_ptr<DirectionalLightComponent>(dlc2));
	EntityManager::SetComponentData<Scale>(dle2, scale);


	MeshRenderer* plmmc = new MeshRenderer();
	plmmc->Mesh = Default::Primitives::Sphere;
	plmmc->Material = sharedMat;
	scale.Value = glm::vec3(0.5f);

	PointLightComponent* plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 200.0f;
	plc->diffuse = glm::vec3(3.0f);
	plc->specular = glm::vec3(5.0f);
	Entity ple = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<PointLightComponent>(ple, std::shared_ptr<PointLightComponent>(plc));
	EntityManager::SetComponentData<Scale>(ple, scale);
	EntityManager::SetSharedComponent<MeshRenderer>(ple, std::shared_ptr<MeshRenderer>(plmmc));


#pragma endregion

	InitGround();
#pragma region EngineLoop
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	//Another way to run engine is to simply execute:
	//Application.Run();
	while (loopable) {
		Application::PreUpdate();
		LightSettingMenu();
		SplitDisplay();
		//ImGui::ShowDemoWindow();
#pragma region LightsPosition
		Rotation r;
		r.Value = glm::quatLookAt(
			glm::normalize(glm::vec3(
				glm::cos(glm::radians(lightAngle0)) * glm::sin(glm::radians(lightAngle1)),
				glm::sin(glm::radians(lightAngle0)),
				glm::cos(glm::radians(lightAngle0)) * glm::cos(glm::radians(lightAngle1))))
			, glm::vec3(0, 1, 0));
		EntityManager::SetComponentData<Rotation>(dle, r);

		r.Value = glm::quatLookAt(
			glm::normalize(glm::vec3(
				glm::cos(glm::radians(lightAngle2)) * glm::sin(glm::radians(lightAngle3)),
				glm::sin(glm::radians(lightAngle2)),
				glm::cos(glm::radians(lightAngle2)) * glm::cos(glm::radians(lightAngle3))))
			, glm::vec3(0, 1, 0));
		EntityManager::SetComponentData<Rotation>(dle2, r);

		dlc->specular = glm::vec3(lightAngle8);
		dlc->diffuse = glm::vec3(lightAngle4);
		dlc2->specular = glm::vec3(lightAngle8);
		dlc2->diffuse = glm::vec3(lightAngle5);
		plc->specular = glm::vec3(lightAngle8);
		
		Translation p;
		p.Value = glm::vec4(glm::vec3(-30.0f * glm::cos(glm::radians(lightAngle6)), 30.0f * glm::sin(glm::radians(lightAngle6)), 0.0f), 0.0f);
		EntityManager::SetComponentData<Translation>(ple, p);
		plc->diffuse = glm::vec3(lightAngle7);

		ImGui::Begin("Light Bleed Control");
		ImGui::SliderFloat("Factor", &lightBleedControl, 0.0f, 1.0f);
		ImGui::End();
		RenderManager::SetLightBleedControlFactor(lightBleedControl);

		ImGui::Begin("PCSS Scale factor");
		ImGui::SliderFloat("Factor", &pcssScale, 0.0f, 2.0f);
		ImGui::End();
		RenderManager::SetPCSSScaleFactor(pcssScale);

		ImGui::Begin("Directional Light Size");
		ImGui::SliderFloat("Size", &lightSize, 0.0f, 1.0f);
		ImGui::End();
		dlc->lightSize = lightSize;

#pragma endregion

		ImGui::Begin("SSAO");
		ImGui::SliderFloat("Radius", &ssaoradius, 0.1f, 5.0f);
		ImGui::SliderFloat("Bias", &ssaobias, 0.0f, 1.0f);
		ImGui::SliderFloat("Scale", &ssaoscale, 1.0f, 10.0f);
		ImGui::SliderFloat("Factor", &ssaofactor, 1.0f, 10.0f);
		ImGui::SliderInt("Sample Size", &ssaoSampleSize, 0, 64);
		ImGui::End();
		RenderManager::SetSSAOKernelRadius(ssaoradius);
		RenderManager::SetSSAOKernelBias(ssaobias);
		RenderManager::SetSSAOScale(ssaoscale);
		RenderManager::SetSSAOFactor(ssaofactor);
		RenderManager::SetSSAOSampleSize(ssaoSampleSize);
		Application::Update();
		loopable = Application::LateUpdate();
	}
	Application::End();
#pragma endregion
	return 0;
}

void LightSettingMenu() {
	ImGui::Begin("Light Angle Controller");
	ImGui::SliderFloat("Soft light angle", &lightAngle0, 0.0f, 89.0f);
	ImGui::SliderFloat("Soft light circle", &lightAngle1, 0.0f, 360.0f);
	ImGui::SliderFloat("Hard light angle", &lightAngle2, 0.0f, 89.0f);
	ImGui::SliderFloat("Hard light circle", &lightAngle3, 0.0f, 360.0f);
	ImGui::SliderFloat("Soft Light brightness", &lightAngle4, 0.0f, 2.0f);
	ImGui::SliderFloat("Hard light brightness", &lightAngle5, 0.0f, 2.0f);
	ImGui::SliderFloat("Point Light", &lightAngle6, 0.0f, 180.0f);
	ImGui::SliderFloat("Point Light brightness", &lightAngle7, 0.0f, 10.0f);
	ImGui::SliderFloat("Specular light brightness", &lightAngle8, 0.0f, 2.0f);
	ImGui::End();
}

bool _DisplaySplit = false;

void SplitDisplay() {
	ImGui::Begin("Cascades Shadow Map");
	std::string text = std::string(_DisplaySplit ? "Disable" : "Enable");
	if (ImGui::Button(text.c_str())) {
		_DisplaySplit = !_DisplaySplit;
		RenderManager::SetPCSSBSAmount(_DisplaySplit);
	}
	ImGui::End();
}

void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Translation translation = Translation();
	translation.Value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.Value = glm::vec3(100.0f);
	EntityManager::SetComponentData<Translation>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);
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
	mat->SetProgram(Default::GLPrograms::DeferredPrepass);
	auto texture = std::make_shared<Texture2D>(TextureType::DIFFUSE);
	texture->LoadTexture(FileIO::GetResourcePath("Textures/floor.png"), "");
	mat->SetTexture(texture);
	mat->SetShininess(32.0f);
	auto meshMaterial = std::make_shared<MeshRenderer>();
	meshMaterial->Mesh = Default::Primitives::Quad;
	meshMaterial->Material = mat;
	EntityManager::SetSharedComponent<MeshRenderer>(entity, meshMaterial);
	//EntityManager::SetSharedComponent<MeshRenderer>(entity1, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity2, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity3, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity4, std::shared_ptr<MeshRenderer>(meshMaterial));
}

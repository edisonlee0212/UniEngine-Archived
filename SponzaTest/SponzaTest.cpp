// SponzaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "UniEngine.h"
#include "CameraControlSystem.h"

using namespace UniEngine;
void LightAngleSlider();
void InitGround();
void SplitDisplay();
float lightAngle0 = 0;
float lightAngle1 = 0;
float lightAngle2 = 0;
float lightAngle3 = 0;
float lightAngle4 = 0.8f;
float lightAngle5 = 0.0f;
float lightAngle6 = 0;
float lightAngle7 = 0;
float lightSize = 0.5;
float lightBleedControl = 0.0;
float pcssScale = 1.0f;
bool enableNormalMapping = true;
enum TestScene {
	NANOSUIT,
	BACKPACK,
	SPONZA_TEST,
	PCSS,
};
int main()
{
#pragma region Lighting and Shadow settings
	LightingManager::SetDirectionalLightResolution(1024);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(500);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
#pragma endregion
	Application::Init();
#pragma region Preparations
	World* world = Application::GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;


	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Translation, Rotation, Scale, LocalToWorld>(Translation(), Rotation(), Scale(), LocalToWorld());
	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	ccs->EnableWindowControl(true);
	ccs->SetPosition(glm::vec3(-40, 25, 3));
	EntityArchetype backpackArchetype = EntityManager::CreateEntityArchetype(
		LocalToParent(),
		Translation(),
		Scale(),
		LocalToWorld());



#pragma endregion
	MeshMaterialComponent* cylinder = new MeshMaterialComponent();
	cylinder->_Mesh = Default::Primitives::Cylinder;
	cylinder->_Material = Default::Materials::StandardMaterial;
	Scale scale;
	scale.Value = glm::vec3(0.5f);
	TestScene testScene = NANOSUIT;
#pragma region PCSS test
	if (testScene == NANOSUIT) {
		Model* backpack = ModelManager::LoadModel(FileIO::GetPath("Models/nanosuit/nanosuit.obj"), Default::GLPrograms::StandardProgram);
		Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
		Translation bpp;
		bpp.Value = glm::vec3(0, 5, 0);
		Scale bps;
		bps.Value = glm::vec3(2.0f);
		EntityManager::SetComponentData<Translation>(backpackEntity, bpp);
		EntityManager::SetComponentData<Scale>(backpackEntity, bps);
	}
	else if (testScene == BACKPACK) {
		Model* backpack = ModelManager::LoadModel(FileIO::GetPath("Models/backpack/backpack.obj"), Default::GLPrograms::StandardProgram);
		Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
		Translation bpp;
		bpp.Value = glm::vec3(0, 10, 0);
		Scale bps;
		bps.Value = glm::vec3(5.0f);
		EntityManager::SetComponentData<Translation>(backpackEntity, bpp);
		EntityManager::SetComponentData<Scale>(backpackEntity, bps);
	}
	else if (testScene == SPONZA_TEST) {
		//1. Load models using Assimp including textures and meshes and transforms.
		Model* backpack = ModelManager::LoadModel(FileIO::GetPath("Models/Sponza/sponza.obj"), Default::GLPrograms::StandardProgram);
		Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
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
		MeshMaterialComponent* cmmc = new MeshMaterialComponent();
		cmmc->_Mesh = Default::Primitives::Cube;
		cmmc->_Material = Default::Materials::StandardMaterial;
		Translation pos;

		Entity model1 = EntityManager::CreateEntity(archetype);
		pos.Value = glm::vec3(-6.0f, 7.0f, 0.0f);


		scale.Value = glm::vec3(4.0f, 8.0f, 4.0f);
		EntityManager::SetComponentData<Translation>(model1, pos);
		EntityManager::SetComponentData<Scale>(model1, scale);
		EntityManager::SetSharedComponent<MeshMaterialComponent>(model1, cylinder);

		MeshMaterialComponent* mmmc = new MeshMaterialComponent();
		mmmc->_Mesh = Default::Primitives::Sphere;
		mmmc->_Material = Default::Materials::StandardMaterial;

		Entity model2 = EntityManager::CreateEntity(archetype);
		pos.Value = glm::vec3(6.0f, 7.0f, 0.0f);

		scale.Value = glm::vec3(5.0f, 5.0f, 5.0f);
		EntityManager::SetComponentData<Translation>(model2, pos);
		EntityManager::SetComponentData<Scale>(model2, scale);
		EntityManager::SetSharedComponent<MeshMaterialComponent>(model2, mmmc);
	}
#pragma endregion
#pragma region Lights

	MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
	cylinder->_Mesh = Default::Primitives::Ring;
	cylinder->_Material = Default::Materials::StandardMaterial;
	scale.Value = glm::vec3(0.5f);

	DirectionalLightComponent* dlc = new DirectionalLightComponent();

	Entity dle = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	EntityManager::SetComponentData<Scale>(dle, scale);


	DirectionalLightComponent* dlc2 = new DirectionalLightComponent();
	Entity dle2 = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle2, dlc2);
	EntityManager::SetComponentData<Scale>(dle2, scale);


	MeshMaterialComponent* plmmc = new MeshMaterialComponent();
	plmmc->_Mesh = Default::Primitives::Sphere;
	plmmc->_Material = Default::Materials::StandardMaterial;
	scale.Value = glm::vec3(0.5f);

	PointLightComponent* plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 200.0f;
	plc->diffuse = glm::vec3(3.0f);
	plc->specular = glm::vec3(5.0f);
	Entity ple = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<PointLightComponent>(ple, plc);
	EntityManager::SetComponentData<Scale>(ple, scale);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(ple, plmmc);

#pragma endregion
	InitGround();
#pragma region EngineLoop
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	//Another way to run engine is to simply execute:
	//Application.Run();
	while (loopable) {
		Application::PreUpdate();
		LightAngleSlider();
		SplitDisplay();
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

		dlc->specular = glm::vec3(lightAngle4);
		dlc->diffuse = glm::vec3(lightAngle4);
		dlc2->specular = glm::vec3(lightAngle5);
		dlc2->diffuse = glm::vec3(lightAngle5);

		Translation p;
		p.Value = glm::vec4(glm::vec3(-30.0f * glm::cos(glm::radians(lightAngle6)), 30.0f * glm::sin(glm::radians(lightAngle6)), 0.0f), 0.0f);
		EntityManager::SetComponentData<Translation>(ple, p);
		plc->diffuse = glm::vec3(lightAngle7);

		ImGui::Begin("Light Bleed Control");
		ImGui::SliderFloat("Factor", &lightBleedControl, 0.0f, 1.0f);
		ImGui::End();
		LightingManager::SetLightBleedControlFactor(lightBleedControl);

		ImGui::Begin("PCSS Scale factor");
		ImGui::SliderFloat("Factor", &pcssScale, 0.0f, 2.0f);
		ImGui::End();
		LightingManager::SetPCSSScaleFactor(pcssScale);

		ImGui::Begin("Directional Light Size");
		ImGui::SliderFloat("Size", &lightSize, 0.0f, 1.0f);
		ImGui::End();
		dlc->lightSize = lightSize;

#pragma endregion
		Application::Update();
		loopable = Application::LateUpdate();
	}
	Application::End();
#pragma endregion
	return 0;
}

void LightAngleSlider() {
	ImGui::Begin("Light Angle Controller");
	ImGui::SliderFloat("Soft light angle", &lightAngle0, 0.0f, 89.0f);
	ImGui::SliderFloat("Soft light circle", &lightAngle1, 0.0f, 360.0f);
	ImGui::SliderFloat("Hard light angle", &lightAngle2, 0.0f, 89.0f);
	ImGui::SliderFloat("Hard light circle", &lightAngle3, 0.0f, 360.0f);
	ImGui::SliderFloat("Soft Light brightness", &lightAngle4, 0.0f, 2.0f);
	ImGui::SliderFloat("Hard light brightness", &lightAngle5, 0.0f, 2.0f);
	ImGui::SliderFloat("Point Light", &lightAngle6, 0.0f, 180.0f);
	ImGui::SliderFloat("Point Light brightness", &lightAngle7, 0.0f, 10.0f);
	ImGui::End();
}

bool _DisplaySplit = false;

void SplitDisplay() {
	ImGui::Begin("Cascades Shadow Map");
	std::string text = std::string(_DisplaySplit ? "Disable" : "Enable");
	if (ImGui::Button(text.c_str())) {
		_DisplaySplit = !_DisplaySplit;
		LightingManager::SetEnableSplitDisplay(_DisplaySplit);
	}
	ImGui::End();
}

void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Translation, Rotation, Scale, LocalToWorld>(Translation(), Rotation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Translation translation = Translation();
	translation.Value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.Value = glm::vec3(100.0f);
	EntityManager::SetComponentData<Translation>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);

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


	auto mat = new Material();
	mat->Programs()->push_back(Default::GLPrograms::StandardProgram);
	auto texture = new Texture2D(TextureType::DIFFUSE);
	texture->LoadTexture(FileIO::GetPath("Textures/floor.png"), "");
	mat->Textures2Ds()->push_back(texture);
	mat->SetMaterialProperty("material.shininess", 32.0f);
	MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
	meshMaterial->_Mesh = Default::Primitives::Quad;
	meshMaterial->_Material = mat;
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity1, meshMaterial);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity2, meshMaterial);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity3, meshMaterial);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity4, meshMaterial);
}

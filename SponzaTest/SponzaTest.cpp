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
float lightAngle4 = 0.7f;
float lightAngle5 = 0.2f;
float lightAngle6 = 0;
float lightAngle7 = 0;
int main()
{
 	Engine* engine = new Engine();
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetEnableVSM(true);
	LightingManager::SetStableFit(true);
	LightingManager::SetEnableEVSM(false);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(400);

	LightingManager::SetVSMMaxVariance(0.01f);
	LightingManager::SetLightBleedControlFactor(0.7f);
	LightingManager::SetEVSMExponent(40.0f);

	LightingManager::SetSplitRatio(0.1f, 0.2f, 0.4f, 1.0f);
	auto window = WindowManager::CreateGLFWwindow(1600, 900, "Main", NULL);
	engine->Start(window, 1600, 900);

#pragma region Preparations
	World* world = engine->GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;
	
	Camera* mainCamera = new Camera(WindowManager::CurrentWindow(), 0.1f, 500.0f);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());

	auto cameraEntity = EntityManager::CreateEntity(archetype);
	Position pos;
	pos.value = glm::vec3(0.0f, 5.0f, 10.0f);
	EntityManager::SetComponentData<Position>(cameraEntity, pos);
	Scale scale;
	scale.value = glm::vec3(1.0f);
	EntityManager::SetComponentData<Scale>(cameraEntity, scale);
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = mainCamera;
	EntityManager::SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent);

	engine->SetMainCamera(cameraEntity);

	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>();
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(15.0f);
	ccs->Enable();
	ccs->SetTargetCamera(cameraEntity);

	EntityArchetype backpackArchetype = EntityManager::CreateEntityArchetype<
		//LocalPosition, 
		//LocalRotation,
		//LocalScale,
		LocalToParent,
		Position,
		Rotation,
		Scale,
		LocalToWorld
	>(//LocalPosition(),
	//LocalRotation(),
	//LocalScale(),
		LocalToParent(),
		Position(),
		Rotation(),
		Scale(),
		LocalToWorld());

	Model* backpack = ModelManager::LoadModel(FileIO::GetPath("Models/Sponza/sponza.obj"), Default::GLPrograms::StandardProgram);
	Entity backpackEntity = ModelManager::ToEntity(backpackArchetype, backpack);
	Position bpp;
	bpp.value = glm::vec3(5, 5, 5);
	Scale bps;
	bps.value = glm::vec3(0.05f);
	EntityManager::SetComponentData<Position>(backpackEntity, bpp);
	EntityManager::SetComponentData<Scale>(backpackEntity, bps);
#pragma endregion

#pragma region Lights
	
	MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
	dlmmc->_Mesh = Default::Primitives::Cylinder;
	dlmmc->_Material = Default::Materials::StandardMaterial;
	scale.value = glm::vec3(0.5f);

	DirectionalLightComponent* dlc = new DirectionalLightComponent();

	dlc->softShadow = true;
	Entity dle = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	EntityManager::SetComponentData<Scale>(dle, scale);

	
	DirectionalLightComponent* dlc2 = new DirectionalLightComponent();
	Entity dle2 = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle2, dlc2);
	EntityManager::SetComponentData<Scale>(dle2, scale);
	/*

	MeshMaterialComponent* plmmc = new MeshMaterialComponent();
	plmmc->_Mesh = Default::Primitives::Sphere;
	plmmc->_Material = Default::Materials::StandardMaterial;
	scale.value = glm::vec3(0.5f);
	
	PointLightComponent* plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 70.0f;
	plc->diffuse = glm::vec3(3.0f);
	plc->specular = glm::vec3(5.0f);
	Entity ple = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<PointLightComponent>(ple, plc);
	EntityManager::SetComponentData<Scale>(ple, scale);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(ple, plmmc);

	PointLightComponent* plc2 = new PointLightComponent();
	plc2->constant = 1.0f;
	plc2->linear = 0.09f;
	plc2->quadratic = 0.032f;
	plc2->farPlane = 70.0f;
	plc2->diffuse = glm::vec3(3.0f);
	plc2->specular = glm::vec3(5.0f);
	Entity ple2 = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<PointLightComponent>(ple2, plc2);
	EntityManager::SetComponentData<Scale>(ple2, scale);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(ple2, plmmc);*/
#pragma endregion

#pragma region EngineLoop
	bool loopable = true;


	while (loopable) {
		loopable = engine->LoopStart();

		LightAngleSlider();
		SplitDisplay();
#pragma region LightsPosition
		Rotation r;
		r.value = glm::quatLookAt(
			glm::normalize(glm::vec3(
				glm::cos(glm::radians(lightAngle0)) * glm::sin(glm::radians(lightAngle1)),
				glm::sin(glm::radians(lightAngle0)),
				glm::cos(glm::radians(lightAngle0)) * glm::cos(glm::radians(lightAngle1))))
			, glm::vec3(0, 1, 0));
		EntityManager::SetComponentData<Rotation>(dle, r);

		r.value = glm::quatLookAt(
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

		Position p;
		p.value = glm::vec4(glm::vec3(-20.0f * glm::cos(glm::radians(lightAngle6)), 20.0f * glm::sin(glm::radians(lightAngle6)), 0.0f), 0.0f);
		//EntityManager::SetComponentData<Position>(ple, p);
		p.value = glm::vec4(glm::vec3(20.0f * glm::cos(glm::radians(lightAngle7)), 15.0f, 20.0f * glm::sin(glm::radians(lightAngle7))), 0.0f);
		//EntityManager::SetComponentData<Position>(ple2, p);
#pragma endregion
		loopable = engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
#pragma endregion
	return 0;
}

void LightAngleSlider() {
	ImGui::Begin("Light Angle Controller");
	ImGui::SliderFloat("Directional Light 1 angle", &lightAngle0, 0.0f, 180.0f);
	ImGui::SliderFloat("Directional Light 1 circle", &lightAngle1, 0.0f, 360.0f);
	ImGui::SliderFloat("Directional Light 2 angle", &lightAngle2, 0.0f, 180.0f);
	ImGui::SliderFloat("Directional Light 2 circle", &lightAngle3, 0.0f, 360.0f);
	ImGui::SliderFloat("Directional Light 1 brightness", &lightAngle4, 0.0f, 2.0f);
	ImGui::SliderFloat("Directional Light 2 brightness", &lightAngle5, 0.0f, 2.0f);
	ImGui::SliderFloat("Point Light 1", &lightAngle6, 0.0f, 180.0f);
	ImGui::SliderFloat("Point Light 2", &lightAngle7, 0.0f, 360.0f);
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
	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Position translation = Position();
	translation.value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.value = glm::vec3(40.0f);
	EntityManager::SetComponentData<Position>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);

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
}

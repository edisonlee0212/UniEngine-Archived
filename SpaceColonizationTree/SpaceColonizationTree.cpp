#include "UniEngine.h"
#include "SCTreeSystem.h"
#include "CameraControlSystem.h"

using namespace UniEngine;
using namespace SpaceColonizationTree;

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
float lightSize = 0.01;
float lightBleedControl = 0.0;
float pcssScale = 1.0f;
int main()
{
	Engine* engine = new Engine();
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetShadowMode(ShadowMode::PCSS);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(300);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
	auto window = WindowManager::CreateGLFWwindow(1600, 900, "Main", NULL);
	engine->Start(window, 1600, 900);
	
#pragma region Preparations
	World* world = engine->GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;
	SCTreeSystem* ts = world->CreateSystem<SCTreeSystem>();
	ts->Enable();

	Camera* mainCamera = new Camera(WindowManager::CurrentWindow(), 0.1f, 500.0f);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());

	auto cameraEntity = EntityManager::CreateEntity(archetype);
	Position pos;
	pos.value = glm::vec3(0.0f, 5.0f, 10.0f);
	EntityManager::SetComponentData<Position>(cameraEntity, pos);
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = mainCamera;
	EntityManager::SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent);

	engine->SetMainCamera(cameraEntity);

	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>();
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(15.0f);
	ccs->Enable();
	ccs->SetTargetCamera(cameraEntity);
	
	
#pragma endregion
	
#pragma region Lights
	MeshMaterialComponent* cylinder = new MeshMaterialComponent();
	cylinder->_Mesh = Default::Primitives::Cylinder;
	cylinder->_Material = Default::Materials::StandardMaterial;
	Scale scale;
	scale.value = glm::vec3(0.5f);

	MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
	cylinder->_Mesh = Default::Primitives::Cylinder;
	cylinder->_Material = Default::Materials::StandardMaterial;
	scale.value = glm::vec3(0.5f);

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
	scale.value = glm::vec3(0.5f);

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
		p.value = glm::vec4(glm::vec3(-30.0f * glm::cos(glm::radians(lightAngle6)), 30.0f * glm::sin(glm::radians(lightAngle6)), 0.0f), 0.0f);
		EntityManager::SetComponentData<Position>(ple, p);
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
		loopable = engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
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
	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Position translation = Position();
	translation.value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.value = glm::vec3(100.0f);
	EntityManager::SetComponentData<Position>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);

	auto entity1 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(0.0f, -100.0f, 0.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	Rotation rotation;
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
	EntityManager::SetComponentData<Position>(entity1, translation);
	EntityManager::SetComponentData<Scale>(entity1, scale);
	EntityManager::SetComponentData<Rotation>(entity1, rotation);

	auto entity2 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(0.0f, -100.0f, 0.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0));

	EntityManager::SetComponentData<Position>(entity2, translation);
	EntityManager::SetComponentData<Scale>(entity2, scale);
	EntityManager::SetComponentData<Rotation>(entity2, rotation);


	auto entity3 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(0.0f, -100.0f, 0.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));

	EntityManager::SetComponentData<Position>(entity3, translation);
	EntityManager::SetComponentData<Scale>(entity3, scale);
	EntityManager::SetComponentData<Rotation>(entity3, rotation);

	auto entity4 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(0.0f, -100.0f, 0.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));

	EntityManager::SetComponentData<Position>(entity4, translation);
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

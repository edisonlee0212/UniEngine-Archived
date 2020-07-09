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
float lightAngle4 = 0;
float lightAngle5 = 0;
float lightAngle6 = 0;
float lightAngle7 = 0;
int main()
{
	Engine* engine = new Engine();
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetEnableVSM(false);
	LightingManager::SetStableFit(true);
	LightingManager::SetEnableEVSM(true);
	LightingManager::SetSeamFixRatio(0.1f);
	LightingManager::SetMaxShadowDistance(400);
	LightingManager::SetSplitRatio(0.1f, 0.3f, 0.6f, 1.0f);
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
	MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
	dlmmc->_Mesh = Default::Primitives::Cylinder;
	dlmmc->_Material = Default::Materials::StandardMaterial;
	Scale scale;
	scale.value = glm::vec3(0.5f);

	DirectionalLightComponent* dlc = new DirectionalLightComponent();
	dlc->diffuse = glm::vec3(0.25f);
	dlc->specular = glm::vec3(0.2f);
	dlc->softShadow = true;
	Entity dle = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	EntityManager::SetComponentData<Scale>(dle, scale);
	
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
	EntityManager::SetSharedComponent<MeshMaterialComponent>(ple2, plmmc);
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
		
		Position p;
		p.value = glm::vec4(glm::vec3(-20.0f * glm::cos(glm::radians(lightAngle6)), 20.0f * glm::sin(glm::radians(lightAngle6)), 0.0f), 0.0f);
		EntityManager::SetComponentData<Position>(ple, p);
		p.value = glm::vec4(glm::vec3(20.0f * glm::cos(glm::radians(lightAngle7)), 15.0f, 20.0f * glm::sin(glm::radians(lightAngle7))), 0.0f);
		EntityManager::SetComponentData<Position>(ple2, p);
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
	ImGui::SliderFloat("Directional Light angle", &lightAngle0, 0.0f, 180.0f);
	ImGui::SliderFloat("Directional Light circle", &lightAngle1, 0.0f, 360.0f);
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
	scale.value = glm::vec3(100.0f);
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

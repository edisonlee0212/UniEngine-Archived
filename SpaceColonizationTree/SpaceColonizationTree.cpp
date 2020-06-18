#include "UniEngine.h"
#include "SCTreeSystem.h"
#include "CameraControlSystem.h"

using namespace UniEngine;
using namespace SpaceColonizationTree;

void InitGround();

int main()
{
	Engine* engine = new Engine();
	engine->Start();
	
#pragma region Preparations
	World* world = engine->GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;
	SCTreeSystem* ts = world->CreateSystem<SCTreeSystem>();
	ts->Enable();
	ts->BuildEnvelope();
	ts->BuildTree();

	Camera* mainCamera = new Camera(WindowManager::CurrentWindow());

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());

	auto cameraEntity = EntityManager::CreateEntity(archetype);
	Position pos;
	pos.value = glm::vec3(0.0f, 5.0f, 10.0f);
	EntityManager::SetComponentData<Position>(cameraEntity, pos);
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = mainCamera;
	EntityManager::SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent);

	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>();
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(15.0f);
	ccs->Enable();
	ccs->SetTargetCamera(cameraEntity);

	SCTreeSystem* scts = world->CreateSystem<SCTreeSystem>();



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
	Entity dle = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	EntityManager::SetComponentData<Scale>(dle, scale);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(dle, dlmmc);

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
	Entity ple = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<PointLightComponent>(ple, plc);
	EntityManager::SetComponentData<Scale>(ple, scale);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(ple, plmmc);

	plc = new PointLightComponent();
	plc->constant = 1.0f;
	plc->linear = 0.09f;
	plc->quadratic = 0.032f;
	plc->farPlane = 70.0f;
	plc->diffuse = glm::vec3(2.0f);
	plc->specular = glm::vec3(5.0f);
	Entity ple2 = EntityManager::CreateEntity(archetype);
	EntityManager::SetSharedComponent<PointLightComponent>(ple2, plc);
	EntityManager::SetComponentData<Scale>(ple2, scale);
	EntityManager::SetSharedComponent<MeshMaterialComponent>(ple2, plmmc);
#pragma endregion

	InitGround();

#pragma region EngineLoop
	bool loopable = true;


	while (loopable) {
		loopable = engine->LoopStart();
#pragma region LightsPosition
		Position p;
		p.value = glm::vec4(glm::vec3(0.0f, 20.0f * glm::sin(time->Time() / 2.0f), -20.0f * glm::cos(time->Time() / 2.0f)), 0.0f);
		EntityManager::SetComponentData<Position>(dle, p);
		p.value = glm::vec4(glm::vec3(-20.0f * glm::cos(time->Time() / 2.0f), 20.0f * glm::sin(time->Time() / 2.0f), 0.0f), 0.0f);
		EntityManager::SetComponentData<Position>(ple, p);
		p.value = glm::vec4(glm::vec3(20.0f * glm::cos(time->Time() / 2.0f), 15.0f, 20.0f * glm::sin(time->Time() / 2.0f)), 0.0f);
		EntityManager::SetComponentData<Position>(ple2, p);
#pragma endregion
		loopable = engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
#pragma endregion
	return 0;
}

void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Position translation = Position();
	translation.value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.value = glm::vec3(20.0f);
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


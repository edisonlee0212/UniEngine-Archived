// Galaxy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "ParentSystem.h"
#include "StarClusterSystem.h"

using namespace UniEngine;
using namespace Galaxy;
struct StarTag : ComponentBase
{
};

void Worker(int i) {
	//std::cout << i << std::endl;
}

void example_function()
{
	std::cout << "bla" << std::endl;
}

int main()
{
	
#pragma region Engine Preparations
	Engine* engine = new Engine();
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(500);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
	LightingManager::SetAmbientLight(1.0f);
	auto window = WindowManager::CreateGLFWwindow(1918, 1060, "Main", nullptr);
	engine->Start(window, 1918, 1060);
	World* world = engine->GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;

	Camera* mainCamera = new Camera(WindowManager::CurrentWindow(), 0.1f, 500.0f);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Translation, Rotation, Scale, LocalToWorld>(Translation(), Rotation(), Scale(), LocalToWorld());

	auto cameraEntity = EntityManager::CreateEntity(archetype);
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = mainCamera;
	EntityManager::SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent);

	engine->SetMainCamera(cameraEntity);

	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	ccs->SetTargetCamera(cameraEntity);
	ccs->EnableWindowControl(true);
	ccs->SetPosition(glm::vec3(-40, 25, 3));

	
#pragma endregion

	auto starClusterSystem = world->CreateSystem<StarClusterSystem>(SystemGroup::SimulationSystemGroup);
	starClusterSystem->SetCamera(mainCamera);
	starClusterSystem->Enable();
/*
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
*/
#pragma region Stars
	auto starMat = new Material();
	starMat->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto starTex = new Texture2D(TextureType::DIFFUSE);
	starTex->LoadTexture(FileIO::GetPath("Textures/green.png"), "");
	starMat->Textures2Ds()->push_back(starTex);
	//Generate an entity archetype for cube
	EntityArchetype starArchetype =
		EntityManager::CreateEntityArchetype<StarTag, Translation, Rotation, Scale, LocalToWorld>(StarTag(), Translation(), Rotation(), Scale(), LocalToWorld());
	//Create 200 * 200 = 40000 Cubes
	int width = 300;
	for (int i = 0; i < width * width; i++) {
		auto entity = EntityManager::CreateEntity(starArchetype);
	}
	//Create entityquery for operations
	EntityQuery eq = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<StarTag>(eq, StarTag());
	//Multiple Components Query is allowed
	//EntityManager::SetEntityQueryAllFilters<StarTag, LocalToWorld>(eq, StarTag(), LocalToWorld());
#pragma endregion
#pragma region EngineLoop
	bool loopable = true;
	//Create an array to hold matrices data for cubes.
	std::vector<LocalToWorld> matrices = std::vector<LocalToWorld>();
	float timer = 0.0f;
	float speed = 1.0f;
	while (loopable) {
		loopable = engine->LoopStart();
		//Finish engine loop.
		loopable = engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
#pragma endregion
	return 0;
}
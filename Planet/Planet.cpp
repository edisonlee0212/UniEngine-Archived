// Planet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "PlanetTerrainSystem.h"
#include "PerlinNoiseStage.h"

using namespace UniEngine;
using namespace Planet;
int main()
{
	FileIO::SetResourcePath("../Resources/");

	RenderManager::SetAmbientLight(0.3f);
	Application::Init();

#pragma region Preparations
	auto world = Application::GetWorld();
	WorldTime* time = world->Time();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", LocalToParent(), LocalToWorld());

	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(15.0f);
	ccs->Enable();

	RenderManager::GetMainCamera()->DrawSkyBox = false;
	
	PlanetTerrainSystem* pts = world->CreateSystem<PlanetTerrainSystem>(SystemGroup::SimulationSystemGroup);
	pts->Enable();

	PlanetInfo pi;
	LocalToParent planetTransform;
	
	planetTransform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	planetTransform.SetEulerRotation(glm::vec3(0.0f));
	pi.MaxLodLevel = 8;
	pi.LodDistance = 7.0;
	pi.Radius = 10.0;
	pi.Index = 0;
	pi.Resolution = 8;

	auto planetTerrain1 = std::make_unique<PlanetTerrain>(pi, pts->GetDefaultSurfaceMaterial());
	planetTerrain1->TerrainConstructionStages.push_back(std::make_shared<PerlinNoiseStage>());
	auto planet1 = EntityManager::CreateEntity(archetype);
	planet1.SetPrivateComponent(std::move(planetTerrain1));
	planet1.SetComponentData(planetTransform);
	planet1.SetName("Planet 1");
	planetTransform.SetPosition(glm::vec3(35.0f, 0.0f, 0.0f));
	pi.MaxLodLevel = 20;
	pi.LodDistance = 7.0;
	pi.Radius = 15.0;
	pi.Index = 1;
	auto planetTerrain2 = std::make_unique<PlanetTerrain>(pi, pts->GetDefaultSurfaceMaterial());
	auto planet2 = EntityManager::CreateEntity(archetype);
	planet2.SetPrivateComponent(std::move(planetTerrain2));
	planet2.SetComponentData(planetTransform);
	planet2.SetName("Planet 2");
	planetTransform.SetPosition(glm::vec3(-20.0f, 0.0f, 0.0f));
	pi.MaxLodLevel = 4;
	pi.LodDistance = 7.0;
	pi.Radius = 5.0;
	pi.Index = 2;
	auto planetTerrain3 = std::make_unique<PlanetTerrain>(pi, pts->GetDefaultSurfaceMaterial());
	auto planet3 = EntityManager::CreateEntity(archetype);
	planet3.SetPrivateComponent(std::move(planetTerrain3));
	planet3.SetComponentData(planetTransform);
	planet3.SetName("Planet 3");
#pragma endregion

#pragma region Lights
	EntityArchetype dlarc = EntityManager::CreateEntityArchetype("Directional Light", LocalToParent(), LocalToWorld(), DirectionalLight());
	EntityArchetype plarc = EntityManager::CreateEntityArchetype("Point Light", LocalToParent(), LocalToWorld(), PointLight());
	auto sharedMat = std::make_shared<Material>();
	sharedMat->SetTexture(Default::Textures::StandardTexture, TextureType::DIFFUSE);
	
	LocalToParent ltw;
	DirectionalLight dlc;
	dlc.diffuse = glm::vec3(1.0f);
	dlc.specular = glm::vec3(0.5f);
	Entity dle = EntityManager::CreateEntity(dlarc);
	dle.SetName("Directional Light 1");
	EntityManager::SetComponentData<DirectionalLight>(dle, dlc);
	
	auto plmmc = std::make_unique<MeshRenderer>();
	auto plmmc2 = std::make_unique<MeshRenderer>();
	plmmc->Mesh = Default::Primitives::Sphere;
	plmmc->Material = sharedMat;
	plmmc2->Mesh = Default::Primitives::Sphere;
	plmmc2->Material = sharedMat;
	ltw.SetScale(glm::vec3(0.5f));

	PointLight plc;
	plc.constant = 1.0f;
	plc.linear = 0.09f;
	plc.quadratic = 0.032f;
	plc.farPlane = 70.0f;
	plc.diffuse = glm::vec3(1.0f);
	plc.diffuseBrightness = 5;
	plc.specularBrightness = 2;
	plc.specular = glm::vec3(1.0f);
	Entity ple = EntityManager::CreateEntity(plarc);
	EntityManager::SetComponentData<PointLight>(ple, plc);
	EntityManager::SetComponentData(ple, ltw);
	ple.SetName("Point Light 1");
	EntityManager::SetPrivateComponent<MeshRenderer>(ple, std::move(plmmc));

	plc.constant = 1.0f;
	plc.linear = 0.09f;
	plc.quadratic = 0.032f;
	plc.farPlane = 70.0f;
	plc.diffuse = glm::vec3(1.0f);
	plc.specular = glm::vec3(1.0f);
	Entity ple2 = EntityManager::CreateEntity(plarc);
	EntityManager::SetComponentData<PointLight>(ple2, plc);
	EntityManager::SetComponentData(ple2, ltw);
	ple2.SetName("Point Light 2");
	EntityManager::SetPrivateComponent<MeshRenderer>(ple2, std::move(plmmc2));
#pragma endregion

#pragma region EngineLoop
	bool loopable = true;
	

	bool wireFrame = false;
	while (loopable) {
		Application::PreUpdate();
		static bool show = true;
#pragma region LightsPosition
		ltw.SetPosition(glm::vec4(glm::vec3(0.0f, 20.0f * glm::sin(Application::EngineTime() / 2.0f), -20.0f * glm::cos(Application::EngineTime() / 2.0f)), 0.0f));
		EntityManager::SetComponentData(dle, ltw);
		ltw.SetPosition(glm::vec4(glm::vec3(-20.0f * glm::cos(Application::EngineTime() / 2.0f), 20.0f * glm::sin(Application::EngineTime() / 2.0f), 0.0f), 0.0f));
		EntityManager::SetComponentData(ple, ltw);
		ltw.SetPosition(glm::vec4(glm::vec3(20.0f * glm::cos(Application::EngineTime() / 2.0f), 15.0f, 20.0f * glm::sin(Application::EngineTime() / 2.0f)), 0.0f));
		EntityManager::SetComponentData(ple2, ltw);
#pragma endregion

		Application::Update();
		loopable = Application::LateUpdate();
	}
	Application::End();
#pragma endregion
	return 0;
}

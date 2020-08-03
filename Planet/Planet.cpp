// Planet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "RenderSystem.h"
#include "CameraControlSystem.h"
#include "PlanetTerrainSystem.h"
using namespace UniEngine;
using namespace Planet;
int main()
{
	Engine::Init();

#pragma region Preparations
	World* world = Engine::GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Translation, Rotation, Scale, LocalToWorld>(Translation(), Rotation(), Scale(), LocalToWorld());

	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(15.0f);
	ccs->Enable();

	PlanetTerrainSystem* pts = world->CreateSystem<PlanetTerrainSystem>(SystemGroup::SimulationSystemGroup);
	pts->Enable();

	PlanetInfo pi;
	pi.Position = glm::dvec3(0.0f, 0.0f, 0.0f);
	pi.Rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	pi.MaxLodLevel = 8;
	pi.LodDistance = 2.0f;
	pi.Radius = 10.0;
	pi.Index = 0;
	pi.Resolution = 64;
	pts->CreatePlanet(pi);

	pi.Position = glm::dvec3(35.0f, 0.0f, 0.0f);
	pi.MaxLodLevel = 20;
	pi.LodDistance = 2.0f;
	pi.Radius = 15.0;
	pi.Index = 1;
	pts->CreatePlanet(pi);

	pi.Position = glm::dvec3(-20.0f, 0.0f, 0.0f);
	pi.MaxLodLevel = 4;
	pi.LodDistance = 2.0f;
	pi.Radius = 5.0;
	pi.Index = 2;
	pts->CreatePlanet(pi);

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

#pragma region EngineLoop
	bool loopable = true;
	
	//RenderSystem::SetWireFrameMode(true);
	bool wireFrame = false;
	while (loopable) {
		Engine::PreUpdate();
		static bool show = true;
#pragma region LightsPosition
		Translation p;
		p.value = glm::vec4(glm::vec3(0.0f, 20.0f * glm::sin(time->Time() / 2.0f), -20.0f * glm::cos(time->Time() / 2.0f)), 0.0f);
		EntityManager::SetComponentData<Translation>(dle, p);
		p.value = glm::vec4(glm::vec3(-20.0f * glm::cos(time->Time() / 2.0f), 20.0f * glm::sin(time->Time() / 2.0f), 0.0f), 0.0f);
		EntityManager::SetComponentData<Translation>(ple, p);
		p.value = glm::vec4(glm::vec3(20.0f * glm::cos(time->Time() / 2.0f), 15.0f, 20.0f * glm::sin(time->Time() / 2.0f)), 0.0f);
		EntityManager::SetComponentData<Translation>(ple2, p);
#pragma endregion

		ImGui::Begin("Wire Frame");
		std::string text = std::string(wireFrame ? "Disable" : "Enable");
		if (ImGui::Button(text.c_str())) {
			wireFrame = !wireFrame;
			RenderSystem::SetWireFrameMode(wireFrame);
		}
		ImGui::End();
		Engine::Update();
		loopable = Engine::LateUpdate();
	}
	Engine::End();
#pragma endregion
	return 0;
}

// Galaxy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "StarClusterSystem.h"
using namespace UniEngine;
using namespace Galaxy;

int main()
{
	FileIO::SetResourcePath("../Resources/"); 
#pragma region Application Preparations
	Application::Init();
	RenderManager::SetAmbientLight(0.1f);
	World* world = Application::GetWorld();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
#pragma endregion
#pragma region Star System
	auto starClusterSystem = world->CreateSystem<StarClusterSystem>(SystemGroup::SimulationSystemGroup);
	starClusterSystem->Enable();
#pragma endregion

#pragma region Light
	EntityArchetype dlarc = EntityManager::CreateEntityArchetype("Directional Light", EulerRotation(), Rotation(), DirectionalLightComponent());
	EulerRotation er;
	er.Value = glm::vec3(90, 0, 0);
	DirectionalLightComponent dlc;
	dlc.lightSize = 1.0f;
	Entity dle = EntityManager::CreateEntity(dlarc);
	dle.SetName("Dir Light");
	EntityManager::SetComponentData<DirectionalLightComponent>(dle, dlc);
	dle.SetComponentData(er);
#pragma endregion

#pragma region EngineLoop
	bool loopable = true;
	Application::Run();
	Application::End();
#pragma endregion
	return 0;
}
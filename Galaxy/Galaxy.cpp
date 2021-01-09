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
	auto& world = Application::GetCurrentWorld();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Transform(), GlobalTransform());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
#pragma endregion
#pragma region Star System
	auto starClusterSystem = world->CreateSystem<StarClusterSystem>(SystemGroup::SimulationSystemGroup);
	starClusterSystem->Enable();
#pragma endregion

#pragma region Light
	GlobalTransform ltw;
	ltw.SetEulerRotation(glm::vec3(90, 0, 0));
	auto dlc = std::make_unique<DirectionalLight>();
	dlc->lightSize = 1.0f;
	Entity dle = EntityManager::CreateEntity("Directional Light");
	dle.SetName("Dir Light");
	EntityManager::SetPrivateComponent(dle, std::move(dlc));
	dle.SetComponentData(ltw);
#pragma endregion

#pragma region EngineLoop
	Application::Run();
	Application::End();
#pragma endregion
	return 0;
}
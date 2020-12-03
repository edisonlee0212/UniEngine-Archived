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
	auto world = Application::GetWorld();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Transform(), GlobalTransform());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
#pragma endregion
#pragma region Star System
	auto starClusterSystem = world->CreateSystem<StarClusterSystem>(SystemGroup::SimulationSystemGroup);
	starClusterSystem->Enable();
#pragma endregion

#pragma region Light
	EntityArchetype dlarc = EntityManager::CreateEntityArchetype("Directional Light", Transform(), GlobalTransform(), DirectionalLight());
	GlobalTransform ltw;
	ltw.SetEulerRotation(glm::vec3(90, 0, 0));
	DirectionalLight dlc;
	dlc.lightSize = 1.0f;
	Entity dle = EntityManager::CreateEntity(dlarc);
	dle.SetName("Dir Light");
	EntityManager::SetComponentData<DirectionalLight>(dle, dlc);
	dle.SetComponentData(ltw);
#pragma endregion

#pragma region EngineLoop
	bool loopable = true;
	Application::Run();
	Application::End();
#pragma endregion
	return 0;
}
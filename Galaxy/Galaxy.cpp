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
	RenderManager::SetAmbientLight(1.0f);
	World* world = Application::GetWorld();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
#pragma endregion
#pragma region Star System
	auto starClusterSystem = world->CreateSystem<StarClusterSystem>(SystemGroup::SimulationSystemGroup);
	starClusterSystem->Enable();
#pragma endregion
#pragma region EngineLoop
	bool loopable = true;
	Application::Run();
	Application::End();
#pragma endregion
	return 0;
}
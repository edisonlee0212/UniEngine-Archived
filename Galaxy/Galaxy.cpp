// Galaxy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"
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
#pragma region Application Preparations
	Application::Init();
	LightingManager::SetAmbientLight(1.0f);
	World* world = Application::GetWorld();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype(Translation(), Rotation(), Scale(), LocalToWorld());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
	ccs->SetPosition(glm::vec3(0));
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
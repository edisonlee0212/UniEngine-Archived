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
	engine->Start();
	World* world = engine->GetWorld();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Translation, Rotation, Scale, LocalToWorld>(Translation(), Rotation(), Scale(), LocalToWorld());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
	ccs->SetTargetCamera(engine->GetMainCameraEntity());
	ccs->SetPosition(glm::vec3(0));
#pragma endregion
#pragma region Star System
	auto starClusterSystem = world->CreateSystem<StarClusterSystem>(SystemGroup::SimulationSystemGroup);
	starClusterSystem->SetCameraEntity(engine->GetMainCameraEntity());
	starClusterSystem->Enable();
#pragma endregion
#pragma region Stars
	//Generate an entity archetype for cube
	EntityArchetype starArchetype =
		EntityManager::CreateEntityArchetype<StarTag, Translation, Rotation, Scale, LocalToWorld>(StarTag(), Translation(), Rotation(), Scale(), LocalToWorld());
	//Create 200 * 200 = 40000 Cubes
	int width = 300;
	for (int i = 0; i < width * width; i++) {
		auto entity = EntityManager::CreateEntity(starArchetype);
	}
#pragma endregion
#pragma region EngineLoop
	bool loopable = true;
	while (loopable) {
		engine->LoopStart();
		engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
#pragma endregion
	return 0;
}
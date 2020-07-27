// Galaxy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"

using namespace UniEngine;
int main()
{
	Engine* engine = new Engine();
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(500);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
	LightingManager::SetAmbientLight(1.0f);
	auto window = WindowManager::CreateGLFWwindow(1600, 900, "Main", NULL);
	engine->Start(window, 1600, 900);

#pragma region Preparations
	World* world = engine->GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;

	Camera* mainCamera = new Camera(WindowManager::CurrentWindow(), 0.1f, 500.0f);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());

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

	std::vector<Entity> _Stars = std::vector<Entity>();
	for (int i = 0; i < 100000; i++) {
		auto entity = EntityManager::CreateEntity(archetype);
		_Stars.push_back(entity);
	}

#pragma region EngineLoop
	bool loopable = true;

	EntityQuery eq = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld>(eq, LocalToWorld());

	while (loopable) {
		loopable = engine->LoopStart();
		EntityManager::ForEach<Position, Scale>(eq, [](int i, Position* p, Scale* s) {
			p->value = glm::vec3(0.0, 0.001f * (float)i, 0.0f);
			s->value = glm::vec3(1.0f);
			});

		loopable = engine->Loop();
		loopable = engine->LoopEnd();
	}
	engine->End();
#pragma endregion
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

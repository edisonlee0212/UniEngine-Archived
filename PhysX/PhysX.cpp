#include "UniEngine.h"

using namespace UniEngine;

int main()
{
	FileIO::SetResourcePath("../Resources/");
	RenderManager::SetEnableSSAO(true);
	Application::Init();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());

	Entity e1 = EntityManager::CreateEntity(archetype);
	Entity e2 = EntityManager::CreateEntity(archetype);
	Entity e3 = EntityManager::CreateEntity(archetype);
	Entity e4 = EntityManager::CreateEntity(archetype);
	EntityManager::DeleteEntity(e1);
	EntityManager::DeleteEntity(e2);
	EntityManager::DeleteEntity(e3);
	EntityManager::DeleteEntity(e4);
	e1 = EntityManager::CreateEntity(archetype);
	e2 = EntityManager::CreateEntity(archetype);
	e3 = EntityManager::CreateEntity(archetype);
	e4 = EntityManager::CreateEntity(archetype);

	
#pragma region EngineLoop
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	//Another way to run engine is to simply execute:
	//Application.Run();
	while (loopable) {
		Application::PreUpdate();
		
		Application::Update();
		loopable = Application::LateUpdate();
	}
	Application::End();
#pragma endregion
	return 0;
}

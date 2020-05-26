#include "World.h"
#include "Core.h"
#include "EntityManager.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "ShadowSystem.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "SharedComponentSystem.h"
using namespace UniEngine;

Camera* World::_MainCamera;

World::World() {
	
	Entities = new EntityManager();
	//Initialization System Group
	CreateSystem<TimeSystem>();
	CreateSystem<InputSystem>();

	//Simulation System Group
	CreateSystem<PhysicsSystem>();
	CreateSystem<TransformSystem>();
	CreateSystem<ShadowSystem>();

	//Presentation System Group
	CreateSystem<RenderSystem>();

	

	_MainCamera = new Camera();
	auto cameraEntity = Entities->CreateEntity();
	cameraEntity->SetSharedComponent<Camera>(_MainCamera);

}

template <class T>
T* World::CreateSystem() {
	T* system = GetSystem<T>();
	if (system != nullptr) {
		return system;
	}
	system = new T();
	system->SetEntityManager(Entities);
	system->OnCreate();
	_Systems.push_back((SystemBase*)system);
	return system;
}
template <class T>
void World::DestroySystem() {
	T* system = GetSystem<T>();
	if (system != nullptr) {
		system->OnDestroy();
		delete system;
	}
}
template <class T>
T* World::GetSystem() {
	for (auto i : _Systems) {
		if (dynamic_cast<T*>(i) != nullptr) {
			return dynamic_cast<T*>(i);
		}
	}
}
World::~World() {
	for (auto i : _Systems) {
		i->OnDestroy();
		delete i;
	}
}
void World::Update() {
	if (Time::FixedDeltaTime() >= _TimeStep) {
		Time::SetFixedDeltaTime(0);
		for (auto i : _Systems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	
	for (auto i : _Systems) {
		if (i->Enabled()) i->Update();
	}
}

Camera* UniEngine::World::MainCamera()
{
	return _MainCamera;
}

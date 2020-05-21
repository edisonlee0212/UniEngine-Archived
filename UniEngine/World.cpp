#include "World.h"
#include "Core.h"
#include "EntityManager.h"
using namespace UniEngine;
World::World() {
	Entities = new EntityManager();
}

template <class T>
T* World::CreateSystem() {
	T* system = World::GetSystem<T>();
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
	T* system = World::GetSystem<T>();
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
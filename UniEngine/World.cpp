#include "World.h"

using namespace UniEngine;

World::World() {
}

template <class T>
T* World::CreateSystem() {
	for (auto i : _Systems) {
		if (dynamic_cast<T*>(i) != nullptr) {
			return dynamic_cast<T*>(i);
		}
	}
	T* system = new T();
	system->OnCreate();
	_Systems.push_back(dynamic_cast<SystemBase*>(system));
	return system;
}
template <class T>
void World::DestroySystem() {
	for (auto i : _Systems) {
		if (dynamic_cast<T*>(i) != nullptr) {
			i->OnDestroy();
			delete i;
		}
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
	for (auto i : _Systems) {
		if (i->IsEnabled()) i->Update();
	}
}
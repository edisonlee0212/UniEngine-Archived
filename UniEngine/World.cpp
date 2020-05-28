#include "World.h"
#include "Core.h"
#include "ManagerBase.h"
#include "EntityCollection.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "SharedComponentSystem.h"
#include "WindowManager.h"
#include "CameraComponent.h"
using namespace UniEngine;


World::World() {
	
	_EntityCollection = new EntityCollection();
	ManagerBase::_EntityCollection = _EntityCollection;
	ManagerBase::_World = this;

	

}

void UniEngine::World::Init()
{
	//Initialization System Group
	CreateSystem<TimeSystem>();
	CreateSystem<InputSystem>();

	//Simulation System Group
	CreateSystem<PhysicsSystem>();
	CreateSystem<TransformSystem>();

	//Presentation System Group
	CreateSystem<RenderSystem>();



	_MainCamera = new Camera(WindowManager::CurrentWindow());
	auto cameraEntity = _EntityCollection->CreateEntity();
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = _MainCamera;
	_EntityCollection->SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent) ;
}



template <class T>
T* World::CreateSystem() {
	T* system = GetSystem<T>();
	if (system != nullptr) {
		return system;
	}
	system = new T();
	system->_EntityCollection = _EntityCollection;
	system->_World = this;
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
	return nullptr;
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

#pragma once
#include "EntityCollection.h"
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class UECORE_API World
	{
		EngineTime* _Time;
		std::vector<SystemBase*> _Systems;
		EntityCollection* _EntityCollection;
		size_t _Index;
	public:
		size_t GetIndex();
		World(size_t index);
		void Init();
		EngineTime* GetTime();
		template <class T>
		T* CreateSystem();
		template <class T>
		void DestroySystem();
		template <class T>
		T* GetSystem();
		~World();
		void Update();
		EntityCollection* GetEntityCollection();
	};

	template <class T>
	T* World::CreateSystem() {
		T* system = GetSystem<T>();
		if (system != nullptr) {
			return system;
		}
		system = new T();
		system->_EntityCollection = _EntityCollection;
		system->_World = this;
		system->_Time = _Time;
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
}

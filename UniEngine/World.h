#pragma once
#include "Misc.h"
#include "EntityCollection.h"
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class World
	{
		std::vector<SystemBase*> _Systems;
		float _TimeStep;
		Camera* _MainCamera;
		EntityCollection* _EntityCollection;
		inline void InitImGui();
		inline void DrawInfoWindow();

	public:
		World();
		void Init();
		template <class T>
		T* CreateSystem();
		template <class T>
		void DestroySystem();
		template <class T>
		T* GetSystem();
		~World();
		void Update();
		EntityCollection* GetEntityCollection();
		Camera* MainCamera();
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

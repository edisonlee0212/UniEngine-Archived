#pragma once
#include "EntitiesAPI.h"
#include "SystemBase.h"
#include "WorldTime.h"
#include "Entity.h"
namespace UniEngine {
	struct ENTITIES_API Bound {
		glm::vec3 Center;
		glm::vec3 Size;
		float Radius;
		Bound();
	};

	enum class ENTITIES_API SystemGroup {
		PreparationSystemGroup,
		SimulationSystemGroup,
		PresentationSystemGroup
	};
	class ENTITIES_API World
	{
		WorldTime* _Time;
		std::vector<SystemBase*> _PreparationSystems;
		std::vector<SystemBase*> _SimulationSystems;
		std::vector<SystemBase*> _PresentationSystems;
		size_t _Index;
		UniEngine::Bound _WorldBound;
		ThreadPool* _ThreadPool;
	public:
		Bound GetBound();
		void SetBound(Bound value);
		void SetWorldTime(double time);
		void SetTimeStep(float timeStep);
		size_t GetIndex();
		World(size_t index, ThreadPool* threadPool);
		void Init();
		WorldTime* Time();
		template <class T>
		T* CreateSystem(SystemGroup group);
		template <class T>
		void DestroySystem();
		template <class T>
		T* GetSystem();
		~World();
		void Update();
	};

	template <class T>
	T* World::CreateSystem(SystemGroup group) {
		T* system = GetSystem<T>();
		if (system != nullptr) {
			return system;
		}
		system = new T();
		system->_World = this;
		system->_Time = _Time;
		system->_ThreadPool = _ThreadPool;
		system->OnCreate();
		switch (group)
		{
		case UniEngine::SystemGroup::PreparationSystemGroup:
			_PreparationSystems.push_back((SystemBase*)system);
			break;
		case UniEngine::SystemGroup::SimulationSystemGroup:
			_SimulationSystems.push_back((SystemBase*)system);
			break;
		case UniEngine::SystemGroup::PresentationSystemGroup:
			_PresentationSystems.push_back((SystemBase*)system);
			break;
		default:
			break;
		}

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
		for (auto i : _PreparationSystems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		for (auto i : _SimulationSystems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		for (auto i : _PresentationSystems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		return nullptr;
	}
}
#pragma once
#include "UniEngineAPI.h"
#include "SystemBase.h"
#include "WorldTime.h"
#include "Entity.h"
#include "PrivateComponentStorage.h"
#include "SharedComponentStorage.h"
namespace UniEngine {
	struct UNIENGINE_API Bound {
		glm::vec3 Min;
		glm::vec3 Max;
		Bound();
		glm::vec3 Size() const;

		glm::vec3 Center() const;

		bool InBound(glm::vec3 position) const;

		void ApplyTransform(glm::mat4 transform);

		void PopulateCorners(std::vector<glm::vec3>& corners) const;
	};

	enum class UNIENGINE_API SystemGroup {
		PreparationSystemGroup,
		SimulationSystemGroup,
		PresentationSystemGroup
	};


	struct WorldEntityStorage {
		size_t Index;
		size_t ParentHierarchyVersion = 0;
		std::vector<Entity> Entities;
		std::vector<Entity> ParentRoots;
		std::vector<EntityInfo> EntityInfos;
		std::vector<EntityComponentStorage> EntityComponentStorage;
		SharedComponentStorage EntitySharedComponentStorage;
		PrivateComponentStorage EntityPrivateComponentStorage;
		std::vector<EntityQuery> EntityQueries;
		std::vector<EntityQueryInfo> EntityQueryInfos;
		std::queue<EntityQuery> EntityQueryPools;
	};
	
	class UNIENGINE_API World
	{
		friend class Application;
		friend class EntityManager;
		friend class SerializationManager;
		WorldEntityStorage _WorldEntityStorage;
		WorldTime* _Time;
		std::vector<SystemBase*> _PreparationSystems;
		std::vector<SystemBase*> _SimulationSystems;
		std::vector<SystemBase*> _PresentationSystems;
		std::vector<std::function<void()>> _ExternalFixedUpdateFunctions;
		size_t _Index;
		UniEngine::Bound _WorldBound;
		bool _NeedFixedUpdate = false;
	public:
		void Purge();
		World& operator=(World&&) = delete;
		World& operator=(const World&) = delete;
		void RegisterFixedUpdateFunction(const std::function<void()>& func);
		Bound GetBound() const;
		void SetBound(Bound value);
		void SetFrameStartTime(double time) const;
		void SetTimeStep(float timeStep) const;
		size_t GetIndex() const;
		World(size_t index);
		void ResetTime() const;
		WorldTime* Time() const;
		template <class T = SystemBase>
		T* CreateSystem(SystemGroup group);
		template <class T = SystemBase>
		void DestroySystem();
		template <class T = SystemBase>
		T* GetSystem();
		~World();
		void PreUpdate();
		void Update();
		void LateUpdate();
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
		system->OnCreate();
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
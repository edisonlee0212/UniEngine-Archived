#pragma once
#include "UniEngineAPI.h"
#include "SystemBase.h"
#include "WorldTime.h"
namespace UniEngine {
	struct UNIENGINE_API Bound {
		glm::vec3 Center;
		glm::vec3 Size;
		float Radius;
		Bound();
		bool InBound(glm::vec3 position) const
		{
			if (glm::abs(position.x - Center.x) > Size.x) return false;
			if (glm::abs(position.y - Center.y) > Size.y) return false;
			if (glm::abs(position.z - Center.z) > Size.z) return false;
			return true;
		}
	};

	enum class UNIENGINE_API SystemGroup {
		PreparationSystemGroup,
		SimulationSystemGroup,
		PresentationSystemGroup
	};
	class UNIENGINE_API World
	{
		friend class Application;
		WorldTime* _Time;
		std::vector<SystemBase*> _PreparationSystems;
		std::vector<SystemBase*> _SimulationSystems;
		std::vector<SystemBase*> _PresentationSystems;
		std::vector<std::function<void()>> _ExternalFixedUpdateFunctions;
		size_t _Index;
		UniEngine::Bound _WorldBound;
		ThreadPool* _ThreadPool;
		bool _NeedFixedUpdate = false;
	public:
		void RegisterFixedUpdateFunction(const std::function<void()>& func);
		ThreadPool* GetThreadPool() const;
		Bound GetBound() const;
		void SetBound(Bound value);
		void SetFrameStartTime(double time) const;
		void SetTimeStep(float timeStep) const;
		size_t GetIndex() const;
		World(size_t index, ThreadPool* threadPool);
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
		system->_ThreadPool = _ThreadPool;
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
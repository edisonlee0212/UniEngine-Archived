#pragma once
#include "UniEngineAPI.h"
#include "SystemBase.h"
#include "WorldTime.h"
namespace UniEngine {
	struct UNIENGINE_API Bound {
		glm::vec3 Min;
		glm::vec3 Max;
		Bound();
		glm::vec3 Size() const
		{
			return (Max - Min) / 2.0f;
		}
		glm::vec3 Center() const
		{
			return (Max + Min) / 2.0f;
		}
		bool InBound(glm::vec3 position) const
		{
			glm::vec3 center = (Min + Max) / 2.0f;
			glm::vec3 size = (Max - Min) / 2.0f;
			if (glm::abs(position.x - center.x) > size.x) return false;
			if (glm::abs(position.y - center.y) > size.y) return false;
			if (glm::abs(position.z - center.z) > size.z) return false;
			return true;
		}
		void ApplyTransform(glm::mat4 transform)
		{
			std::vector<glm::vec3> corners;
			PopulateCorners(corners);
			Min = glm::vec3(FLT_MAX);
			Max = glm::vec3(FLT_MIN);

			// Transform all of the corners, and keep track of the greatest and least
			// values we see on each coordinate axis.
			for (int i = 0; i < 8; i++) {
				glm::vec3 transformed = transform * glm::vec4(corners[i], 1.0f);
				Min = glm::min(Min, transformed);
				Max = glm::max(Max, transformed);
			}
		}

		void PopulateCorners(std::vector<glm::vec3>& corners) const
		{
			corners.resize(8);
			corners[0] = Min;
			corners[1] = glm::vec3(Min.x, Min.y, Max.z);
			corners[2] = glm::vec3(Min.x, Max.y, Min.z);
			corners[3] = glm::vec3(Max.x, Min.y, Min.z);
			corners[4] = glm::vec3(Min.x, Max.y, Max.z);
			corners[5] = glm::vec3(Max.x, Min.y, Max.z);
			corners[6] = glm::vec3(Max.x, Max.y, Min.z);
			corners[7] = Max;
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
		World() = default;
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
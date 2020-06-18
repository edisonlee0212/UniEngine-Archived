#pragma once
#include "EntitiesAPI.h"
#include "SystemBase.h"
#include "WorldTime.h"
#include "Entity.h"
namespace UniEngine {
	namespace Entities {
		class ENTITIES_API World
		{
			WorldTime* _Time;
			std::vector<SystemBase*> _Systems;
			size_t _Index;
		public:
			void SetWorldTime(double time);
			void SetTimeStep(float timeStep);
			size_t GetIndex();
			World(size_t index);
			void Init();
			WorldTime* Time();
			template <class T>
			T* CreateSystem();
			template <class T>
			void DestroySystem();
			template <class T>
			T* GetSystem();
			~World();
			void Update();
		};

		template <class T>
		T* World::CreateSystem() {
			T* system = GetSystem<T>();
			if (system != nullptr) {
				return system;
			}
			system = new T();
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
}
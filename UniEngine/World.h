#pragma once
#include "Misc.h"
#include "Core.h"

namespace UniEngine {
	class World
	{
		std::vector<SystemBase*> _Systems;
		double _TimeStep;
		
	public:
		World();
		template <class T>
		T* CreateSystem();
		template <class T>
		void DestroySystem();
		template <class T>
		T* GetSystem();
		~World();
		void Update();
		EntityManager* Entities;
	};
}

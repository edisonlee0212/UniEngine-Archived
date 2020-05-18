#pragma once
#include "Misc.h"
#include "SystemBase.h"

namespace UniEngine {
	class World
	{
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
		//static EntityManager* Entities;
		//static Camera* MainCamera;
	private:
		std::vector<SystemBase*> _Systems;
	};
}

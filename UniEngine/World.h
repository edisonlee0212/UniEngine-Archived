#pragma once
#include "Misc.h"
#include "Core.h"
#include "Camera.h"
namespace UniEngine {
	class World
	{
		std::vector<SystemBase*> _Systems;
		double _TimeStep;
		static Camera* _MainCamera;
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
		static Camera* MainCamera();
	};
}

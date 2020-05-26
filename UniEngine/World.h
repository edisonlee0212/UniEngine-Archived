#pragma once
#include "Misc.h"
#include "EntityCollection.h"
#include "SystemBase.h"
#include "Camera.h"
namespace UniEngine {
	class World
	{
		std::vector<SystemBase*> _Systems;
		double _TimeStep;
		Camera* _MainCamera;
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
		EntityCollection* _EntityCollection;
		Camera* MainCamera();
	};
}

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
		EntityCollection* _EntityCollection;
		Camera* MainCamera();
	};
}

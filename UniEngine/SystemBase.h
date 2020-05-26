#pragma once
#include "Core.h"
#include "EntityManager.h"
namespace UniEngine {
	class SystemBase
	{
	protected:
		friend class World;
		bool _Enabled;
		EntityManager* _Entities;
		void SetEntityManager(EntityManager* entityManager);
		void Enable();
		void Disable();
	public:
		bool Enabled();
		EntityManager* Entities();
		SystemBase();
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnStartRunning() {}
		virtual void OnStopRuning() {}
		virtual void Update() {};
		virtual void FixedUpdate() {};
	};
}


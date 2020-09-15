#pragma once
#include "EntitiesAPI.h"
#include "Entity.h"
namespace UniEngine {
	class World;
	class WorldTime;
	class ENTITIES_API SystemBase
	{
	protected:
		friend class World;
		bool _Enabled;
		WorldTime* _Time;
		World* _World;
		ThreadPool* _ThreadPool;
		virtual void OnStartRunning() {}
		virtual void OnStopRuning() {}
		SystemBase();
	public:
		void Enable();
		void Disable();
		bool Enabled();

		virtual void OnCreate() {};
		virtual void OnDestroy() {};
		virtual void Update() {};
		virtual void FixedUpdate() {};
	};
}
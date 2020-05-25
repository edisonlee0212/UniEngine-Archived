#pragma once
#include "EntityCollection.h"
namespace UniEngine {
	class World;
	class SystemBase
	{
	protected:
		friend class World;
		bool _Enabled;
		World* _World;
		EntityCollection* _EntityCollection;
		void Enable();
		void Disable();
	public:
		bool Enabled();
		SystemBase();
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnStartRunning() {}
		virtual void OnStopRuning() {}
		virtual void Update() {};
		virtual void FixedUpdate() {};
	};
}


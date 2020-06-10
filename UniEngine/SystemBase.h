#pragma once
namespace UniEngine {
	class World;
	class EntityCollection;
	class Time;
	class SystemBase
	{
	protected:
		friend class World;
		bool _Enabled;
		Time* _Time;
		World* _World;
		EntityCollection* _EntityCollection;
		virtual void OnStartRunning() {}
		virtual void OnStopRuning() {}
		SystemBase();
	public:
		void Enable();
		void Disable();
		bool Enabled();
		
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void Update() {};
		virtual void FixedUpdate() {};
	};
}


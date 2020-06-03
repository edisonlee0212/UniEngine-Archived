#pragma once
#include "Misc.h"
#include "Core.h"
#include "World.h"
namespace UniEngine {
	class EngineDriver {
		World* _World;
		bool _Loopable;
	public:
		EngineDriver();
		void GLInit();
		void Start();
		bool Loop();
		void End();
		World* GetWorld();
	};
}
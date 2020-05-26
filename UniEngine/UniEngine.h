#pragma once
#include "Misc.h"
#include "Core.h"
#include "World.h"
namespace UniEngine {
	class EngineDriver {
		World* _World;
		bool _Looping;
	public:
		EngineDriver();
		void GLInit();
		void Start();
		void Loop();
		void End();
		World* GetWorld();
	};
}
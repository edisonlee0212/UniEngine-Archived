#pragma once
#include "Misc.h"
#include "Core.h"
#include "World.h"
namespace UniEngine {
	class EngineDriver {
	public:
		EngineDriver();
		void GLInit();
		void Start();
		void End();
	private:
		World* world;
		bool _Looping;
		void Loop();
	};
}
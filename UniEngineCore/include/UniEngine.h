#pragma once
#include "Misc.h"
#include "Core.h"
#include "World.h"
#include "RenderManager.h"
#include "ModelManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "LightingManager.h"
#include "Default.h"
namespace UniEngine {
	class EngineDriver {
		World* _World;
		bool _Loopable;
	public:
		EngineDriver();
		void GLInit();
		void Start();
		bool LoopStart();
		bool Loop();
		bool LoopEnd();
		void End();
		World* GetWorld();
	};
}
#pragma once
#include "RenderManager.h"
#include "ModelManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "LightingManager.h"
namespace UniEngine {
	class UNIENGINE_API Engine {
		World* _World;
		bool _Loopable;
		double _RealWorldTime;
		float _TimeStep;
		void DrawInfoWindow();
	public:
		Engine();
		void GLInit();
		void Start();
		bool LoopStart();
		bool Loop();
		bool LoopEnd();
		void End();
		World* GetWorld();
		
	};
}
#pragma once
#include "RenderManager.h"
#include "ModelManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "LightingManager.h"
namespace UniEngine {
	class UNIENGINE_API Engine {
		World* _World;
		Entity _MainCamera;
		bool _Loopable;
		double _RealWorldTime;
		float _TimeStep;
		void DrawInfoWindow();
	public:
		Engine();
		void GLInit();
		void Start(GLFWwindow* targetWindow, unsigned width, unsigned height);
		bool LoopStart();
		bool Loop();
		bool LoopEnd();
		void End();
		World* GetWorld();
		void SetMainCamera(Entity entity);
	};
}
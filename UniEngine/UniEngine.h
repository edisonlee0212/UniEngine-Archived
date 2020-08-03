#pragma once
#include "RenderManager.h"
#include "ModelManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "LightingManager.h"
namespace UniEngine {
	class UNIENGINE_API Engine {
		static World* _World;
		static Entity _MainCameraEntity;
		static CameraComponent* _MainCameraComponent;
		static bool _Loopable;
		static double _RealWorldTime;
		static float _TimeStep;
		static bool _Running;
		static ThreadPool _ThreadPool;
		static void GLInit();
		static void LoopStart_Internal();
		static void LoopMain_Internal();
		static bool LoopEnd_Internal();
	public:
		static void Init(bool fullScreen = false);
		static void PreUpdate();
		static void Update();
		static bool LateUpdate();
		static void End();
		static void Run();
		static World* GetWorld();
		static Entity GetMainCameraEntity();
		static CameraComponent* GetMainCameraComponent();
	};
}
#pragma once
#include "RenderManager.h"
#include "ModelManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "LightingManager.h"
namespace UniEngine {
	class UNIENGINE_API Engine {
		World* _World;
		Entity _MainCameraEntity;
		CameraComponent* _MainCameraComponent;
		bool _Loopable;
		double _RealWorldTime;
		float _TimeStep;
		ThreadPool _ThreadPool;
	public:
		Engine(bool fullScreen = false);
		void GLInit();
		void Start();
		void LoopStart();
		void Loop();
		bool LoopEnd();
		void End();
		World* GetWorld();
		Entity GetMainCameraEntity();
		CameraComponent* GetMainCameraComponent();
		void SetMainCamera(Entity entity, CameraComponent* cc);
	};
}
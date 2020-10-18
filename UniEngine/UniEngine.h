#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderManager.h"
#include "ModelManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "RenderSystem.h"
#include "TransformSystem.h"
#include "PhysicsSystem.h"
#include "EntityEditorSystem.h"
namespace UniEngine {
	class UNIENGINE_API Application {
		static std::shared_ptr<Cubemap> _Skybox;
		static std::shared_ptr<World> _World;
		static Entity _MainCameraEntity;
		static std::shared_ptr<CameraComponent> _MainCameraComponent;
		static bool _Loopable;
		static double _RealWorldTime;
		static float _TimeStep;
		static bool _Running;
		static bool _DrawSkybox;
		static bool _DisplayLog;
		static bool _DisplayError;
		static ThreadPool _ThreadPool;
		static void GLInit();
		static void LoopStart_Internal();
		static void LoopMain_Internal();
		static bool LoopEnd_Internal();
	public:
		static void ResetSkybox(std::shared_ptr<Cubemap> cubemap);
		static void SetEnableSkybox(bool value);
		static void SetTimeStep(float value);
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
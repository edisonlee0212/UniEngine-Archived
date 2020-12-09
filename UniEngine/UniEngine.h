#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "TransformManager.h"
#include "PhysicsSimulationManager.h"
#include "EditorManager.h"
namespace UniEngine {
	class UNIENGINE_API Application {
		friend class EntityManager;
		friend class EditorManager;
		static std::shared_ptr<World> _World;
		static bool _Initialized;
		static float _TimeStep;
		static bool _InnerLooping;
		static bool _Playing;
		static ThreadPool _ThreadPool;
		static void PreUpdateInternal();
		static void UpdateInternal();
		static bool LaterUpdateInternal();
	public:
		static double EngineTime();
		static void SetPlaying(bool value);
		static bool IsPlaying();
		//You are only allowed to create entity after this.
		static bool IsInitialized();
		static void SetTimeStep(float value);
		static void Init(bool fullScreen = false);
		static void PreUpdate();
		static void Update();
		static bool LateUpdate();
		static void End();
		static void Run();
		static std::shared_ptr<World>& GetWorld();
	};
}
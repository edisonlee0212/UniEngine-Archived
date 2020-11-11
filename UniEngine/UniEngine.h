#pragma once
#include "FileBrowser.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "TransformSystem.h"
#include "PhysicsSimulationManager.h"
#include "EditorManager.h"
namespace UniEngine {
	class UNIENGINE_API Application {
		friend class EntityManager;
		static std::shared_ptr<World> _World;
		static bool _Initialized;
		static double _RealWorldTime;
		static float _TimeStep;
		static bool _Running;
		
		static ThreadPool _ThreadPool;
		static void GLInit();
		static void LoopStart_Internal();
		static void LoopMain_Internal();
		static bool LoopEnd_Internal();
	public:
		static double EngineTime();
		
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
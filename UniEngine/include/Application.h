#pragma once

#include "Core.h"
namespace UniEngine {
	class UNIENGINE_API Application {
		friend class EntityManager;
		friend class EditorManager;
		static std::unique_ptr<World> _World;
		static bool _Initialized;
		static float _TimeStep;
		static bool _InnerLooping;
		static bool _Playing;
		
		static std::vector<std::function<void()>> _ExternalPreUpdateFunctions;
		static std::vector<std::function<void()>> _ExternalUpdateFunctions;
		static std::vector<std::function<void()>> _ExternalLateUpdateFunctions;

		static void PreUpdateInternal();
		static void UpdateInternal();
		static bool LateUpdateInternal();
	public:
		static double EngineTime();
		static void SetPlaying(bool value);
		static bool IsPlaying();
		//You are only allowed to create entity after this.
		static bool IsInitialized();
		static void SetTimeStep(float value);
		static void Init(bool fullScreen = false);
		static void End();
		static void Run();
		static std::unique_ptr<World>& GetCurrentWorld();
		
		static void RegisterPreUpdateFunction(const std::function<void()>& func);
		static void RegisterUpdateFunction(const std::function<void()>& func);
		static void RegisterLateUpdateFunction(const std::function<void()>& func);
	};
}
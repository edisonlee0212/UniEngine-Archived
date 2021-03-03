#pragma once
#include "Core.h"
namespace UniEngine {
	class UNIENGINE_API Application {
		friend class EntityManager;
		friend class EditorManager;
		static std::unique_ptr<World> m_world;
		static bool m_initialized;
		static float m_timeStep;
		static bool m_innerLooping;
		static bool m_playing;
		
		static std::vector<std::function<void()>> m_externalPreUpdateFunctions;
		static std::vector<std::function<void()>> m_externalUpdateFunctions;
		static std::vector<std::function<void()>> m_externalLateUpdateFunctions;

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
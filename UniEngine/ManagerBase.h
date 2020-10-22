#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class ThreadPool;
	class World;
	class UNIENGINE_API ManagerBase
	{
	protected:
		friend class Application;
		static World* _World;
		static ThreadPool* _ThreadPool;
		static void SetWorld(World* world) { _World = world; }
	public:
		ManagerBase(ManagerBase& other) = delete;
		void operator=(const ManagerBase&) = delete;
		ManagerBase() = delete;
		~ManagerBase() = delete;
	};
}

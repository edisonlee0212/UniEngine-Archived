#pragma once
#include "EntitiesAPI.h"
namespace UniEngine {
	class World;
	class ENTITIES_API ManagerBase
	{
	protected:
		friend class World;
		static World* _World;
		static ThreadPool* _ThreadPool;
	public:
		ManagerBase(ManagerBase& other) = delete;
		void operator=(const ManagerBase&) = delete;
		ManagerBase() = delete;
	};
}

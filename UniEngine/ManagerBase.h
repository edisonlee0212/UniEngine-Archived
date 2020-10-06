#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class World;
	class UNIENGINE_API ManagerBase
	{
	protected:
		friend class World;
		static World* _World;
	public:
		ManagerBase(ManagerBase& other) = delete;
		void operator=(const ManagerBase&) = delete;
		ManagerBase() = delete;
	};
}

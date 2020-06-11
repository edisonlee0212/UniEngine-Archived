#pragma once
#include "Misc.h"
namespace UniEngine {
	class World;
	class EntityCollection;
	class UECORE_API ManagerBase
	{
	protected:
		friend class World;
		static World* _World;
		static EntityCollection* _EntityCollection;
	};
}

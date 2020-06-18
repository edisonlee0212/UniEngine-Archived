#pragma once
#include "EntitiesAPI.h"
namespace UniEngine {
	namespace Entities {
		class World;
		class ENTITIES_API ManagerBase
		{
		protected:
			friend class World;
			static World* _World;
		};
	}
}

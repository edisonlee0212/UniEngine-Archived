#pragma once
#include "World.h"
#include "EntityCollection.h"
namespace UniEngine {
	class ManagerBase
	{
	protected:
		friend class World;
		static World* _World;
		static EntityCollection* _EntityCollection;
	};
}

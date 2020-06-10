#pragma once
namespace UniEngine {
	class World;
	class EntityCollection;
	class ManagerBase
	{
	protected:
		friend class World;
		static World* _World;
		static EntityCollection* _EntityCollection;
	};
}

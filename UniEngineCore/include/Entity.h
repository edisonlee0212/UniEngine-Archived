#pragma once
#include "Misc.h"
#include "FixedData.h"
#include "ComponentBase.h"
#include "SharedComponentBase.h"
namespace UniEngine {
	class Entity
	{
		unsigned _Key;
		Entity* _Parent;
		std::vector<Entity*> _Children;
		friend class EntityCollection;
		Entity(unsigned key);
		void RemoveChild(Entity* child);
		~Entity();
	public:
		Entity* Parent();
		std::vector<Entity*>* Children();
		unsigned Key();
	};

}
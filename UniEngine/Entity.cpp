#include "pch.h"
#include "Entity.h"

#include <utility>
#include "EntityManager.h"
using namespace UniEngine;
inline bool UniEngine::Entity::Enabled() const
{
	return EntityManager::IsEntityEnabled(*this);
}

inline void UniEngine::Entity::SetEnabled(bool value) const
{
	EntityManager::SetEnable(*this, value);
}

bool UniEngine::Entity::IsDeleted() const
{
	return EntityManager::IsEntityDeleted(Index);
}

bool Entity::IsValid() const
{
	return !IsNull() && !IsDeleted();
}

inline std::string Entity::GetName() const
{
	return EntityManager::GetEntityName(*this);
}

inline void Entity::SetName(std::string name) const
{
	return EntityManager::SetEntityName(*this, std::move(name));
}

bool EntityArchetypeInfo::HasType(size_t typeID)
{
	for (const auto& type : ComponentTypes)
	{
		if (typeID == type.TypeID) return true;
	}
	return false;
}

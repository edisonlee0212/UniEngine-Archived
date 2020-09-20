#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"
using namespace UniEngine;
inline bool UniEngine::Entity::Enabled() {
	return EntityManager::IsEntityEnabled(*this);
}

inline void UniEngine::Entity::SetEnabled(bool value) {
	EntityManager::SetEnable(*this, value);
}

bool UniEngine::Entity::IsDeleted()
{
	return EntityManager::IsEntityDeleted(Index);
}

inline std::string Entity::GetName()
{
	return EntityManager::GetEntityName(*this);
}

inline bool Entity::SetName(std::string name)
{
	return EntityManager::SetEntityName(*this, name);
}

bool EntityArchetypeInfo::HasType(size_t typeID)
{
	for (const auto& type : ComponentTypes)
	{
		if (typeID == type.TypeID) return true;
	}
	return false;
}

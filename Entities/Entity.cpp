#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"
using namespace UniEngine;

inline bool Entity::Enabled()
{
	return EntityManager::IsEntityEnabled(*this);
}

inline void Entity::SetEnabled(bool value)
{
	EntityManager::SetEnable(*this, value);
}

bool Entity::IsDeleted()
{
	return EntityManager::IsEntityDeleted(Index);
}

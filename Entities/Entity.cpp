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

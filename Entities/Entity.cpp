#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"
using namespace UniEngine;
inline bool UniEngine::Entity::Enabled() {
	return EntityManager::IsEntityEnabled(*this);
}

inline bool UniEngine::Entity::SetEnabled(bool value) {
	EntityManager::SetEnable(*this, value);
}
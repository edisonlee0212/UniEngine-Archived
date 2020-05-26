#include "Entity.h"
#include "Math.h"
using namespace UniEngine;
UniEngine::Entity::Entity(uint key) : _Key(key)
{
	_Parent = nullptr;
	_SharedComponents = new std::unordered_map<std::size_t, SharedComponent*>();
}
UniEngine::Entity::~Entity()
{
	delete _SharedComponents;
}
void UniEngine::Entity::SetParent(Entity* parent)
{
	_Parent = parent;
}

uint UniEngine::Entity::Key()
{
	return _Key;
}

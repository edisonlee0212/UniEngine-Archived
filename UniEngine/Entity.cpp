#include "Entity.h"

using namespace UniEngine;
UniEngine::Entity::Entity(unsigned key) : _Key(key)
{
	_Parent = nullptr;
	_Children = std::vector<Entity*>();
	_SharedComponents = new std::unordered_map<std::size_t, SharedComponent*>();
}
void UniEngine::Entity::RemoveChild(Entity* child)
{
	for (auto i = 0; i < _Children.size(); i++) {
		if (child == _Children[i]) _Children.erase(_Children.begin() + i);
	}
}
UniEngine::Entity::~Entity()
{
	delete _SharedComponents;
}

Entity* UniEngine::Entity::Parent()
{
	return _Parent;
}

std::vector<Entity*>* UniEngine::Entity::Children()
{
	return &_Children;
}

unsigned UniEngine::Entity::Key()
{
	return _Key;
}

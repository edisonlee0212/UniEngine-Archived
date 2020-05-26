#include "EntityCollection.h"
#include "Entity.h"
using namespace UniEngine;
UniEngine::EntityCollection::EntityCollection()
{
	_Entities = std::vector<Entity*>();
	_FixedDataStorage = new FixedDataStorage();
}

void UniEngine::EntityCollection::SetParent(Entity* child, Entity* parent)
{
	if (child->_Parent != nullptr) {
		//unbind parent.
		child->_Parent->RemoveChild(child);
		child->_Parent = nullptr;
	}
	if (parent != nullptr) {
		parent->_Children.push_back(child);
		child->_Parent = parent;
	}
}

std::vector<Entity*>* UniEngine::EntityCollection::Entities()
{
	return &_Entities;
}

Entity* UniEngine::EntityCollection::CreateEntity()
{
	Entity* retVal = new Entity(_Entities.size());
	_Entities.push_back(retVal);
	_FixedDataStorage->PushBack();
	return retVal;
}

void UniEngine::EntityCollection::DeleteEntity(Entity* entity)
{
	for (auto i : entity->_Children) {
		DeleteEntity(i);
	}
	SetParent(entity, nullptr);
	int index = entity->_Key;
	if(index == _Entities.size() - 1)_Entities.pop_back();
	else {
		_Entities.at(index) = _Entities.back();
		_Entities.pop_back();
		_Entities.at(index)->_Key = index;
	}
	_FixedDataStorage->RemoveSwapBack(index);

	delete entity;
}

void UniEngine::EntityCollection::DeleteEntity(unsigned key)
{
	Entity* entity = _Entities.at(key);
	for (auto i : entity->_Children) {
		DeleteEntity(i);
	}
	SetParent(entity, nullptr);
	_Entities.at(key) = _Entities.back();
	_Entities.pop_back();
	_Entities.at(key)->_Key = key;
	_FixedDataStorage->RemoveSwapBack(key);
	delete entity;
}

Entity* UniEngine::EntityCollection::GetEntity(unsigned key)
{
	return _Entities.at(key);
}

size_t UniEngine::EntityCollection::GetEntitiesAmount()
{
	return _Entities.size();
}

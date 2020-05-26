#include "EntityManager.h"
#include "Entity.h"
using namespace UniEngine;
UniEngine::EntityManager::EntityManager()
{
	_Entities = std::vector<Entity*>();
	_FixedDataStorage = new FixedDataStorage();
}

std::vector<Entity*>* UniEngine::EntityManager::Entities()
{
	return &_Entities;
}

Entity* UniEngine::EntityManager::CreateEntity()
{
	Entity* retVal = new Entity(_Entities.size());
	_Entities.push_back(retVal);
	_FixedDataStorage->PushBack();
	return retVal;
}

void UniEngine::EntityManager::DeleteEntity(Entity* entity)
{
	int index = entity->_Key;
	_Entities.at(index) = _Entities.back();
	_Entities.pop_back();
	_Entities.at(index)->_Key = index;
	_FixedDataStorage->RemoveSwapBack(index);
	delete entity;
}

void UniEngine::EntityManager::DeleteEntity(uint key)
{
	Entity* entity = _Entities.at(key);
	_Entities.at(key) = _Entities.back();
	_Entities.pop_back();
	_Entities.at(key)->_Key = key;
	_FixedDataStorage->RemoveSwapBack(key);
	delete entity;
}

Entity* UniEngine::EntityManager::GetEntity(uint key)
{
	return _Entities.at(key);
}

size_t UniEngine::EntityManager::GetEntitiesAmount()
{
	return _Entities.size();
}

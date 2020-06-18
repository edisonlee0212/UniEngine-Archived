#include "pch.h"
#include "EntityManager.h"
using namespace UniEngine::Entities;


std::vector<WorldEntityStorage*> UniEngine::Entities::EntityManager::_WorldEntityStorage;
std::vector<EntityInfo>* UniEngine::Entities::EntityManager::_Entities;
std::vector<EntityComponentStorage>* UniEngine::Entities::EntityManager::_EntityComponentStorage;
std::vector<std::queue<Entity>>* UniEngine::Entities::EntityManager::_EntityPool;
SharedComponentStorage* UniEngine::Entities::EntityManager::_EntitySharedComponentStorage;

#pragma region EntityManager

std::vector<EntityInfo>* UniEngine::Entities::EntityManager::GetAllEntities() {
	return _Entities;
}

void UniEngine::Entities::EntityManager::SetWorld(World* world)
{
	size_t index = world->GetIndex();
	while (index >= _WorldEntityStorage.size()) {
		_WorldEntityStorage.push_back(new WorldEntityStorage());
	}
	WorldEntityStorage* targetStorage = _WorldEntityStorage[index];
	_Entities = &targetStorage->Entities;
	_EntityComponentStorage = &targetStorage->EntityComponentStorage;
	_EntityPool = &targetStorage->EntityPool;
	_EntitySharedComponentStorage = &targetStorage->EntitySharedComponentStorage;
}

Entity UniEngine::Entities::EntityManager::CreateEntity(EntityArchetype archetype)
{
	Entity retVal;
	if (_EntityPool->at(archetype.Index).empty()) {
		EntityComponentStorage storage = _EntityComponentStorage->at(archetype.Index);
		EntityArchetypeInfo* info = storage.ArchetypeInfo;
		unsigned chunkIndex = info->EntityCount / info->ChunkCapacity;
		unsigned chunkPointer = info->EntityCount % info->ChunkCapacity;
		if (storage.ChunkArray->Chunks.size() <= chunkIndex) {
			//Allocate new chunk;
			ComponentDataChunk chunk;
			chunk.Data = (void*)malloc(ARCHETYPECHUNK_SIZE);
			storage.ChunkArray->Chunks.push_back(chunk);
		}
		retVal.Index = _Entities->size();
		//If the version is 0 in chunk means it's deleted.
		retVal.Version = 1;
		EntityInfo entityInfo;
		entityInfo.ArchetypeInfoIndex = archetype.Index;
		entityInfo.ChunkArrayIndex = info->EntityCount;
		entityInfo.Entity = retVal;
		storage.ChunkArray->Entities.push_back(retVal);
		_Entities->push_back(entityInfo);
		info->EntityCount++;
	}
	else {
		//TODO: Update version when we delete entity.
		retVal = _EntityPool->at(archetype.Index).front();
		_EntityPool->at(archetype.Index).pop();
		EntityInfo entityInfo = _Entities->at(retVal.Index);
		EntityComponentStorage storage = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		entityInfo.Entity = retVal;
		_Entities->at(retVal.Index) = entityInfo;
	}
	return retVal;
}

void UniEngine::Entities::EntityManager::DeleteEntity(Entity entity)
{
	EntityInfo info = _Entities->at(entity.Index);
	if (info.Entity == entity) {
		_EntitySharedComponentStorage->DeleteEntity(info.Entity);
		info.Entity.Version++;
		_EntityPool->at(info.ArchetypeInfoIndex).push(info.Entity);
		//Set to version 0, marks it as deleted.
		info.Entity.Version = 0;
		EntityComponentStorage storage = _EntityComponentStorage->at(info.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[info.ChunkArrayIndex] = info.Entity;
	}
	else {
		Debug::Error("Entity already deleted!");
		return;
	}
	_Entities->at(entity.Index) = info;
}

EntityArchetype UniEngine::Entities::EntityManager::GetEntityArchetype(Entity entity)
{
	EntityInfo info = _Entities->at(entity.Index);
	EntityArchetype retVal;
	retVal.Index = info.ArchetypeInfoIndex;
	return retVal;
}

UniEngine::Entities::EntityComponentStorage::EntityComponentStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array)
{
	ArchetypeInfo = info;
	ChunkArray = array;
}

#pragma endregion

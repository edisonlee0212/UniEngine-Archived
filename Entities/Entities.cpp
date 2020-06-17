#include "pch.h"
#include "Entities.h"

using namespace UniEngine::Entities;

std::vector<EntityComponentStorage*> UniEngine::Entities::EntityManager::_EntityComponentStorage;
std::vector<EntityInfo>* UniEngine::Entities::EntityManager::_Entities;
std::vector<EntityArchetypeStorage>* UniEngine::Entities::EntityManager::_EntityArchetypes;
std::vector<std::queue<Entity>>* UniEngine::Entities::EntityManager::_EntityPool;

void UniEngine::Entities::EntityManager::SetWorld(UniEngine::World* world)
{
	_World = world;
	size_t index = world->GetIndex();
	while (index >= _EntityComponentStorage.size()) {
		_EntityComponentStorage.push_back(new EntityComponentStorage());
	}
	EntityComponentStorage* targetStorage = _EntityComponentStorage[index];
	_Entities = &targetStorage->Entities;
	_EntityArchetypes = &targetStorage->EntityArchetypes;
	_EntityPool = &targetStorage->EntityPool;
}

Entity UniEngine::Entities::EntityManager::CreateEntity(EntityArchetype archetype)
{
	Entity retVal;
	if (_EntityPool[archetype.Index].empty()) {
		EntityArchetypeStorage storage = _EntityArchetypes->at(archetype.Index);
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
		EntityInfo info = _Entities->at(retVal.Index);
		EntityArchetypeStorage storage = _EntityArchetypes->at(info.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[info.ChunkArrayIndex] = retVal;
	}
	return retVal;
}

void UniEngine::Entities::EntityManager::DeleteEntity(Entity entity)
{
	EntityInfo info = _Entities->at(entity.Index);
	if (info.Entity == entity) {
		info.Entity.Version++;
		_EntityPool->at(info.ArchetypeInfoIndex).push(info.Entity);
		//Set to version 0, marks it as deleted.
		info.Entity.Version = 0;
		EntityArchetypeStorage storage = _EntityArchetypes->at(info.ArchetypeInfoIndex);
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

UniEngine::Entities::EntityArchetypeStorage::EntityArchetypeStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array)
{
	ArchetypeInfo = info;
	ChunkArray = array;
}

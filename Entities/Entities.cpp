#include "pch.h"
#include "Entities.h"

using namespace UniEngine::Entities;

Entity UniEngine::Entities::EntityManager::CreateEntity(EntityArchetype archetype)
{
	Entity retVal;
	if (_EntityPool[archetype.Index].empty()) {
		EntityArchetypeStorage storage = _EntityArchetypes[archetype.Index];
		EntityArchetypeInfo* info = storage.first;
		unsigned chunkIndex = info->EntityCount / info->ChunkCapacity;
		unsigned chunkPointer = info->EntityCount % info->ChunkCapacity;
		if (storage.second->Chunks.size() <= chunkIndex) {
			//Allocate new chunk;
			ComponentDataChunk chunk;
			chunk.Data = (void*)malloc(ARCHETYPECHUNK_SIZE);
			storage.second->Chunks.push_back(chunk);
		}
		retVal.Index = _Entities.size();
		//If the version is 0 in chunk means it's deleted.
		retVal.Version = 1;
		EntityInfo entityInfo;
		entityInfo.ArchetypeIndex = archetype.Index;
		entityInfo.ChunkIndex = info->EntityCount;
		entityInfo.Entity = retVal;
		storage.second->Entities.push_back(retVal);
		_Entities.push_back(entityInfo);
		info->EntityCount++;
	}
	else {
		//TODO: Update version when we delete entity.
		retVal = _EntityPool[archetype.Index].front();
		_EntityPool[archetype.Index].pop();
		EntityInfo info = _Entities[retVal.Index];
		EntityArchetypeStorage storage = _EntityArchetypes[info.ArchetypeIndex];
		storage.second->Entities[info.ChunkIndex] = retVal;
	}
	return retVal;
}

void UniEngine::Entities::EntityManager::DeleteEntity(Entity entity)
{
	EntityInfo info = _Entities[entity.Index];
	if (info.Entity == entity) {
		info.Entity.Version++;
		_EntityPool[info.ArchetypeIndex].push(info.Entity);
		//Set to version 0, marks it as deleted.
		info.Entity.Version = 0;
		EntityArchetypeStorage storage = _EntityArchetypes[info.ArchetypeIndex];
		storage.second->Entities[info.ChunkIndex] = info.Entity;
	}
	else {
		Debug::Error("Entity already deleted!");
		return;
	}
	_Entities[entity.Index] = info;
}

EntityArchetype UniEngine::Entities::EntityManager::GetEntityArchetype(Entity entity)
{
	EntityInfo info = _Entities[entity.Index];
	EntityArchetype retVal;
	retVal.Index = info.ArchetypeIndex;
	return retVal;
}

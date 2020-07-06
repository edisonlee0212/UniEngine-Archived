#include "pch.h"
#include "EntityManager.h"
using namespace UniEngine::Entities;


std::vector<WorldEntityStorage*> UniEngine::Entities::EntityManager::_WorldEntityStorage;
std::vector<EntityInfo>* UniEngine::Entities::EntityManager::_EntityInfos;
std::vector<Entity>* UniEngine::Entities::EntityManager::_Entities;
std::vector<EntityComponentStorage>* UniEngine::Entities::EntityManager::_EntityComponentStorage;
std::vector<std::queue<Entity>>* UniEngine::Entities::EntityManager::_EntityPool;
SharedComponentStorage* UniEngine::Entities::EntityManager::_EntitySharedComponentStorage;
#pragma region EntityManager

void UniEngine::Entities::EntityManager::DeleteEntityInternal(Entity entity)
{
	EntityInfo info = _EntityInfos->at(entity.Index);
	Entity actualEntity = _Entities->at(entity.Index);
	if (actualEntity == entity) {
		_EntitySharedComponentStorage->DeleteEntity(actualEntity);
		actualEntity.Version++;
		_EntityPool->at(info.ArchetypeInfoIndex).push(actualEntity);
		//Set to version 0, marks it as deleted.
		actualEntity.Version = 0;
		EntityComponentStorage storage = _EntityComponentStorage->at(info.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[info.ChunkArrayIndex] = actualEntity;
	}
	else {
		Debug::Error("Entity already deleted!");
		return;
	}
	_Entities->at(entity.Index) = actualEntity;
}

void UniEngine::Entities::EntityManager::GetAllEntities(std::vector<Entity>* target) {
	target->insert(target->end() ,_Entities->begin() + 1, _Entities->end());
}

std::vector<Entity>* UniEngine::Entities::EntityManager::GetAllEntitiesUnsafe()
{
	return _Entities;
}

void UniEngine::Entities::EntityManager::SetWorld(World* world)
{
	size_t index = world->GetIndex();
	while (index >= _WorldEntityStorage.size()) {
		auto storage = new WorldEntityStorage();
		storage->Entities.push_back(Entity());
		storage->EntityInfos.push_back(EntityInfo());
		_WorldEntityStorage.push_back(storage);
	}
	WorldEntityStorage* targetStorage = _WorldEntityStorage[index];
	_Entities = &targetStorage->Entities;
	_EntityInfos = &targetStorage->EntityInfos;
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
			chunk.Data = (void*)calloc(1, ARCHETYPECHUNK_SIZE);
			storage.ChunkArray->Chunks.push_back(chunk);
		}
		retVal.Index = _Entities->size();
		//If the version is 0 in chunk means it's deleted.
		retVal.Version = 1;
		EntityInfo entityInfo;
		entityInfo.ArchetypeInfoIndex = archetype.Index;
		entityInfo.ChunkArrayIndex = info->EntityCount;
		storage.ChunkArray->Entities.push_back(retVal);
		_EntityInfos->push_back(entityInfo);
		_Entities->push_back(retVal);
		info->EntityCount++;
	}
	else {
		//TODO: Update version when we delete entity.
		retVal = _EntityPool->at(archetype.Index).front();
		_EntityPool->at(archetype.Index).pop();
		EntityInfo entityInfo = _EntityInfos->at(retVal.Index);
		EntityComponentStorage storage = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		_Entities->at(retVal.Index) = retVal;
	}
	return retVal;
}

void UniEngine::Entities::EntityManager::DeleteEntity(Entity entity)
{
	DeleteEntityInternal(entity);
	//_RelationStorage->DeleteEntity(entity);
}

void UniEngine::Entities::EntityManager::SetParent(Entity entity, Entity parent)
{
}

EntityArchetype UniEngine::Entities::EntityManager::GetEntityArchetype(Entity entity)
{
	EntityInfo info = _EntityInfos->at(entity.Index);
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

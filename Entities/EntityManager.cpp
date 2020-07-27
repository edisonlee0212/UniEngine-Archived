#include "pch.h"
#include "EntityManager.h"
using namespace UniEngine::Entities;


std::vector<WorldEntityStorage*> UniEngine::Entities::EntityManager::_WorldEntityStorage;
std::vector<EntityInfo>* UniEngine::Entities::EntityManager::_EntityInfos;
std::vector<Entity>* UniEngine::Entities::EntityManager::_Entities;
std::vector<EntityComponentStorage>* UniEngine::Entities::EntityManager::_EntityComponentStorage;
std::vector<std::queue<Entity>>* UniEngine::Entities::EntityManager::_EntityPool;
SharedComponentStorage* UniEngine::Entities::EntityManager::_EntitySharedComponentStorage;
std::vector<EntityQuery>* UniEngine::Entities::EntityManager::_EntityQueries;
std::vector<EntityQueryInfo>* UniEngine::Entities::EntityManager::_EntityQueryInfos;
std::queue<EntityQuery>* UniEngine::Entities::EntityManager::_EntityQueryPools;


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
		//TODO: Swap entity data in storage, reset entityinfo for both entity
		if (info.ChunkArrayIndex != storage.ArchetypeInfo->EntityAliveCount - 1) {
			auto swappedIndex = SwapEntity(storage, info.ChunkArrayIndex, storage.ArchetypeInfo->EntityAliveCount - 1);
			_EntityInfos->at(entity.Index).ChunkArrayIndex = storage.ArchetypeInfo->EntityAliveCount - 1;
			_EntityInfos->at(swappedIndex).ChunkArrayIndex = info.ChunkArrayIndex;
		}
		storage.ArchetypeInfo->EntityAliveCount--;
	}
	else {
		Debug::Error("Entity already deleted!");
		return;
	}
	_Entities->at(entity.Index) = actualEntity;
}

void UniEngine::Entities::EntityManager::RefreshEntityQueryInfos(size_t index)
{
	_EntityQueryInfos->at(index).QueriedStorages.clear();
	//Select storage with every contained.
	if (!_EntityQueryInfos->at(index).AllComponentTypes.empty()) {
		for (auto i : *_EntityComponentStorage) {
			if (i.ArchetypeInfo == nullptr) continue;
			bool check = true;
			for (auto type : _EntityQueryInfos->at(index).AllComponentTypes) {
				bool contain = false;
				for (auto confirm : i.ArchetypeInfo->ComponentTypes) {
					if (type.TypeID == confirm.TypeID) contain = true;
				}
				if (!contain) check = false;
			}
			if (check) _EntityQueryInfos->at(index).QueriedStorages.push_back(i);
		}
	}
	else {
		for (auto i : *_EntityComponentStorage) {
			if (i.ArchetypeInfo == nullptr) continue;
			_EntityQueryInfos->at(index).QueriedStorages.push_back(i);
		}
	}
	//Erase with any
	if (!_EntityQueryInfos->at(index).AnyComponentTypes.empty()) {
		for (int i = 0; i < _EntityQueryInfos->at(index).QueriedStorages.size(); i++) {
			bool contain = false;
			for (auto type : _EntityQueryInfos->at(index).AnyComponentTypes) {
				for (auto confirm : _EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->ComponentTypes) {
					if (confirm.TypeID == type.TypeID) {
						contain = true;
						break;
					}
				}
				if (contain) break;
			}
			if (!contain) {
				_EntityQueryInfos->at(index).QueriedStorages.erase(_EntityQueryInfos->at(index).QueriedStorages.begin() + i);
				i--;
			}
		}
	}
	//Erase with none
	if (!_EntityQueryInfos->at(index).NoneComponentTypes.empty()) {
		for (int i = 0; i < _EntityQueryInfos->at(index).QueriedStorages.size(); i++) {
			bool contain = false;
			for (auto type : _EntityQueryInfos->at(index).NoneComponentTypes) {
				for (auto confirm : _EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->ComponentTypes) {
					if (confirm.TypeID == type.TypeID) {
						contain = true;
						break;
					}
				}
				if (contain) break;
			}
			if (contain) {
				_EntityQueryInfos->at(index).QueriedStorages.erase(_EntityQueryInfos->at(index).QueriedStorages.begin() + i);
				i--;
			}
		}
	}
}

size_t UniEngine::Entities::EntityManager::SwapEntity(EntityComponentStorage storage, size_t index1, size_t index2)
{
	if (index1 == index2) return -1;
	auto info = storage.ArchetypeInfo;
	size_t retVal = storage.ChunkArray->Entities[index2].Index;
	Entity temp = storage.ChunkArray->Entities[index2];
	storage.ChunkArray->Entities[index2] = storage.ChunkArray->Entities[index1];
	storage.ChunkArray->Entities[index1] = temp;
	size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
	size_t chunkIndex1 = index1 / capacity;
	size_t chunkIndex2 = index2 / capacity;
	size_t chunkPointer1 = index1 % capacity;
	size_t chunkPointer2 = index2 % capacity;

	for (auto i : storage.ArchetypeInfo->ComponentTypes) {
		void* temp = (void*)malloc(i.Size);
		void* d1 = (void*)((char*)storage.ChunkArray->Chunks[chunkIndex1].Data
			+ i.Offset * capacity
			+ i.Size * chunkPointer1);

		void* d2 = (void*)((char*)storage.ChunkArray->Chunks[chunkIndex2].Data
			+ i.Offset * capacity
			+ i.Size * chunkPointer2);

		memcpy(temp, d1, i.Size);
		memcpy(d1, d2, i.Size);
		memcpy(d2, temp, i.Size);
		free(temp);
	}
	return retVal;
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
		storage->EntityComponentStorage.push_back(EntityComponentStorage(nullptr, nullptr));
		storage->EntityPool.push_back(std::queue<Entity>());
		storage->EntityQueries.push_back(EntityQuery());
		storage->EntityQueryInfos.push_back(EntityQueryInfo());
		_WorldEntityStorage.push_back(storage);
	}
	WorldEntityStorage* targetStorage = _WorldEntityStorage[index];
	_Entities = &targetStorage->Entities;
	_EntityInfos = &targetStorage->EntityInfos;
	_EntityComponentStorage = &targetStorage->EntityComponentStorage;
	_EntityPool = &targetStorage->EntityPool;
	_EntitySharedComponentStorage = &targetStorage->EntitySharedComponentStorage;
	_EntityQueries = &targetStorage->EntityQueries;
	_EntityQueryInfos = &targetStorage->EntityQueryInfos;
	_EntityQueryPools = &targetStorage->EntityQueryPools;
}

Entity UniEngine::Entities::EntityManager::CreateEntity(EntityArchetype archetype)
{
	if (archetype.Index == 0) return Entity();
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
		info->EntityAliveCount++;
	}
	else {
		//TODO: Update version when we delete entity.
		retVal = _EntityPool->at(archetype.Index).front();
		_EntityPool->at(archetype.Index).pop();
		EntityInfo entityInfo = _EntityInfos->at(retVal.Index);
		EntityComponentStorage storage = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		_Entities->at(retVal.Index) = retVal;
		storage.ArchetypeInfo->EntityAliveCount++;
	}
	return retVal;
}

void UniEngine::Entities::EntityManager::DeleteEntity(Entity entity)
{
	if (entity.IsNull()) return;
	size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Entity out of date!");
	}
	for (auto child : _EntityInfos->at(entityIndex).Children) {
		DeleteEntity(child);
	}
	_EntityInfos->at(entityIndex).Children.clear();
	DeleteEntityInternal(entity);
	if(_EntityInfos->at(entityIndex).Parent.Index != 0) RemoveChild(entity, _EntityInfos->at(entityIndex).Parent);
}

void UniEngine::Entities::EntityManager::SetParent(Entity entity, Entity parent)
{
	if (entity.IsNull() || parent.IsNull()) return;
	size_t childIndex = entity.Index;
	size_t parentIndex = parent.Index;
	if (entity != _Entities->at(childIndex)) {
		Debug::Error("Child already deleted!");
		return;
	}
	if (parent != _Entities->at(parentIndex)) {
		Debug::Error("Parent already deleted!");
		return;
	}
	if (_EntityInfos->at(childIndex).Parent.Index != 0) {
		RemoveChild(entity, _Entities->at(_EntityInfos->at(childIndex).Parent.Index));
	}
	_EntityInfos->at(childIndex).Parent = parent;
	_EntityInfos->at(parentIndex).Children.push_back(entity);
}

Entity UniEngine::Entities::EntityManager::GetParent(Entity entity)
{
	if (entity.IsNull()) return Entity();
	size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Entity already deleted!");
		return Entity();
	}
	return _EntityInfos->at(entityIndex).Parent;
}

std::vector<Entity> UniEngine::Entities::EntityManager::GetChildren(Entity entity)
{
	if (entity.IsNull()) return std::vector<Entity>();
	size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Parent already deleted!");
		return std::vector<Entity>();
	}
	return _EntityInfos->at(entityIndex).Children;
}

void UniEngine::Entities::EntityManager::RemoveChild(Entity entity, Entity parent)
{
	if (entity.IsNull() || parent.IsNull()) return;
	size_t childIndex = entity.Index;
	size_t parentIndex = parent.Index;

	if (entity != _Entities->at(childIndex)) {
		Debug::Error("Child already deleted!");
		return;
	}
	if (parent != _Entities->at(parentIndex)) {
		Debug::Error("Parent already deleted!");
		return;
	}
	if (_EntityInfos->at(childIndex).Parent.Index == 0) {
		Debug::Error("No child by the parent!");
	}
	_EntityInfos->at(childIndex).Parent = Entity();
	size_t childrenCount = _EntityInfos->at(parentIndex).Children.size();
	for (int i = 0; i < childrenCount; i++) {
		if (_EntityInfos->at(parentIndex).Children[i].Index == childIndex) {
			_EntityInfos->at(parentIndex).Children[i] = _EntityInfos->at(parentIndex).Children.back();
			_EntityInfos->at(parentIndex).Children.pop_back();
		}
	}
}

EntityArchetype UniEngine::Entities::EntityManager::GetEntityArchetype(Entity entity)
{
	if (entity.IsNull()) return EntityArchetype();
	EntityInfo info = _EntityInfos->at(entity.Index);
	EntityArchetype retVal;
	retVal.Index = info.ArchetypeInfoIndex;
	return retVal;
}

EntityQuery UniEngine::Entities::EntityManager::CreateEntityQuery()
{
	EntityQuery retVal;
	if (_EntityQueryPools->empty()) {
		retVal.Index = _EntityQueries->size();
		retVal.Version = 1;
		_EntityQueries->push_back(retVal);
		
		EntityQueryInfo info;
		_EntityQueryInfos->push_back(info);
		RefreshEntityQueryInfos(retVal.Index);
		return retVal;
	}
	else {
		retVal = _EntityQueryPools->front();
		_EntityQueryPools->pop();
		_EntityQueries->at(retVal.Index).Version = retVal.Version;
		RefreshEntityQueryInfos(retVal.Index);
	}
}

void UniEngine::Entities::EntityManager::DeleteEntityQuery(EntityQuery entityQuery)
{
	if (entityQuery.IsNull()) return;
	unsigned index = entityQuery.Index;
	if (_EntityQueries->at(index).IsDeleted()) {
		Debug::Error("EntityQuery already deleted!");
		return;
	}
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return;
	}
	EntityQuery toPool = _EntityQueries->at(index);
	_EntityQueryInfos->at(index).AllComponentTypes.clear();
	_EntityQueryInfos->at(index).AnyComponentTypes.clear();
	_EntityQueryInfos->at(index).NoneComponentTypes.clear();
	_EntityQueryInfos->at(index).QueriedStorages.clear();
	_EntityQueries->at(index).Version = 0;
	toPool.Version++;
	_EntityQueryPools->push(toPool);
}

std::vector<EntityComponentStorage> UniEngine::Entities::EntityManager::UnsafeQueryStorages(EntityQuery entityQuery)
{
	if (entityQuery.IsNull()) return std::vector<EntityComponentStorage>();
	unsigned index = entityQuery.Index;
	if (_EntityQueries->at(index).IsDeleted()) {
		Debug::Error("EntityQuery already deleted!");
		return std::vector<EntityComponentStorage>();
	}
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return std::vector<EntityComponentStorage>();
	}
	return _EntityQueryInfos->at(index).QueriedStorages;
}

ComponentDataChunkArray* UniEngine::Entities::EntityManager::UnsafeGetEntityComponentDataChunkArray(EntityArchetype entityArchetype)
{
	if (entityArchetype.IsNull()) return nullptr;
	return _EntityComponentStorage->at(entityArchetype.Index).ChunkArray;
}

UniEngine::Entities::EntityComponentStorage::EntityComponentStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array)
{
	ArchetypeInfo = info;
	ChunkArray = array;
}

#pragma endregion

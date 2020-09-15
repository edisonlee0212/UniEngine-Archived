#include "pch.h"
#include "EntityManager.h"
using namespace UniEngine;
std::vector<WorldEntityStorage*> UniEngine::EntityManager::_WorldEntityStorage;
WorldEntityStorage* UniEngine::EntityManager::_CurrentActivitedWorldEntityStorage;
std::vector<EntityInfo>* UniEngine::EntityManager::_EntityInfos;
std::vector<Entity>* UniEngine::EntityManager::_Entities;
std::vector<Entity>* UniEngine::EntityManager::_ParentRoots;
std::vector<EntityComponentStorage>* UniEngine::EntityManager::_EntityComponentStorage;
//std::vector<std::queue<Entity>>* UniEngine::EntityManager::_EntityPool;
SharedComponentStorage* UniEngine::EntityManager::_EntitySharedComponentStorage;
std::vector<EntityQuery>* UniEngine::EntityManager::_EntityQueries;
std::vector<EntityQueryInfo>* UniEngine::EntityManager::_EntityQueryInfos;
std::queue<EntityQuery>* UniEngine::EntityManager::_EntityQueryPools;

UniEngine::ThreadPool* UniEngine::EntityManager::_ThreadPool;
#pragma region EntityManager

void UniEngine::EntityManager::ForEachComponentUnsafe(Entity entity, const std::function<void(ComponentType type, void* data)>& func)
{
	if (entity.IsNull()) return;
	EntityInfo info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		for (const auto& i : chunkInfo->ComponentTypes) {
			func(i.second, (void*)((char*)chunk.Data + i.second.Offset * chunkInfo->ChunkCapacity + chunkPointer * i.second.Size));
		}
	}
}

void UniEngine::EntityManager::ForEachEntityStorageUnsafe(const std::function<void(int i, EntityComponentStorage storage)>& func)
{
	for (size_t i = 1; i < _EntityComponentStorage->size(); i++) {
		if (_EntityComponentStorage->at(i).ArchetypeInfo->EntityAliveCount != 0) {
			func(i, _EntityComponentStorage->at(i));
		}
	}
}

void UniEngine::EntityManager::DeleteEntityInternal(Entity entity)
{
	EntityInfo info = _EntityInfos->at(entity.Index);
	Entity actualEntity = _Entities->at(entity.Index);
	if (actualEntity == entity) {
		_EntitySharedComponentStorage->DeleteEntity(actualEntity);
		info.Version = actualEntity.Version + 1;
		//actualEntity.Version++;
		//_EntityPool->at(info.ArchetypeInfoIndex).push(actualEntity);
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

void UniEngine::EntityManager::RefreshEntityQueryInfos(size_t index)
{
	_EntityQueryInfos->at(index).QueriedStorages.clear();
	//Select storage with every contained.
	if (!_EntityQueryInfos->at(index).AllComponentTypes.empty()) {
		for (auto i : *_EntityComponentStorage) {
			if (i.ArchetypeInfo == nullptr) continue;
			bool check = true;
			for (const auto& type : _EntityQueryInfos->at(index).AllComponentTypes) {
				auto search = i.ArchetypeInfo->ComponentTypes.find(type.TypeID);
				if (search == i.ArchetypeInfo->ComponentTypes.end()) check = false;
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
			for (const auto& type : _EntityQueryInfos->at(index).AnyComponentTypes) {
				auto search = _EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->ComponentTypes.find(type.TypeID);
				if (search != _EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->ComponentTypes.end()) contain = true;
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
			for (const auto& type : _EntityQueryInfos->at(index).NoneComponentTypes) {
				auto search = _EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->ComponentTypes.find(type.TypeID);
				if (search != _EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->ComponentTypes.end()) contain = true;
				if (contain) break;
			}
			if (contain) {
				_EntityQueryInfos->at(index).QueriedStorages.erase(_EntityQueryInfos->at(index).QueriedStorages.begin() + i);
				i--;
			}
		}
	}
}

void UniEngine::EntityManager::GetEntityStorage(EntityComponentStorage storage, std::vector<Entity>* container)
{
	size_t amount = storage.ArchetypeInfo->EntityAliveCount;
	if (amount == 0) return;
	container->resize(container->size() + amount);
	size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
	size_t chunkAmount = amount / capacity;
	size_t remainAmount = amount % capacity;
	memcpy(&container->at(container->size() - amount), storage.ChunkArray->Entities.data(), amount * sizeof(Entity));
}

size_t UniEngine::EntityManager::SwapEntity(EntityComponentStorage storage, size_t index1, size_t index2)
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
		void* temp = (void*)malloc(i.second.Size);
		void* d1 = (void*)((char*)storage.ChunkArray->Chunks[chunkIndex1].Data
			+ i.second.Offset * capacity
			+ i.second.Size * chunkPointer1);

		void* d2 = (void*)((char*)storage.ChunkArray->Chunks[chunkIndex2].Data
			+ i.second.Offset * capacity
			+ i.second.Size * chunkPointer2);

		memcpy(temp, d1, i.second.Size);
		memcpy(d1, d2, i.second.Size);
		memcpy(d2, temp, i.second.Size);
		free(temp);
	}
	return retVal;
}

std::vector<Entity>* UniEngine::EntityManager::GetParentRootsUnsafe()
{
	return _ParentRoots;
}

void UniEngine::EntityManager::Init(ThreadPool* threadPool)
{
	SetThreadPool(threadPool);
}

void UniEngine::EntityManager::GetAllEntities(std::vector<Entity>* target) {
	target->insert(target->end() ,_Entities->begin() + 1, _Entities->end());
}

std::vector<Entity>* UniEngine::EntityManager::GetAllEntitiesUnsafe()
{
	return _Entities;
}

void UniEngine::EntityManager::SetThreadPool(ThreadPool* pool)
{
	_ThreadPool = pool;
}

void UniEngine::EntityManager::SetWorld(World* world)
{
	size_t index = world->GetIndex();
	while (index >= _WorldEntityStorage.size()) {
		auto storage = new WorldEntityStorage();
		storage->Entities.push_back(Entity());
		storage->EntityInfos.push_back(EntityInfo());
		storage->EntityComponentStorage.push_back(EntityComponentStorage(nullptr, nullptr));
		//storage->EntityPool.push_back(std::queue<Entity>());
		storage->EntityQueries.push_back(EntityQuery());
		storage->EntityQueryInfos.push_back(EntityQueryInfo());
		_WorldEntityStorage.push_back(storage);
	}
	WorldEntityStorage* targetStorage = _WorldEntityStorage[index];
	_CurrentActivitedWorldEntityStorage = targetStorage;
	_Entities = &targetStorage->Entities;
	_ParentRoots = &targetStorage->ParentRoots;
	_EntityInfos = &targetStorage->EntityInfos;
	_EntityComponentStorage = &targetStorage->EntityComponentStorage;
	//_EntityPool = &targetStorage->EntityPool;
	_EntitySharedComponentStorage = &targetStorage->EntitySharedComponentStorage;
	_EntityQueries = &targetStorage->EntityQueries;
	_EntityQueryInfos = &targetStorage->EntityQueryInfos;
	_EntityQueryPools = &targetStorage->EntityQueryPools;

	
}

Entity UniEngine::EntityManager::CreateEntity(EntityArchetype archetype)
{
	if (archetype.Index == 0) return Entity();
	Entity retVal;
	EntityComponentStorage storage = _EntityComponentStorage->at(archetype.Index);
	EntityArchetypeInfo* info = storage.ArchetypeInfo;
	if (info->EntityCount == info->EntityAliveCount) {
		size_t chunkIndex = info->EntityCount / info->ChunkCapacity;
		size_t chunkPointer = info->EntityCount % info->ChunkCapacity;
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
		entityInfo.Version = 1;
		entityInfo.Parent = Entity();
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
		retVal = storage.ChunkArray->Entities.at(info->EntityAliveCount);
		EntityInfo entityInfo = _EntityInfos->at(retVal.Index);
		retVal.Version = entityInfo.Version;
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		_Entities->at(retVal.Index) = retVal;
		storage.ArchetypeInfo->EntityAliveCount++;
		//Reset all component data
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ArchetypeInfo;
		size_t chunkIndex = entityInfo.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		size_t chunkPointer = entityInfo.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		ComponentDataChunk chunk = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		size_t offset = 0;
		bool found = false;
		for (const auto& i : chunkInfo->ComponentTypes) {
			offset = i.second.Offset * chunkInfo->ChunkCapacity + chunkPointer * i.second.Size;
			chunk.ClearData(offset, i.second.Size);
		}
		/*
		retVal = _EntityPool->at(archetype.Index).front();
		_EntityPool->at(archetype.Index).pop();
		EntityInfo entityInfo = _EntityInfos->at(retVal.Index);
		EntityComponentStorage storage = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		_Entities->at(retVal.Index) = retVal;
		storage.ArchetypeInfo->EntityAliveCount++;
		*/
	}
	return retVal;
}

void UniEngine::EntityManager::DeleteEntity(Entity entity)
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
	if (_EntityInfos->at(entityIndex).Parent.Index == 0) {
		for (int i = 0; i < _ParentRoots->size(); i++) {
			if (_Entities->at(entityIndex) == _ParentRoots->at(i)) {
				_ParentRoots->erase(_ParentRoots->begin() + i);
			}
		}
	}
	if(_EntityInfos->at(entityIndex).Parent.Index != 0) RemoveChild(entity, _EntityInfos->at(entityIndex).Parent);
	DeleteEntityInternal(entity);

	_CurrentActivitedWorldEntityStorage->ParentHierarchyVersion++;
}

void UniEngine::EntityManager::SetParent(Entity entity, Entity parent)
{
	if (entity.IsNull() || parent.IsNull()) return;
	_CurrentActivitedWorldEntityStorage->ParentHierarchyVersion++;
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
	_EntityInfos->at(childIndex).Enabled = _EntityInfos->at(parentIndex).Enabled;
	for (int i = 0; i < _ParentRoots->size(); i++) {
		if (_Entities->at(childIndex) == _ParentRoots->at(i)) {
			_ParentRoots->erase(_ParentRoots->begin() + i);
		}
	}
	if (!_EntityInfos->at(parentIndex).Parent.IsNull()) return;
	bool addParent = true;
	for (int i = 0; i < _ParentRoots->size(); i++) {
		if (_Entities->at(parentIndex) == _ParentRoots->at(i)) {
			addParent = false;
		}
	}
	if (addParent) _ParentRoots->push_back(_Entities->at(parentIndex));
	
}

Entity UniEngine::EntityManager::GetParent(Entity entity)
{
	if (entity.IsNull()) return Entity();
	size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Entity already deleted!");
		return Entity();
	}
	return _EntityInfos->at(entityIndex).Parent;
}

std::vector<Entity> UniEngine::EntityManager::GetChildren(Entity entity)
{
	if (entity.IsNull()) return std::vector<Entity>();
	size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Parent already deleted!");
		return std::vector<Entity>();
	}
	return _EntityInfos->at(entityIndex).Children;
}

size_t UniEngine::EntityManager::GetChildrenAmount(Entity entity)
{
	if (entity.IsNull()) return 0;
	size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Parent already deleted!");
		return 0;
	}
	return _EntityInfos->at(entityIndex).Children.size();
}

inline void UniEngine::EntityManager::ForEachChild(Entity entity, const std::function<void(Entity child)>& func)
{
	for (auto i : _EntityInfos->at(entity.Index).Children) {
		func(i);
	}
}

void UniEngine::EntityManager::RemoveChild(Entity entity, Entity parent)
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
	_CurrentActivitedWorldEntityStorage->ParentHierarchyVersion++;
	_EntityInfos->at(childIndex).Parent = Entity();
	size_t childrenCount = _EntityInfos->at(parentIndex).Children.size();
	for (int i = 0; i < childrenCount; i++) {
		if (_EntityInfos->at(parentIndex).Children[i].Index == childIndex) {
			_EntityInfos->at(parentIndex).Children[i] = _EntityInfos->at(parentIndex).Children.back();
			_EntityInfos->at(parentIndex).Children.pop_back();
			break;
		}
	}
	if (_EntityInfos->at(parentIndex).Children.empty()) {
		for (int i = 0; i < _ParentRoots->size(); i++) {
			if (_ParentRoots->at(i) == _Entities->at(parentIndex)) _ParentRoots->erase(_ParentRoots->begin() + i);
		}
	}
}

void UniEngine::EntityManager::GetParentRoots(std::vector<Entity>* container)
{
	size_t amount = _ParentRoots->size();
	container->resize(container->size() + amount);
	memcpy(&container->at(container->size() - amount), _ParentRoots->data(), amount * sizeof(Entity));
}

size_t UniEngine::EntityManager::GetParentHierarchyVersion()
{
	return _CurrentActivitedWorldEntityStorage->ParentHierarchyVersion;
}

EntityArchetype UniEngine::EntityManager::GetEntityArchetype(Entity entity)
{
	EntityArchetype retVal = EntityArchetype();
	if (entity.IsNull()) return retVal;
	EntityInfo info = _EntityInfos->at(entity.Index);
	retVal.Index = info.ArchetypeInfoIndex;
	return retVal;
}

void UniEngine::EntityManager::SetEnable(Entity entity, bool value) {
	_EntityInfos->at(entity.Index).Enabled = value;
	for (auto i : _EntityInfos->at(entity.Index).Children) {
		SetEnable(i, value);
	}
}

bool UniEngine::EntityManager::IsEntityEnabled(Entity entity) {
	return _EntityInfos->at(entity.Index).Enabled;
}

bool UniEngine::EntityManager::IsEntityDeleted(size_t index)
{
	return _Entities->at(index).Version == 0;
}

EntityQuery UniEngine::EntityManager::CreateEntityQuery()
{
	EntityQuery retVal;
	if (_EntityQueryPools->empty()) {
		retVal.Index = _EntityQueries->size();
		retVal.Version = 1;
		_EntityQueries->push_back(retVal);
		
		EntityQueryInfo info;
		_EntityQueryInfos->push_back(info);
		RefreshEntityQueryInfos(retVal.Index);
	}
	else {
		retVal = _EntityQueryPools->front();
		_EntityQueryPools->pop();
		_EntityQueries->at(retVal.Index).Version = retVal.Version;
		RefreshEntityQueryInfos(retVal.Index);
	}
	return retVal;
}

void UniEngine::EntityManager::DeleteEntityQuery(EntityQuery entityQuery)
{
	if (entityQuery.IsNull()) return;
	size_t index = entityQuery.Index;
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

std::vector<EntityComponentStorage> UniEngine::EntityManager::UnsafeQueryStorages(EntityQuery entityQuery)
{
	if (entityQuery.IsNull()) return std::vector<EntityComponentStorage>();
	size_t index = entityQuery.Index;
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

ComponentDataChunkArray* UniEngine::EntityManager::UnsafeGetEntityComponentDataChunkArray(EntityArchetype entityArchetype)
{
	if (entityArchetype.IsNull()) return nullptr;
	return _EntityComponentStorage->at(entityArchetype.Index).ChunkArray;
}

void UniEngine::EntityManager::ForAllEntities(const std::function<void(int i, Entity entity)>& func)
{
	for (int index = 0; index < _Entities->size(); index++) {
		if (_Entities->at(index).Version != 0) {
			func(index, _Entities->at(index));
		}
	}
}

inline void UniEngine::EntityManager::ForAllRootParent(const std::function<void(int i, Entity rootParent)>& func)
{
	for (int index = 0; index < _ParentRoots->size(); index++) {
		func(index, _ParentRoots->at(index));
	}
}

void UniEngine::EntityManager::GetEntityArray(EntityQuery entityQuery, std::vector<Entity>* container)
{
	if (entityQuery.IsNull()) return;
	size_t index = entityQuery.Index;
	if (_EntityQueries->at(index).IsDeleted()) {
		Debug::Error("EntityQuery already deleted!");
		return;
	}
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return;
	}
	for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
		GetEntityStorage(i, container);
	}
}

void UniEngine::EntityQuery::ToEntityArray(std::vector<Entity>* container)
{
	EntityManager::GetEntityArray(*this, container);
}

UniEngine::EntityComponentStorage::EntityComponentStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array)
{
	ArchetypeInfo = info;
	ChunkArray = array;
}

size_t UniEngine::EntityManager::GetEntityAmount(EntityQuery entityQuery) {
	if (entityQuery.IsNull()) return 0;
	size_t index = entityQuery.Index;
	if (_EntityQueries->at(index).IsDeleted()) {
		Debug::Error("EntityQuery already deleted!");
		return 0;
	}
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return 0;
	}
	size_t retVal = 0;
	for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
		 retVal += i.ArchetypeInfo->EntityAliveCount;
	}
	return retVal;
}

size_t UniEngine::EntityQuery::GetEntityAmount()
{
	return EntityManager::GetEntityAmount(*this);
}
#pragma endregion

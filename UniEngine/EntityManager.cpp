#include "pch.h"
#include "EntityManager.h"
#include "Debug.h"
#include "UniEngine.h"
#include "World.h"
using namespace UniEngine;
std::vector<WorldEntityStorage*> UniEngine::EntityManager::_WorldEntityStorage;
WorldEntityStorage* UniEngine::EntityManager::_CurrentActivatedWorldEntityStorage;
std::vector<EntityInfo>* UniEngine::EntityManager::_EntityInfos;
std::vector<Entity>* UniEngine::EntityManager::_Entities;
std::vector<Entity>* UniEngine::EntityManager::_ParentRoots;
std::vector<EntityComponentStorage>* UniEngine::EntityManager::_EntityComponentStorage;
SharedComponentStorage* UniEngine::EntityManager::_EntitySharedComponentStorage;
PrivateComponentStorage* UniEngine::EntityManager::_EntityPrivateComponentStorage;
std::vector<EntityQuery>* UniEngine::EntityManager::_EntityQueries;
std::vector<EntityQueryInfo>* UniEngine::EntityManager::_EntityQueryInfos;
std::queue<EntityQuery>* UniEngine::EntityManager::_EntityQueryPools;
//std::map<size_t, ComponentCreateFunction> UniEngine::EntityManager::_ComponentCreationFunctionMap;
//std::map<size_t, ComponentDestroyFunction> UniEngine::EntityManager::_ComponentDestructionFunctionMap;
#pragma region EntityManager

void UniEngine::EntityManager::ForEachComponentUnsafe(Entity entity, const std::function<void(ComponentType type, void* data)>& func)
{
	if (entity.IsNull()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		for (const auto& i : chunkInfo->ComponentTypes) {
			func(i, (void*)((char*)chunk.Data + i.Offset * chunkInfo->ChunkCapacity + chunkPointer * i.Size));
		}
	}
}

void EntityManager::ForEachSharedComponent(Entity entity, const std::function<void(SharedComponentElement data)>& func)
{
	if (entity.IsNull()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity)
	{
		for (auto& component : info.SharedComponentElements)
		{
			func(component);
		}
	}
}

void EntityManager::ForEachPrivateComponent(Entity entity,
	const std::function<void(PrivateComponentElement& data)>& func)
{
	if (entity.IsNull()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity)
	{
		for (auto& component : info.PrivateComponentElements)
		{
			func(component);
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
	EntityInfo& info = _EntityInfos->at(entity.Index);
	Entity actualEntity = _Entities->at(entity.Index);

	EntityComponentStorage storage = _EntityComponentStorage->at(info.ArchetypeInfoIndex);
	if (actualEntity == entity) {
		/*
		for (auto& type : archetypeInfoinfo->ComponentTypes)
		{
			auto search = _ComponentDestructionFunctionMap.find(type.TypeID);
			if (search != _ComponentDestructionFunctionMap.end())
			{
				search->second.Function(GetComponentDataPointer(entity, type.TypeID));
			}
		}
		*/
		_EntitySharedComponentStorage->DeleteEntity(actualEntity);
		_EntityPrivateComponentStorage->DeleteEntity(actualEntity);
		info.Version = actualEntity.Version + 1;
		info.PrivateComponentElements.clear();
		info.SharedComponentElements.clear();
		//Set to version 0, marks it as deleted.
		actualEntity.Version = 0;
		EntityComponentStorage storage = _EntityComponentStorage->at(info.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[info.ChunkArrayIndex] = actualEntity;
		auto originalIndex = info.ChunkArrayIndex;
		if (info.ChunkArrayIndex != storage.ArchetypeInfo->EntityAliveCount - 1) {
			auto swappedIndex = SwapEntity(storage, info.ChunkArrayIndex, storage.ArchetypeInfo->EntityAliveCount - 1);
			_EntityInfos->at(entity.Index).ChunkArrayIndex = storage.ArchetypeInfo->EntityAliveCount - 1;
			_EntityInfos->at(swappedIndex).ChunkArrayIndex = originalIndex;
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
				if (!i.ArchetypeInfo->HasType(type.TypeID)) check = false;
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
				if (_EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->HasType(type.TypeID)) contain = true;
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
				if (_EntityQueryInfos->at(index).QueriedStorages.at(i).ArchetypeInfo->HasType(type.TypeID)) contain = true;
				if (contain) break;
			}
			if (contain) {
				_EntityQueryInfos->at(index).QueriedStorages.erase(_EntityQueryInfos->at(index).QueriedStorages.begin() + i);
				i--;
			}
		}
	}
}

void UniEngine::EntityManager::GetEntityStorage(EntityComponentStorage storage, std::vector<Entity>& container)
{
	size_t amount = storage.ArchetypeInfo->EntityAliveCount;
	if (amount == 0) return;
	container.resize(container.size() + amount);
	size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
	size_t chunkAmount = amount / capacity;
	size_t remainAmount = amount % capacity;
	memcpy(&container.at(container.size() - amount), storage.ChunkArray->Entities.data(), amount * sizeof(Entity));
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

std::vector<Entity>* UniEngine::EntityManager::GetParentRootsUnsafe()
{
	return _ParentRoots;
}

void UniEngine::EntityManager::GetAllEntities(std::vector<Entity>& target) {
	target.insert(target.end(), _Entities->begin() + 1, _Entities->end());
}

std::vector<Entity>* UniEngine::EntityManager::GetAllEntitiesUnsafe()
{
	return _Entities;
}


void UniEngine::EntityManager::SetWorld(World* world)
{
	size_t index = world->GetIndex();
	while (index >= _WorldEntityStorage.size()) {
		auto storage = new WorldEntityStorage();
		storage->Entities.emplace_back();
		storage->EntityInfos.emplace_back();
		storage->EntityComponentStorage.emplace_back(nullptr, nullptr);
		storage->EntityQueries.emplace_back();
		storage->EntityQueryInfos.emplace_back();
		_WorldEntityStorage.push_back(storage);
	}
	WorldEntityStorage* targetStorage = _WorldEntityStorage[index];
	_CurrentActivatedWorldEntityStorage = targetStorage;
	_Entities = &targetStorage->Entities;
	_ParentRoots = &targetStorage->ParentRoots;
	_EntityInfos = &targetStorage->EntityInfos;
	_EntityComponentStorage = &targetStorage->EntityComponentStorage;
	_EntitySharedComponentStorage = &targetStorage->EntitySharedComponentStorage;
	_EntityPrivateComponentStorage = &targetStorage->EntityPrivateComponentStorage;
	_EntityQueries = &targetStorage->EntityQueries;
	_EntityQueryInfos = &targetStorage->EntityQueryInfos;
	_EntityQueryPools = &targetStorage->EntityQueryPools;
}


Entity UniEngine::EntityManager::CreateEntity(EntityArchetype archetype, std::string name)
{
	if (!Application::_Initialized)
	{
		Debug::Error("CreateEntity: Initialize Engine first!");
		return Entity();
	}
	if (archetype.Index == 0) return Entity();
	Entity retVal;
	EntityComponentStorage storage = _EntityComponentStorage->at(archetype.Index);
	EntityArchetypeInfo* info = storage.ArchetypeInfo;
	if (info->EntityCount == info->EntityAliveCount) {
		size_t chunkIndex = info->EntityCount / info->ChunkCapacity;
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
		if (name.length() == 0)
		{
			entityInfo.Name = "Unnamed";
		}
		else
		{
			entityInfo.Name = name;
		}
		entityInfo.Version = 1;
		entityInfo.Parent = Entity();
		entityInfo.Enabled = true;
		entityInfo.ArchetypeInfoIndex = archetype.Index;
		entityInfo.ChunkArrayIndex = info->EntityCount;
		storage.ChunkArray->Entities.push_back(retVal);
		_EntityInfos->push_back(std::move(entityInfo));
		_Entities->push_back(retVal);
		info->EntityCount++;
		info->EntityAliveCount++;
	}
	else {
		//TODO: Update version when we delete entity.
		retVal = storage.ChunkArray->Entities.at(info->EntityAliveCount);
		EntityInfo& entityInfo = _EntityInfos->at(retVal.Index);
		entityInfo.Enabled = true;
		if (name.length() == 0)
		{
			entityInfo.Name = "Unnamed";
		}
		else
		{
			entityInfo.Name = name;
		}
		retVal.Version = entityInfo.Version;
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		_Entities->at(retVal.Index) = retVal;
		storage.ArchetypeInfo->EntityAliveCount++;
		//Reset all component data
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ArchetypeInfo;
		size_t chunkIndex = entityInfo.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		size_t chunkPointer = entityInfo.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		ComponentDataChunk chunk = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		
		for (const auto& i : chunkInfo->ComponentTypes) {
			size_t offset = i.Offset * chunkInfo->ChunkCapacity + chunkPointer * i.Size;
			chunk.ClearData(offset, i.Size);
		}
	}
	/*
	for (auto& type : info->ComponentTypes)
	{
		auto search = _ComponentCreationFunctionMap.find(type.TypeID);
		if (search != _ComponentCreationFunctionMap.end())
		{
			search->second.Function(GetComponentDataPointer(retVal, type.TypeID));
		}
	}
	*/
	return retVal;
}

void UniEngine::EntityManager::DeleteEntity(Entity entity)
{
	if (!Application::_Initialized)
	{
		Debug::Error("DeleteEntity: Initialize Engine first!");
		return;
	}
	if (entity.IsNull()) return;
	if (entity.IsDeleted())
	{
		Debug::Error("DeleteEntity: Entity already deleted!");
		return;
	}
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
	if (_EntityInfos->at(entityIndex).Parent.Index != 0) RemoveChild(entity, _EntityInfos->at(entityIndex).Parent);
	DeleteEntityInternal(entity);

	_CurrentActivatedWorldEntityStorage->ParentHierarchyVersion++;
}

std::string EntityManager::GetEntityName(Entity entity)
{
	if (entity.IsNull()) return "";
	size_t index = entity.Index;

	if (entity != _Entities->at(index)) {
		Debug::Error("Child already deleted!");
		return "";
	}
	return _EntityInfos->at(index).Name;
}

bool EntityManager::SetEntityName(Entity entity, std::string name)
{
	if (entity.IsNull()) return false;
	size_t index = entity.Index;

	if (entity != _Entities->at(index)) {
		Debug::Error("Child already deleted!");
		return false;
	}
	if (name.length() != 0) {
		_EntityInfos->at(index).Name = name;
		return true;
	}

	_EntityInfos->at(index).Name = "Unnamed";
	return false;

}

void UniEngine::EntityManager::SetParent(Entity entity, Entity parent)
{
	if (entity.IsNull() || parent.IsNull()) return;
	_CurrentActivatedWorldEntityStorage->ParentHierarchyVersion++;
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
	auto children = _EntityInfos->at(entity.Index).Children;
	for (auto i : children) {
		if (!i.IsDeleted()) func(i);
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
	_CurrentActivatedWorldEntityStorage->ParentHierarchyVersion++;
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
			break;
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
	return _CurrentActivatedWorldEntityStorage->ParentHierarchyVersion;
}

void EntityManager::SetComponentData(Entity entity, size_t id, size_t size, ComponentBase* data)
{
	if (entity.IsNull()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);

	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		bool found = false;
		for (const auto& type : chunkInfo->ComponentTypes)
		{
			if (type.TypeID == id)
			{
				chunk.SetData(static_cast<size_t>(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size), size, data);
				return;
			}
		}
		Debug::Log("ComponentData doesn't exist");
	}
	else {
		Debug::Error("Entity already deleted!");
	}
}

ComponentBase* EntityManager::GetComponentDataPointer(Entity entity, size_t id)
{
	if (entity.IsNull()) return nullptr;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		for (const auto& type : chunkInfo->ComponentTypes)
		{
			if (type.TypeID == id)
			{
				return chunk.GetDataPointer(static_cast<size_t>(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size));
			}
		}
		Debug::Log("ComponentData doesn't exist");
		return nullptr;
	}
	else {
		Debug::Error("Entity already deleted!");
		return nullptr;
	}
}

bool EntityManager::RemovePrivateComponent(Entity entity, size_t typeId)
{
	if (entity.IsNull()) return false;
	bool found = false;
	for (auto i = 0; i < _EntityInfos->at(entity.Index).PrivateComponentElements.size(); i++)
	{
		if (_EntityInfos->at(entity.Index).PrivateComponentElements[i].TypeID == typeId)
		{
			found = true;
			_EntityInfos->at(entity.Index).PrivateComponentElements.erase(_EntityInfos->at(entity.Index).PrivateComponentElements.begin() + i);
		}
	}
	_EntityPrivateComponentStorage->RemovePrivateComponent(entity, typeId);
	return found;
}

EntityArchetype UniEngine::EntityManager::GetEntityArchetype(Entity entity)
{
	EntityArchetype retVal = EntityArchetype();
	if (entity.IsNull()) return retVal;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	retVal.Index = info.ArchetypeInfoIndex;
	return retVal;
}

void UniEngine::EntityManager::SetEnable(Entity entity, bool value) {
	if (_EntityInfos->at(entity.Index).Enabled != value)
	{
		for (auto& i : _EntityInfos->at(entity.Index).PrivateComponentElements)
		{
			if (value)
			{
				i.PrivateComponentData->OnEntityEnable();
			}
			else
			{
				i.PrivateComponentData->OnEntityDisable();
			}
		}
	}
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

std::vector<EntityComponentStorage> UniEngine::EntityManager::UnsafeQueryStorage(EntityQuery entityQuery)
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

void UniEngine::EntityManager::GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container)
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

void UniEngine::EntityQuery::ToEntityArray(std::vector<Entity>& container)
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

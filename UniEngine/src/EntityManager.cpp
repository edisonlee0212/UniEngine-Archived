#include "pch.h"
#include "EntityManager.h"
#include "Debug.h"
#include "UniEngine.h"
#include "World.h"
using namespace UniEngine;
EntityArchetype EntityManager::_BasicArchetype;
WorldEntityStorage* UniEngine::EntityManager::_CurrentAttachedWorldEntityStorage = nullptr;
std::vector<EntityInfo>* UniEngine::EntityManager::_EntityInfos = nullptr;
std::vector<Entity>* UniEngine::EntityManager::_Entities = nullptr;
std::vector<Entity>* UniEngine::EntityManager::_ParentRoots = nullptr;
std::vector<EntityComponentStorage>* UniEngine::EntityManager::_EntityComponentStorage = nullptr;
PrivateComponentStorage* UniEngine::EntityManager::_EntityPrivateComponentStorage = nullptr;
std::vector<EntityQuery>* UniEngine::EntityManager::_EntityQueries = nullptr;
std::vector<EntityQueryInfo>* UniEngine::EntityManager::_EntityQueryInfos = nullptr;
std::queue<EntityQuery>* UniEngine::EntityManager::_EntityQueryPools = nullptr;
#pragma region EntityManager
bool UniEngine::ComponentTypeComparator(const ComponentType& a, const ComponentType& b)
{
	return a.TypeID < b.TypeID;
}

void UniEngine::EntityManager::UnsafeForEachComponent(const Entity& entity, const std::function<void(ComponentType type, void* data)>& func)
{
	if (!entity.IsValid()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		const size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		const size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		const ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		for (const auto& i : chunkInfo->ComponentTypes) {
			func(i, static_cast<void*>(static_cast<char*>(chunk.Data) + i.Offset * chunkInfo->ChunkCapacity + chunkPointer * i.Size));
		}
	}
}

void EntityManager::ForEachPrivateComponent(const Entity& entity,
	const std::function<void(PrivateComponentElement& data)>& func)
{
	if (!entity.IsValid()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity)
	{
		for (auto& component : info.PrivateComponentElements)
		{
			func(component);
		}
	}
}

void UniEngine::EntityManager::UnsafeForEachEntityStorage(const std::function<void(int i, EntityComponentStorage storage)>& func)
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
		_EntityPrivateComponentStorage->DeleteEntity(actualEntity);
		info.Version = actualEntity.Version + 1;
		info.PrivateComponentElements.clear();
		//Set to version 0, marks it as deleted.
		actualEntity.Version = 0;
		EntityComponentStorage storage = _EntityComponentStorage->at(info.ArchetypeInfoIndex);
		storage.ChunkArray->Entities[info.ChunkArrayIndex] = actualEntity;
		const auto originalIndex = info.ChunkArrayIndex;
		if (info.ChunkArrayIndex != storage.ArchetypeInfo->EntityAliveCount - 1) {
			const auto swappedIndex = SwapEntity(storage, info.ChunkArrayIndex, storage.ArchetypeInfo->EntityAliveCount - 1);
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
	_EntityQueryInfos->at(index).QueriedStorage.clear();
	//Select storage with every contained.
	if (!_EntityQueryInfos->at(index).AllComponentTypes.empty()) {
		for (auto i : *_EntityComponentStorage) {
			if (i.ArchetypeInfo == nullptr) continue;
			bool check = true;
			for (const auto& type : _EntityQueryInfos->at(index).AllComponentTypes) {
				if (!i.ArchetypeInfo->HasType(type.TypeID)) check = false;
			}
			if (check) _EntityQueryInfos->at(index).QueriedStorage.push_back(i);
		}
	}
	else {
		for (auto i : *_EntityComponentStorage) {
			if (i.ArchetypeInfo == nullptr) continue;
			_EntityQueryInfos->at(index).QueriedStorage.push_back(i);
		}
	}
	//Erase with any
	if (!_EntityQueryInfos->at(index).AnyComponentTypes.empty()) {
		for (int i = 0; i < _EntityQueryInfos->at(index).QueriedStorage.size(); i++) {
			bool contain = false;
			for (const auto& type : _EntityQueryInfos->at(index).AnyComponentTypes) {
				if (_EntityQueryInfos->at(index).QueriedStorage.at(i).ArchetypeInfo->HasType(type.TypeID)) contain = true;
				if (contain) break;
			}
			if (!contain) {
				_EntityQueryInfos->at(index).QueriedStorage.erase(_EntityQueryInfos->at(index).QueriedStorage.begin() + i);
				i--;
			}
		}
	}
	//Erase with none
	if (!_EntityQueryInfos->at(index).NoneComponentTypes.empty()) {
		for (int i = 0; i < _EntityQueryInfos->at(index).QueriedStorage.size(); i++) {
			bool contain = false;
			for (const auto& type : _EntityQueryInfos->at(index).NoneComponentTypes) {
				if (_EntityQueryInfos->at(index).QueriedStorage.at(i).ArchetypeInfo->HasType(type.TypeID)) contain = true;
				if (contain) break;
			}
			if (contain) {
				_EntityQueryInfos->at(index).QueriedStorage.erase(_EntityQueryInfos->at(index).QueriedStorage.begin() + i);
				i--;
			}
		}
	}
}

void EntityManager::EraseDuplicates(std::vector<ComponentType>& types)
{
	std::vector<ComponentType> copy;
	copy.insert(copy.begin(), types.begin(), types.end());
	types.clear();
	for(const auto& i : copy)
	{
		bool found = false;
		for(const auto j : types)
		{
			if (i == j) {
				found = true;
				break;
			}
		}
		if(found) continue;
		types.push_back(i);
	}
}

void UniEngine::EntityManager::GetEntityStorage(EntityComponentStorage storage, std::vector<Entity>& container)
{
	const size_t amount = storage.ArchetypeInfo->EntityAliveCount;
	if (amount == 0) return;
	container.resize(container.size() + amount);
	const size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
	size_t chunkAmount = amount / capacity;
	size_t remainAmount = amount % capacity;
	memcpy(&container.at(container.size() - amount), storage.ChunkArray->Entities.data(), amount * sizeof(Entity));
}

size_t UniEngine::EntityManager::SwapEntity(EntityComponentStorage storage, size_t index1, size_t index2)
{
	if (index1 == index2) return -1;
	auto info = storage.ArchetypeInfo;
	const size_t retVal = storage.ChunkArray->Entities[index2].Index;
	const Entity other = storage.ChunkArray->Entities[index2];
	storage.ChunkArray->Entities[index2] = storage.ChunkArray->Entities[index1];
	storage.ChunkArray->Entities[index1] = other;
	const size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
	const size_t chunkIndex1 = index1 / capacity;
	const size_t chunkIndex2 = index2 / capacity;
	const size_t chunkPointer1 = index1 % capacity;
	const size_t chunkPointer2 = index2 % capacity;

	for (auto i : storage.ArchetypeInfo->ComponentTypes) {
		void* temp = static_cast<void*>(malloc(i.Size));
		void* d1 = static_cast<void*>(static_cast<char*>(storage.ChunkArray->Chunks[chunkIndex1].Data)
			+ i.Offset * capacity
			+ i.Size * chunkPointer1);

		void* d2 = static_cast<void*>(static_cast<char*>(storage.ChunkArray->Chunks[chunkIndex2].Data)
			+ i.Offset * capacity
			+ i.Size * chunkPointer2);

		memcpy(temp, d1, i.Size);
		memcpy(d1, d2, i.Size);
		memcpy(d2, temp, i.Size);
		free(temp);
	}
	return retVal;
}

std::vector<Entity>* UniEngine::EntityManager::UnsafeGetParentRoots()
{
	return _ParentRoots;
}

void UniEngine::EntityManager::GetAllEntities(std::vector<Entity>& target) {
	target.insert(target.end(), _Entities->begin() + 1, _Entities->end());
}

void EntityManager::Detach()
{
	_CurrentAttachedWorldEntityStorage = nullptr;
	_Entities = nullptr;
	_ParentRoots = nullptr;
	_EntityInfos = nullptr;
	_EntityComponentStorage = nullptr;
	_EntityPrivateComponentStorage = nullptr;
	_EntityQueries = nullptr;
	_EntityQueryInfos = nullptr;
	_EntityQueryPools = nullptr;
}

std::vector<Entity>* UniEngine::EntityManager::UnsafeGetAllEntities()
{
	return _Entities;
}


void UniEngine::EntityManager::Attach(std::unique_ptr<World>& world)
{
	WorldEntityStorage* targetStorage = &world->_WorldEntityStorage;
	_CurrentAttachedWorldEntityStorage = targetStorage;
	_Entities = &targetStorage->Entities;
	_ParentRoots = &targetStorage->ParentRoots;
	_EntityInfos = &targetStorage->EntityInfos;
	_EntityComponentStorage = &targetStorage->EntityComponentStorage;
	_EntityPrivateComponentStorage = &targetStorage->EntityPrivateComponentStorage;
	_EntityQueries = &targetStorage->EntityQueries;
	_EntityQueryInfos = &targetStorage->EntityQueryInfos;
	_EntityQueryPools = &targetStorage->EntityQueryPools;
	_BasicArchetype = CreateEntityArchetype("Basic", Transform(), GlobalTransform());
}


Entity EntityManager::CreateEntity(const std::string& name)
{
	if (!_CurrentAttachedWorldEntityStorage)
	{
		Debug::Error("EntityManager not attached to any world!");
		return Entity();
	}
	return CreateEntity(_BasicArchetype, name);
}

Entity UniEngine::EntityManager::CreateEntity(EntityArchetype archetype, const std::string& name)
{
	if (!_CurrentAttachedWorldEntityStorage)
	{
		Debug::Error("EntityManager not attached to any world!");
		return Entity();
	}
	if (archetype.IsValid()) return Entity();
	Entity retVal;
	EntityComponentStorage storage = _EntityComponentStorage->at(archetype.Index);
	EntityArchetypeInfo* info = storage.ArchetypeInfo;
	if (info->EntityCount == info->EntityAliveCount) {
		const size_t chunkIndex = info->EntityCount + 1 / info->ChunkCapacity;
		if (storage.ChunkArray->Chunks.size() <= chunkIndex) {
			//Allocate new chunk;
			ComponentDataChunk chunk;
			chunk.Data = static_cast<void*>(calloc(1, ARCHETYPECHUNK_SIZE));
			storage.ChunkArray->Chunks.push_back(chunk);
		}
		retVal.Index = _Entities->size();
		//If the version is 0 in chunk means it's deleted.
		retVal.Version = 1;
		EntityInfo entityInfo;
		entityInfo.Name = name;
		entityInfo.ArchetypeInfoIndex = archetype.Index;
		entityInfo.ChunkArrayIndex = info->EntityCount;
		storage.ChunkArray->Entities.push_back(retVal);
		_EntityInfos->push_back(std::move(entityInfo));
		_Entities->push_back(retVal);
		info->EntityCount++;
		info->EntityAliveCount++;
	}
	else {
		retVal = storage.ChunkArray->Entities.at(info->EntityAliveCount);
		EntityInfo& entityInfo = _EntityInfos->at(retVal.Index);
		entityInfo.Enabled = true;
		entityInfo.Name = name;
		retVal.Version = entityInfo.Version;
		storage.ChunkArray->Entities[entityInfo.ChunkArrayIndex] = retVal;
		_Entities->at(retVal.Index) = retVal;
		storage.ArchetypeInfo->EntityAliveCount++;
		//Reset all component data
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ArchetypeInfo;
		const size_t chunkIndex = entityInfo.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		const size_t chunkPointer = entityInfo.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		const ComponentDataChunk chunk = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		for (const auto& i : chunkInfo->ComponentTypes) {
			const size_t offset = i.Offset * chunkInfo->ChunkCapacity + chunkPointer * i.Size;
			chunk.ClearData(offset, i.Size);
		}
	}

	const Transform transform;
	const GlobalTransform globalTransform;
	retVal.SetComponentData(transform);
	retVal.SetComponentData(globalTransform);
	
	return retVal;
}

std::vector<Entity> EntityManager::CreateEntities(EntityArchetype archetype, const size_t& amount, const std::string& name)
{
	if (!_CurrentAttachedWorldEntityStorage)
	{
		Debug::Error("EntityManager not attached to any world!");
		return std::vector<Entity>();
	}
	if (archetype.IsValid()) return std::vector<Entity>();
	
	EntityComponentStorage storage = _EntityComponentStorage->at(archetype.Index);
	EntityArchetypeInfo* info = storage.ArchetypeInfo;
	info->EntityCount += amount;
	info->EntityAliveCount += amount;
	const size_t chunkIndex = info->EntityCount + 1 / info->ChunkCapacity;
	while (storage.ChunkArray->Chunks.size() <= chunkIndex) {
		//Allocate new chunk;
		ComponentDataChunk chunk;
		chunk.Data = static_cast<void*>(calloc(1, ARCHETYPECHUNK_SIZE));
		storage.ChunkArray->Chunks.push_back(chunk);
	}
	const size_t originalSize = _Entities->size();
	_Entities->resize(originalSize + amount);
	_EntityInfos->resize(originalSize + amount);
	
	for(int i = 0; i < amount; i++)
	{
		auto& entity = _Entities->at(originalSize + i);
		entity.Index = originalSize + i;
		entity.Version = 1;
		
		auto& entityInfo = _EntityInfos->at(originalSize + i);
		entityInfo.Name = name;
		entityInfo.ArchetypeInfoIndex = archetype.Index;
		entityInfo.ChunkArrayIndex = info->EntityCount - amount + i;
	}
	std::vector<Entity> retVal;
	storage.ChunkArray->Entities.insert(storage.ChunkArray->Entities.end(), _Entities->begin() + originalSize, _Entities->begin() + originalSize + amount);
	const Transform transform;
	const GlobalTransform globalTransform;

	const int threadSize = JobManager::GetThreadPool().Size();
	int perThreadAmount = amount / threadSize;
	int reminder = amount % threadSize;
	if(perThreadAmount > 0)
	{
		std::vector<std::shared_future<void>> results;
		for(int i = 0; i < threadSize; i++)
		{
			results.push_back(
				JobManager::GetThreadPool().Push([i, perThreadAmount, originalSize](int id)
					{
						const Transform transform;
						const GlobalTransform globalTransform;
						for (int index = originalSize + i * perThreadAmount; index < originalSize + (i + 1) * perThreadAmount; index++) {
							auto& entity = _Entities->at(index);
							entity.SetComponentData(transform);
							entity.SetComponentData(globalTransform);
						}
					}
			).share());
		}
		results.push_back(
			JobManager::GetThreadPool().Push([perThreadAmount, originalSize, &amount, threadSize](int id)
				{
					const Transform transform;
					const GlobalTransform globalTransform;
					for (int index = originalSize + perThreadAmount * threadSize; index < originalSize + amount; index++) {
						auto& entity = _Entities->at(index);
						entity.SetComponentData(transform);
						entity.SetComponentData(globalTransform);
					}
				}
		).share());
		for (const auto& i : results) i.wait();
	}

	
	retVal.insert(retVal.begin(), _Entities->begin() + originalSize, _Entities->begin() + originalSize + amount);
	return retVal;
}

void UniEngine::EntityManager::DeleteEntity(const Entity& entity)
{
	if (!Application::_Initialized)
	{
		Debug::Error("DeleteEntity: Initialize Engine first!");
		return;
	}
	if (!entity.IsValid()) return;
	const size_t entityIndex = entity.Index;
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

	_CurrentAttachedWorldEntityStorage->ParentHierarchyVersion++;
}

std::string EntityManager::GetEntityName(const Entity& entity)
{
	if (!entity.IsValid()) return "";
	const size_t index = entity.Index;

	if (entity != _Entities->at(index)) {
		Debug::Error("Child already deleted!");
		return "";
	}
	return _EntityInfos->at(index).Name;
}

void EntityManager::SetEntityName(const Entity& entity, const std::string& name)
{
	if (!entity.IsValid()) return;
	const size_t index = entity.Index;

	if (entity != _Entities->at(index)) {
		Debug::Error("Child already deleted!");
		return;
	}
	if (name.length() != 0) {
		_EntityInfos->at(index).Name = name;
		return;
	}
	_EntityInfos->at(index).Name = "Unnamed";
}

void UniEngine::EntityManager::SetParent(const Entity& entity, const Entity& parent)
{
	if (!entity.IsValid() || !parent.IsValid()) return;
	_CurrentAttachedWorldEntityStorage->ParentHierarchyVersion++;
	const size_t childIndex = entity.Index;
	const size_t parentIndex = parent.Index;
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
	if(entity.HasComponentData<Transform>() && entity.HasComponentData<GlobalTransform>() && parent.HasComponentData<GlobalTransform>())
	{
		const auto childGlobalTransform = entity.GetComponentData<GlobalTransform>();
		const auto parentGlobalTransform = parent.GetComponentData<GlobalTransform>();
		Transform childTransform;
		childTransform.Value = glm::inverse(parentGlobalTransform.Value) * childGlobalTransform.Value;
		entity.SetComponentData(childTransform);
	}
	_EntityInfos->at(childIndex).Parent = parent;
	_EntityInfos->at(parentIndex).Children.push_back(entity);
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

Entity UniEngine::EntityManager::GetParent(const Entity& entity)
{
	if (!entity.IsValid()) return Entity();
	const size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Entity already deleted!");
		return Entity();
	}
	return _EntityInfos->at(entityIndex).Parent;
}

std::vector<Entity> UniEngine::EntityManager::GetChildren(const Entity& entity)
{
	if (!entity.IsValid()) return std::vector<Entity>();
	const size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Parent already deleted!");
		return std::vector<Entity>();
	}
	return _EntityInfos->at(entityIndex).Children;
}

size_t UniEngine::EntityManager::GetChildrenAmount(const Entity& entity)
{
	if (!entity.IsValid()) return 0;
	const size_t entityIndex = entity.Index;
	if (entity != _Entities->at(entityIndex)) {
		Debug::Error("Parent already deleted!");
		return 0;
	}
	return _EntityInfos->at(entityIndex).Children.size();
}

inline void UniEngine::EntityManager::ForEachChild(const Entity& entity, const std::function<void(Entity child)>& func)
{
	if (!entity.IsValid()) return;
	auto children = _EntityInfos->at(entity.Index).Children;
	for (auto i : children) {
		if (!i.IsDeleted()) func(i);
	}
}

void UniEngine::EntityManager::RemoveChild(const Entity& entity, const Entity& parent)
{
	if (!entity.IsValid() || !parent.IsValid()) return;
	const size_t childIndex = entity.Index;
	const size_t parentIndex = parent.Index;

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
	_CurrentAttachedWorldEntityStorage->ParentHierarchyVersion++;
	_EntityInfos->at(childIndex).Parent = Entity();
	const size_t childrenCount = _EntityInfos->at(parentIndex).Children.size();
	
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
	if (entity.HasComponentData<Transform>() && entity.HasComponentData<GlobalTransform>())
	{
		const auto childGlobalTransform = entity.GetComponentData<GlobalTransform>();
		Transform childTransform;
		childTransform.Value = childGlobalTransform.Value;
		entity.SetComponentData(childTransform);
	}
}

void UniEngine::EntityManager::GetParentRoots(std::vector<Entity>& container)
{
	const size_t amount = _ParentRoots->size();
	container.resize(container.size() + amount);
	memcpy(&container.at(container.size() - amount), _ParentRoots->data(), amount * sizeof(Entity));
}

size_t UniEngine::EntityManager::GetParentHierarchyVersion()
{
	return _CurrentAttachedWorldEntityStorage->ParentHierarchyVersion;
}

void EntityManager::RemoveComponentData(const Entity& entity, size_t typeID)
{
	if (!entity.IsValid()) return;
	if (typeID == typeid(Transform).hash_code())
	{
		return;
	}
	if (typeID == typeid(GlobalTransform).hash_code())
	{
		return;
	}
	EntityInfo& entityInfo = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) != entity) {
		Debug::Error("Entity version mismatch!");
		return;
	}
	EntityArchetypeInfo* archetypeInfo = _EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ArchetypeInfo;
	if (archetypeInfo->ComponentTypes.size() <= 1)
	{
		Debug::Error("Remove Component Data failed: Entity must have at least 1 data component!");
		return;
	}
#pragma region Create new archetype
	auto* newArchetypeInfo = new EntityArchetypeInfo();
	newArchetypeInfo->Name = "New archetype";
	newArchetypeInfo->EntityCount = 0;
	newArchetypeInfo->ComponentTypes = archetypeInfo->ComponentTypes;
	bool found = false;
	for (int i = 0; i < newArchetypeInfo->ComponentTypes.size(); i++)
	{
		if (newArchetypeInfo->ComponentTypes[i].TypeID == typeID)
		{
			newArchetypeInfo->ComponentTypes.erase(newArchetypeInfo->ComponentTypes.begin() + i);
			found = true;
			break;
		}
	}
	if (!found)
	{
		delete newArchetypeInfo;
		Debug::Error("Failed to remove component data: Component not found");
		return;
	}
#pragma region Sort types and check duplicate
	size_t offset = 0;
	ComponentType prev = newArchetypeInfo->ComponentTypes[0];
	for (auto& i : newArchetypeInfo->ComponentTypes)
	{
		i.Offset = offset;
		offset += i.Size;
	}

	newArchetypeInfo->EntitySize = newArchetypeInfo->ComponentTypes.back().Offset + newArchetypeInfo->ComponentTypes.back().Size;
	newArchetypeInfo->ChunkCapacity = ARCHETYPECHUNK_SIZE / newArchetypeInfo->EntitySize;
	int duplicateIndex = -1;
	for (size_t i = 1; i < _EntityComponentStorage->size(); i++) {
		EntityArchetypeInfo* compareInfo = _EntityComponentStorage->at(i).ArchetypeInfo;
		if (newArchetypeInfo->ChunkCapacity != compareInfo->ChunkCapacity) continue;
		if (newArchetypeInfo->EntitySize != compareInfo->EntitySize) continue;
		bool typeCheck = true;
		for (const auto& j : newArchetypeInfo->ComponentTypes)
		{
			if (!compareInfo->HasType(j.TypeID)) typeCheck = false;
		}
		if (typeCheck) {
			duplicateIndex = compareInfo->Index;
			delete newArchetypeInfo;
			newArchetypeInfo = compareInfo;
			break;
		}
	}
#pragma endregion
	EntityArchetype archetype;
	if (duplicateIndex == -1) {
		archetype.Index = _EntityComponentStorage->size();
		newArchetypeInfo->Index = archetype.Index;
		_EntityComponentStorage->push_back(EntityComponentStorage(newArchetypeInfo, new ComponentDataChunkArray()));
	}
	else {
		archetype.Index = duplicateIndex;
	}
#pragma endregion
#pragma region Create new Entity with new archetype
	const Entity newEntity = CreateEntity(archetype);
	//Transfer component data
	for (const auto& type : newArchetypeInfo->ComponentTypes)
	{
		SetComponentData(newEntity, type.TypeID, type.Size, GetComponentDataPointer(entity, type.TypeID));
	}
	//5. Swap entity.
	EntityInfo& newEntityInfo = _EntityInfos->at(newEntity.Index);
	const auto tempArchetypeInfoIndex = newEntityInfo.ArchetypeInfoIndex;
	const auto tempChunkArrayIndex = newEntityInfo.ChunkArrayIndex;
	newEntityInfo.ArchetypeInfoIndex = entityInfo.ArchetypeInfoIndex;
	newEntityInfo.ChunkArrayIndex = entityInfo.ChunkArrayIndex;
	entityInfo.ArchetypeInfoIndex = tempArchetypeInfoIndex;
	entityInfo.ChunkArrayIndex = tempChunkArrayIndex;
	//Apply to chunk.
	_EntityComponentStorage->at(entityInfo.ArchetypeInfoIndex).ChunkArray->Entities[entityInfo.ChunkArrayIndex] = entity;
	_EntityComponentStorage->at(newEntityInfo.ArchetypeInfoIndex).ChunkArray->Entities[newEntityInfo.ChunkArrayIndex] = newEntity;
	DeleteEntity(newEntity);
#pragma endregion
	for (size_t i = 0; i < _EntityQueryInfos->size(); i++) {
		RefreshEntityQueryInfos(i);
	}
}

void EntityManager::SetComponentData(const Entity& entity, size_t id, size_t size, ComponentBase* data)
{
	if (!entity.IsValid()) return;
	EntityInfo& info = _EntityInfos->at(entity.Index);

	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		const size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		const size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		const ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		if (id == typeid(Transform).hash_code())
		{
			const auto& type = chunkInfo->ComponentTypes[0];
			chunk.SetData(static_cast<size_t>(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size), size, data);
			return;
		}
		if (id == typeid(GlobalTransform).hash_code())
		{
			const auto& type = chunkInfo->ComponentTypes[1];
			chunk.SetData(static_cast<size_t>(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size), size, data);
			return;
		}
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

ComponentBase* EntityManager::GetComponentDataPointer(const Entity& entity, size_t id)
{
	if (!entity.IsValid()) return nullptr;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	if (_Entities->at(entity.Index) == entity) {
		EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
		const size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
		const size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
		const ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
		if (id == typeid(Transform).hash_code())
		{
			const auto& type = chunkInfo->ComponentTypes[0];
			return chunk.GetDataPointer(static_cast<size_t>(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size));
		}
		if (id == typeid(GlobalTransform).hash_code())
		{
			const auto& type = chunkInfo->ComponentTypes[1];
			return chunk.GetDataPointer(static_cast<size_t>(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size));
		}
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

EntityArchetype EntityManager::CreateEntityArchetype(const std::string& name, const std::vector<ComponentType>& types)
{
	auto* info = new EntityArchetypeInfo();
	info->Name = name;
	info->EntityCount = 0;
	std::vector<ComponentType> actualTypes;
	actualTypes.push_back(typeof<Transform>());
	actualTypes.push_back(typeof<GlobalTransform>());
	actualTypes.insert(actualTypes.end(), types.begin(), types.end());
	std::sort(actualTypes.begin() + 2, actualTypes.end(), ComponentTypeComparator);
	size_t offset = 0;
	ComponentType prev = actualTypes[0];
	//Erase duplicates
	EraseDuplicates(actualTypes);
	for (auto& i : actualTypes)
	{
		i.Offset = offset;
		offset += i.Size;
	}
	info->ComponentTypes = actualTypes;
	info->EntitySize = info->ComponentTypes.back().Offset + info->ComponentTypes.back().Size;
	info->ChunkCapacity = ARCHETYPECHUNK_SIZE / info->EntitySize;
	int duplicateIndex = -1;
	for (size_t i = 1; i < _EntityComponentStorage->size(); i++) {
		EntityArchetypeInfo* compareInfo = _EntityComponentStorage->at(i).ArchetypeInfo;
		if (info->ChunkCapacity != compareInfo->ChunkCapacity) continue;
		if (info->EntitySize != compareInfo->EntitySize) continue;
		bool typeCheck = true;
		for(const auto& j : info->ComponentTypes)
		{
			if (!compareInfo->HasType(j.TypeID)) typeCheck = false;
		}
		if (typeCheck) {
			duplicateIndex = compareInfo->Index;
			delete info;
			info = compareInfo;
			break;
		}
	}
	EntityArchetype retVal;
	if (duplicateIndex == -1) {
		retVal.Index = _EntityComponentStorage->size();
		info->Index = retVal.Index;
		_EntityComponentStorage->push_back(EntityComponentStorage(info, new ComponentDataChunkArray()));
	}
	else {
		retVal.Index = duplicateIndex;
	}
	for (size_t i = 0; i < _EntityQueryInfos->size(); i++) {
		RefreshEntityQueryInfos(i);
	}
	return retVal;
}

void EntityManager::SetPrivateComponent(const Entity& entity, const std::string& name, size_t id,
	PrivateComponentBase* ptr)
{
	if (!entity.IsValid()) return;
	bool found = false;
	size_t i = 0;
	for (auto& element : _EntityInfos->at(entity.Index).PrivateComponentElements)
	{
		if (id == element.TypeID)
		{
			found = true;
			element.PrivateComponentData = std::unique_ptr<PrivateComponentBase>(ptr);
			element.ResetOwner(entity);
			element.PrivateComponentData->Init();
		}
		i++;
	}
	if (!found)
	{
		_EntityPrivateComponentStorage->SetPrivateComponent(entity, id);
		_EntityInfos->at(entity.Index).PrivateComponentElements.emplace_back(name, id, std::unique_ptr<PrivateComponentBase>(ptr), entity);
	}
}

bool EntityManager::IsEntityArchetypeValid(const EntityArchetype& archetype)
{
	return archetype.IsNull() && _EntityComponentStorage->size() > archetype.Index;
}

Entity EntityManager::GetRoot(const Entity& entity)
{
	Entity retVal = entity;
	auto parent = GetParent(retVal);
	while (!parent.IsNull()) {
		retVal = parent;
		parent = GetParent(retVal);
	}
	return retVal;
}

Entity EntityManager::GetEntity(size_t index)
{
	if (index > 0 && index < _Entities->size()) return _Entities->at(index);
	return Entity();
}

void EntityManager::RemovePrivateComponent(const Entity& entity, size_t typeId)
{
	if (!entity.IsValid()) return;
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
}

EntityArchetype UniEngine::EntityManager::GetEntityArchetype(const Entity& entity)
{
	EntityArchetype retVal = EntityArchetype();
	if (!entity.IsValid()) return retVal;
	EntityInfo& info = _EntityInfos->at(entity.Index);
	retVal.Index = info.ArchetypeInfoIndex;
	return retVal;
}

void UniEngine::EntityManager::SetEnable(const Entity& entity, bool value) {
	if (!entity.IsValid()) return;
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
	
	for (const auto& i : _EntityInfos->at(entity.Index).Children) {
		SetEnable(i, value);
	}
}

void EntityManager::SetStatic(const Entity& entity, bool value)
{
	if (!entity.IsValid()) return;
	_EntityInfos->at(entity.Index).Static = value;
}

void EntityManager::SetEnableSingle(const Entity& entity, bool value)
{
	if (!entity.IsValid()) return;
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
}

bool UniEngine::EntityManager::IsEntityEnabled(const Entity& entity) {
	if (!entity.IsValid()) return false;
	return _EntityInfos->at(entity.Index).Enabled;
}

bool EntityManager::IsEntityStatic(const Entity& entity)
{
	if (!entity.IsValid()) return false;
	return _EntityInfos->at(entity.Index).Static;
}

bool UniEngine::EntityManager::IsEntityDeleted(size_t index)
{
	return _Entities->at(index).Version == 0;
}

bool EntityManager::IsEntityValid(const Entity& entity)
{
	return _Entities->at(entity.Index).Version == entity.Version;
}


EntityQuery UniEngine::EntityManager::CreateEntityQuery()
{
	EntityQuery retVal;
	retVal.Index = _EntityQueries->size();
	_EntityQueries->push_back(retVal);

	const EntityQueryInfo info;
	_EntityQueryInfos->push_back(info);
	RefreshEntityQueryInfos(retVal.Index);
	
	return retVal;
}

std::vector<EntityComponentStorage> UniEngine::EntityManager::UnsafeQueryStorage(EntityQuery entityQuery)
{
	if (entityQuery.IsNull()) return std::vector<EntityComponentStorage>();
	const size_t index = entityQuery.Index;
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return std::vector<EntityComponentStorage>();
	}
	return _EntityQueryInfos->at(index).QueriedStorage;
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

std::string EntityManager::GetEntityArchetypeName(const EntityArchetype& entityArchetype)
{
	return _CurrentAttachedWorldEntityStorage->EntityComponentStorage[entityArchetype.Index].ArchetypeInfo->Name;
}

void UniEngine::EntityManager::GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container)
{
	if (entityQuery.IsNull()) return;
	const size_t index = entityQuery.Index;
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return;
	}
	for (auto i : _EntityQueryInfos->at(index).QueriedStorage) {
		GetEntityStorage(i, container);
	}
}

void UniEngine::EntityQuery::ToEntityArray(std::vector<Entity>& container) const
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
	const size_t index = entityQuery.Index;
	if (_EntityQueries->at(index) != entityQuery) {
		Debug::Error("EntityQuery out of date!");
		return 0;
	}
	size_t retVal = 0;
	for (auto i : _EntityQueryInfos->at(index).QueriedStorage) {
		retVal += i.ArchetypeInfo->EntityAliveCount;
	}
	return retVal;
}

size_t UniEngine::EntityQuery::GetEntityAmount() const
{
	return EntityManager::GetEntityAmount(*this);
}
#pragma endregion

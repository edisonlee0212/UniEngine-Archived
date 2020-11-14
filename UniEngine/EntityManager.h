#pragma once
#include "UniEngineAPI.h"
#include "ManagerBase.h"
#include "Entity.h"
#include "PrivateComponentStorage.h"
#include "SharedComponentStorage.h"
#include "ThreadPool.h"
#include "Debug.h"
namespace UniEngine {
	class ThreadPool;
#pragma region EntityManager
	struct WorldEntityStorage {
		size_t Index;
		size_t ParentHierarchyVersion = 0;
		std::vector<Entity> Entities;
		std::vector<Entity> ParentRoots;
		std::vector<EntityInfo> EntityInfos;
		std::vector<EntityComponentStorage> EntityComponentStorage;
		SharedComponentStorage EntitySharedComponentStorage;
		PrivateComponentStorage EntityPrivateComponentStorage;
		std::vector<EntityQuery> EntityQueries;
		std::vector<EntityQueryInfo> EntityQueryInfos;
		std::queue<EntityQuery> EntityQueryPools;
	};
	struct ComponentCreateFunction
	{
		size_t ComponentSize;
		std::function<void(ComponentBase*)> Function;
	};
	struct ComponentDestroyFunction
	{
		size_t ComponentSize;
		std::function<void(ComponentBase*)> Function;
	};
	class UNIENGINE_API EntityManager : public ManagerBase {
		friend class PrivateComponentStorage;
		friend class SharedComponentStorage;

#pragma region Data Storage
		static std::vector<WorldEntityStorage*> _WorldEntityStorage;
		static WorldEntityStorage* _CurrentActivatedWorldEntityStorage;
		static std::vector<Entity>* _Entities;
		static std::vector<Entity>* _ParentRoots;
		static std::vector<EntityInfo>* _EntityInfos;
		static std::vector<EntityComponentStorage>* _EntityComponentStorage;
		static SharedComponentStorage* _EntitySharedComponentStorage;
		static PrivateComponentStorage* _EntityPrivateComponentStorage;
		static std::vector<EntityQuery>* _EntityQueries;
		static std::vector<EntityQueryInfo>* _EntityQueryInfos;
		static std::queue<EntityQuery>* _EntityQueryPools;
#pragma endregion
		//static std::map<size_t, ComponentCreateFunction> _ComponentCreationFunctionMap;
		//static std::map<size_t, ComponentDestroyFunction> _ComponentDestructionFunctionMap;
		template<typename T = ComponentBase>
		static bool CheckComponentTypes(T arg);
		template<typename T = ComponentBase, typename... Ts>
		static bool CheckComponentTypes(T arg, Ts... args);
		
		template<typename T = ComponentBase>
		static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg);
		template<typename T = ComponentBase, typename... Ts>
		static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		static std::vector<ComponentType> CollectComponentTypes(T arg, Ts... args);
		static void DeleteEntityInternal(Entity entity);
		static void RefreshEntityQueryInfos(size_t index);
#pragma region ForEach
		template<typename T1 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func, bool checkEnable = true);

#pragma endregion
		template<typename T = ComponentBase>
		static void GetComponentDataArrayStorage(EntityComponentStorage storage, std::vector<T>& container);
		static void GetEntityStorage(EntityComponentStorage storage, std::vector<Entity>& container);
		static size_t SwapEntity(EntityComponentStorage storage, size_t index1, size_t index2);

		friend struct EntityQuery;
		template<typename T = ComponentBase>
		static void GetComponentDataArray(EntityQuery entityQuery, std::vector<T>& container);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void GetComponentDataArray(EntityQuery entityQuery, std::vector<T1>& container, const std::function<bool(T2&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		static void GetComponentDataArray(EntityQuery entityQuery, std::vector<T1>& container, const std::function<bool(T2&, T3&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void GetComponentDataArray(EntityQuery entityQuery, T1 filter, std::vector<T2>& container);


		static void GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container);
		template<typename T1 = ComponentBase>
		static void GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container, const std::function<bool(Entity, T1&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container, const std::function<bool(Entity, T1&, T2&)>& filterFunc);
		template<typename T1 = ComponentBase>
		static void GetEntityArray(EntityQuery entityQuery, T1 filter, std::vector<Entity>& container);

		static size_t GetEntityAmount(EntityQuery entityQuery);
		friend struct Entity;
		//Enable or Disable an Entity. Note that the disable action will recursively disable the children of current entity. You are not allowed to enable an entity unless its parent(if exist) is enabled. 
		static void SetEnable(Entity entity, bool value);
		static bool IsEntityEnabled(Entity entity);

		static bool IsEntityDeleted(size_t index);

		//Unsafe zone, allow directly manipulation of entity data, which may result in data corruption.
		static std::vector<EntityComponentStorage> UnsafeQueryStorage(EntityQuery entityQuery);
		static ComponentDataChunkArray* UnsafeGetEntityComponentDataChunkArray(EntityArchetype entityArchetype);
		static std::vector<Entity>* GetAllEntitiesUnsafe();
		static std::vector<Entity>* GetParentRootsUnsafe();

		static void SetComponentData(Entity entity, size_t id, size_t size, ComponentBase* data);
		static ComponentBase* GetComponentDataPointer(Entity entity, size_t id);
	public:
		template <typename T>
		static const std::vector<Entity>* GetPrivateComponentOwnersList();
		/*
		template<typename T1 = ComponentBase>
		static void RegisterComponentDataCreator(const std::function<void(ComponentBase*)>& func);
		template<typename T1 = ComponentBase>
		static void RegisterComponentDataDestroyer(const std::function<void(ComponentBase*)>& func);
		*/
		static void ForEachComponentUnsafe(Entity entity, const std::function<void(ComponentType type, void* data)>& func);
		static void ForEachSharedComponent(Entity entity, const std::function<void(SharedComponentElement data)>& func);
		static void ForEachPrivateComponent(Entity entity, const std::function<void(PrivateComponentElement& data)>& func);

		static void ForEachEntityStorageUnsafe(const std::function<void(int i, EntityComponentStorage storage)>& func);
		static void GetAllEntities(std::vector<Entity>& target);

		static void SetWorld(World* world);
		template<typename T = ComponentBase, typename... Ts>
		static EntityArchetype CreateEntityArchetype(std::string name, T arg, Ts... args);

		static Entity CreateEntity(EntityArchetype archetype, std::string name = "");
		static void DeleteEntity(Entity entity);

		static std::string GetEntityName(Entity entity);

		static bool SetEntityName(Entity entity, std::string name);

		static void SetParent(Entity entity, Entity parent);
		static Entity GetParent(Entity entity);
		static std::vector<Entity> GetChildren(Entity entity);
		static size_t GetChildrenAmount(Entity entity);
		static void ForEachChild(Entity entity, const std::function<void(Entity child)>& func);

		static void RemoveChild(Entity entity, Entity parent);
		static void GetParentRoots(std::vector<Entity>* container);
		static size_t GetParentHierarchyVersion();


		template<typename T = ComponentBase>
		static void SetComponentData(Entity entity, T value);

		template<typename T = ComponentBase>
		static void SetComponentData(size_t index, T value);

		template<typename T = ComponentBase>
		static T GetComponentData(Entity entity);

		template<typename T = ComponentBase>
		static bool HasComponentData(Entity entity);

		template<typename T = ComponentBase>
		static T GetComponentData(size_t index);
		template<typename T = ComponentBase>
		static bool HasComponentData(size_t index);

		template <typename T = SharedComponentBase>
		static std::shared_ptr<T> GetSharedComponent(Entity entity);
		template <typename T = SharedComponentBase>
		static void SetSharedComponent(Entity entity, std::shared_ptr<T> value);
		template <typename T = SharedComponentBase>
		static bool RemoveSharedComponent(Entity entity);
		template <typename T = SharedComponentBase>
		static bool HasSharedComponent(Entity entity);

		template <typename T = PrivateComponentBase>
		static std::unique_ptr<T>* GetPrivateComponent(Entity entity);
		template <typename T = PrivateComponentBase>
		static void SetPrivateComponent(Entity entity, std::unique_ptr<T> value);
		template <typename T = PrivateComponentBase>
		static bool RemovePrivateComponent(Entity entity);
		template <typename T = PrivateComponentBase>
		static bool HasPrivateComponent(Entity entity);

		static bool RemovePrivateComponent(Entity entity, size_t typeId);
		
		template <typename T = SharedComponentBase>
		static std::vector<Entity>* GetSharedComponentEntities(std::shared_ptr<T> value);
		template <typename T = SharedComponentBase>
		static std::vector<std::shared_ptr<T>>* GetSharedComponentDataArray();

		static EntityArchetype GetEntityArchetype(Entity entity);

		static EntityQuery CreateEntityQuery();
		static void DeleteEntityQuery(EntityQuery entityQuery);
		template<typename T = ComponentBase, typename... Ts>
		static void SetEntityQueryAllFilters(EntityQuery entityQuery, T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		static void SetEntityQueryAnyFilters(EntityQuery entityQuery, T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		static void SetEntityQueryNoneFilters(EntityQuery entityQuery, T arg, Ts... args);


		template<typename T1 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func, bool checkEnable = true);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func, bool checkEnable = true);

		static void ForAllEntities(const std::function<void(int i, Entity entity)>& func);
		static void ForAllRootParent(const std::function<void(int i, Entity rootParent)>& func);
	};
#pragma endregion
#pragma region Functions
#pragma region Collectors

	template <typename T>
	bool EntityManager::CheckComponentTypes(T arg)
	{
		return std::is_standard_layout<T>::value;
	}

	template <typename T, typename ... Ts>
	bool EntityManager::CheckComponentTypes(T arg, Ts... args)
	{
		return std::is_standard_layout<T>::value && CheckComponentTypes(args...);
	}

	template<typename T>
	size_t EntityManager::CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg)
	{
		ComponentType type = typeof<T>();
		componentTypes->push_back(type);
		return type.Size;
	}

	template<typename T, typename ...Ts>
	size_t EntityManager::CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg, Ts ...args)
	{
		auto offset = CollectComponentTypes(componentTypes, args...);
		ComponentType type = typeof<T>();
		componentTypes->push_back(type);
		return type.Size + offset;
	}

	template<typename T, typename ...Ts>
	std::vector<ComponentType> EntityManager::CollectComponentTypes(T arg, Ts ...args)
	{
		std::vector<ComponentType> retVal = std::vector<ComponentType>();
		CollectComponentTypes(&retVal, arg, args...);
		std::sort(retVal.begin(), retVal.end(), ComponentTypeComparator);
		size_t offset = 0;
		ComponentType prev = retVal[0];
		//Erase duplicates
		for (size_t i = 1; i < retVal.size(); i++) {
			if (retVal[i] == prev) {
				retVal.erase(retVal.begin() + i);
				i--;
			}
			else {
				prev = retVal[i];
			}
		}
		for (size_t i = 0; i < retVal.size(); i++) {
			retVal[i].Offset = offset;
			offset += retVal[i].Size;
		}
		return retVal;
	}
#pragma endregion
#pragma region ForEachStorage
	template<typename T1>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*)>& func, bool checkEnable)
	{
		ComponentType targetType1 = typeof<T1>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
		}
		if (found1) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = entityCount / capacity;
			size_t remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*)>& func, bool checkEnable)
	{
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
		}

		if (found1 && found2) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = entityCount / capacity;
			size_t remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2, typename T3>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func, bool checkEnable) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.TypeID == targetType3.TypeID)
			{
				targetType3 = type;
				found3 = true;
			}
		}
		if (found1 && found2 && found3) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = entityCount / capacity;
			size_t remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2, typename T3, typename T4>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func, bool checkEnable) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		ComponentType targetType4 = typeof<T4>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.TypeID == targetType3.TypeID)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.TypeID == targetType4.TypeID)
			{
				targetType4 = type;
				found4 = true;
			}
		}
		if (found1 && found2 && found3 && found4) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = entityCount / capacity;
			size_t remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func, bool checkEnable) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		ComponentType targetType4 = typeof<T4>();
		ComponentType targetType5 = typeof<T5>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.TypeID == targetType3.TypeID)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.TypeID == targetType4.TypeID)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.TypeID == targetType5.TypeID)
			{
				targetType5 = type;
				found5 = true;
			}
		}
		if (found1 && found2 && found3 && found4 && found5) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = entityCount / capacity;
			size_t remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, remainder, checkEnable](int id)
						{
							for (int i = 0; i < remainder; i++) {
								int index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func, bool checkEnable) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		ComponentType targetType4 = typeof<T4>();
		ComponentType targetType5 = typeof<T5>();
		ComponentType targetType6 = typeof<T6>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		bool found6 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.TypeID == targetType3.TypeID)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.TypeID == targetType4.TypeID)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.TypeID == targetType5.TypeID)
			{
				targetType5 = type;
				found5 = true;
			}
			else if (type.TypeID == targetType6.TypeID)
			{
				targetType6 = type;
				found6 = true;
			}
		}
		if (found1 && found2 && found3 && found4 && found5 && found6) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = entityCount / capacity;
			size_t remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size),
									(T6*)((char*)data + targetType6.Offset * capacity + (i % capacity) * targetType6.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size),
									(T6*)((char*)data + targetType6.Offset * capacity + (i % capacity) * targetType6.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func, bool checkEnable) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		ComponentType targetType4 = typeof<T4>();
		ComponentType targetType5 = typeof<T5>();
		ComponentType targetType6 = typeof<T6>();
		ComponentType targetType7 = typeof<T7>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		bool found6 = false;
		bool found7 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.TypeID == targetType3.TypeID)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.TypeID == targetType4.TypeID)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.TypeID == targetType5.TypeID)
			{
				targetType5 = type;
				found5 = true;
			}
			else if (type.TypeID == targetType6.TypeID)
			{
				targetType6 = type;
				found6 = true;
			}
			else if (type.TypeID == targetType7.TypeID)
			{
				targetType7 = type;
				found7 = true;
			}
		}
		if (found1 && found2 && found3 && found4 && found5 && found6 && found7) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			int chunkAmount = entityCount / capacity;
			int remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size),
									(T6*)((char*)data + targetType6.Offset * capacity + (i % capacity) * targetType6.Size),
									(T7*)((char*)data + targetType7.Offset * capacity + (i % capacity) * targetType7.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size),
									(T6*)((char*)data + targetType6.Offset * capacity + (i % capacity) * targetType6.Size),
									(T7*)((char*)data + targetType7.Offset * capacity + (i % capacity) * targetType7.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func, bool checkEnable) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		ComponentType targetType4 = typeof<T4>();
		ComponentType targetType5 = typeof<T5>();
		ComponentType targetType6 = typeof<T6>();
		ComponentType targetType7 = typeof<T7>();
		ComponentType targetType8 = typeof<T8>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		bool found6 = false;
		bool found7 = false;
		bool found8 = false;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType1.TypeID)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.TypeID == targetType2.TypeID)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.TypeID == targetType3.TypeID)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.TypeID == targetType4.TypeID)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.TypeID == targetType5.TypeID)
			{
				targetType5 = type;
				found5 = true;
			}
			else if (type.TypeID == targetType6.TypeID)
			{
				targetType6 = type;
				found6 = true;
			}
			else if (type.TypeID == targetType7.TypeID)
			{
				targetType7 = type;
				found7 = true;
			}
			else if (type.TypeID == targetType8.TypeID)
			{
				targetType8 = type;
				found8 = true;
			}
		}
		if (found1 && found2 && found3 && found4 && found5 && found6 && found7 && found8) {
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			int chunkAmount = entityCount / capacity;
			int remainder = entityCount % capacity;
			ComponentDataChunkArray* chunkArray = storage.ChunkArray;
			std::vector<Entity>* entities = &chunkArray->Entities;
			std::vector<std::shared_future<void>> results;
			for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
				void* data = chunkArray->Chunks[chunkIndex].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8, checkEnable](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size),
									(T6*)((char*)data + targetType6.Offset * capacity + (i % capacity) * targetType6.Size),
									(T7*)((char*)data + targetType7.Offset * capacity + (i % capacity) * targetType7.Size),
									(T8*)((char*)data + targetType8.Offset * capacity + (i % capacity) * targetType8.Size)
								);
							}
						}
				).share());
			}
			if (remainder != 0) {
				void* data = chunkArray->Chunks[chunkAmount].Data;
				results.push_back(
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8, remainder, checkEnable](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (checkEnable && !entity.Enabled()) continue;
								func((int)index, entity,
									(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
									(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
									(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
									(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size),
									(T5*)((char*)data + targetType5.Offset * capacity + (i % capacity) * targetType5.Size),
									(T6*)((char*)data + targetType6.Offset * capacity + (i % capacity) * targetType6.Size),
									(T7*)((char*)data + targetType7.Offset * capacity + (i % capacity) * targetType7.Size),
									(T8*)((char*)data + targetType8.Offset * capacity + (i % capacity) * targetType8.Size)
								);
							}
						}
				).share());
			}
			for (size_t i = 0; i < results.size(); i++) {
				results[i].wait();
			}
		}
	}
#pragma endregion
#pragma region Others
	template<typename T>
	void EntityManager::GetComponentDataArrayStorage(EntityComponentStorage storage, std::vector<T>& container)
	{
		ComponentType targetType = typeof<T>();
		size_t entityCount = storage.ArchetypeInfo->EntityCount;
		for (const auto& type : storage.ArchetypeInfo->ComponentTypes)
		{
			if (type.TypeID == targetType.TypeID)
			{
				targetType = type;
				size_t amount = storage.ArchetypeInfo->EntityAliveCount;
				if (amount == 0) return;
				container.resize(container.size() + amount);
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				size_t chunkAmount = amount / capacity;
				size_t remainAmount = amount % capacity;
				for (size_t i = 0; i < chunkAmount; i++) {
					memcpy(&container.at(container.size() - remainAmount - capacity * (chunkAmount - i)), (void*)((char*)storage.ChunkArray->Chunks[i].Data + capacity * targetType.Offset), capacity * targetType.Size);
				}
				if (remainAmount > 0) memcpy(&container.at(container.size() - remainAmount), (void*)((char*)storage.ChunkArray->Chunks[chunkAmount].Data + capacity * targetType.Offset), remainAmount * targetType.Size);
			}
		}
	}

	template<typename T, typename ...Ts>
	inline EntityArchetype EntityManager::CreateEntityArchetype(std::string name, T arg, Ts ...args)
	{
		if(!CheckComponentTypes(arg, args...))
		{
			Debug::Error("CreateEntityArchetype failed: Standard Layout");
			return EntityArchetype();
		}
		EntityArchetypeInfo* info = new EntityArchetypeInfo();
		info->Name = name;
		info->EntityCount = 0;
		info->ComponentTypes = CollectComponentTypes(arg, args...);
		info->EntitySize = info->ComponentTypes.back().Offset + info->ComponentTypes.back().Size;
		info->ChunkCapacity = ARCHETYPECHUNK_SIZE / info->EntitySize;
		int duplicateIndex = -1;
		for (size_t i = 1; i < _EntityComponentStorage->size(); i++) {
			EntityArchetypeInfo* compareInfo = _EntityComponentStorage->at(i).ArchetypeInfo;
			if (info->ChunkCapacity != compareInfo->ChunkCapacity) continue;
			if (info->EntitySize != compareInfo->EntitySize) continue;
			bool typeCheck = true;

			for (size_t j = 0; j < info->ComponentTypes.size(); j++) {
				if (!compareInfo->HasType(info->ComponentTypes[j].TypeID)) typeCheck = false;
			}
			if (typeCheck) {
				duplicateIndex = compareInfo->Index;
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
#pragma endregion
#pragma region GetSetHas
	template<typename T>
	void EntityManager::SetComponentData(Entity entity, T value)
	{
		if (entity.IsNull()) return;
		EntityInfo& info = _EntityInfos->at(entity.Index);

		if (_Entities->at(entity.Index) == entity) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			bool found = false;
			for (const auto& type : chunkInfo->ComponentTypes)
			{
				if (type.TypeID == id)
				{
					chunk.SetData<T>((size_t)(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size), value);
					return;
				}
			}
			Debug::Log("ComponentData doesn't exist");
		}
		else {
			Debug::Error("Entity already deleted!");
		}
	}
	template<typename T>
	void EntityManager::SetComponentData(size_t index, T value)
	{
		if (index > _EntityInfos->size()) return;
		EntityInfo& info = _EntityInfos->at(index);

		if (_Entities->at(index).Version != 0) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			bool found = false;
			for (const auto& type : chunkInfo->ComponentTypes)
			{
				if (type.TypeID == id)
				{
					chunk.SetData<T>((size_t)(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size), value);
					return;
				}
			}
			Debug::Log("ComponentData doesn't exist");
		}
		else {
			Debug::Error("Entity already deleted!");
		}
	}
	template<typename T>
	T EntityManager::GetComponentData(Entity entity)
	{
		if (entity.IsNull()) return T();
		EntityInfo& info = _EntityInfos->at(entity.Index);
		if (_Entities->at(entity.Index) == entity) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			for (const auto& type : chunkInfo->ComponentTypes)
			{
				if (type.TypeID == id)
				{
					return chunk.GetData<T>((size_t)(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size));
				}
			}
			Debug::Log("ComponentData doesn't exist");
			return T();
		}
		else {
			Debug::Error("Entity already deleted!");
			return T();
		}
	}
	template<typename T>
	bool EntityManager::HasComponentData(Entity entity)
	{
		if (entity.IsNull()) return false;
		EntityInfo& info = _EntityInfos->at(entity.Index);
		if (_Entities->at(entity.Index) == entity) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			for (const auto& type : chunkInfo->ComponentTypes)
			{
				if (type.TypeID == id)
				{
					return true;
				}
			}
			return false;
		}
		Debug::Error("Entity already deleted!");
		return false;
	}
	template<typename T>
	T EntityManager::GetComponentData(size_t index)
	{
		if (index > _EntityInfos->size()) return T();
		EntityInfo& info = _EntityInfos->at(index);
		if (_Entities->at(index).Version != 0) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			for (const auto& type : chunkInfo->ComponentTypes)
			{
				if (type.TypeID == id)
				{
					return chunk.GetData<T>((size_t)(type.Offset * chunkInfo->ChunkCapacity + chunkPointer * type.Size));
				}
			}
			Debug::Log("ComponentData doesn't exist");
			return T();
		}
		else {
			Debug::Error("Entity already deleted!");
			return T();
		}
	}
	template<typename T>
	bool EntityManager::HasComponentData(size_t index)
	{
		if (index > _EntityInfos->size()) return false;
		EntityInfo& info = _EntityInfos->at(index);
		if (_Entities->at(index).Version != 0) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			for (const auto& type : chunkInfo->ComponentTypes)
			{
				if (type.TypeID == id)
				{
					return true;
				}
			}
			return false;
		}
		Debug::Error("Entity already deleted!");
		return false;
	}
	template<typename T>
	std::shared_ptr<T> EntityManager::GetSharedComponent(Entity entity)
	{
		if (entity.IsNull()) return nullptr;
		for (auto& element : _EntityInfos->at(entity.Index).SharedComponentElements)
		{
			if (element.TypeID == typeid(T).hash_code())
			{
				return std::dynamic_pointer_cast<T>(element.SharedComponentData);
			}
		}
		return nullptr;
	}
	template<typename T>
	void EntityManager::SetSharedComponent(Entity entity, std::shared_ptr<T> value)
	{
		if (entity.IsNull()) return;
		bool found = false;
		for (auto& element : _EntityInfos->at(entity.Index).SharedComponentElements)
		{
			if (element.TypeID == typeid(T).hash_code())
			{
				found = true;
				element.SharedComponentData = value;
			}
		}
		if (!found)
		{
			_EntityInfos->at(entity.Index).SharedComponentElements.push_back(SharedComponentElement(typeid(T).name(), typeid(T).hash_code(), value));
		}
		_EntitySharedComponentStorage->SetSharedComponent<T>(entity, value);
	}
	template<typename T>
	bool EntityManager::RemoveSharedComponent(Entity entity)
	{
		if (entity.IsNull()) return false;
		bool found = false;
		for (auto i = 0; i < _EntityInfos->at(entity.Index).SharedComponentElements.size(); i++)
		{
			if (_EntityInfos->at(entity.Index).SharedComponentElements[i].TypeID == typeid(T).hash_code())
			{
				found = true;
				_EntityInfos->at(entity.Index).SharedComponentElements.erase(_EntityInfos->at(entity.Index).SharedComponentElements.begin() + i);
			}
		}
		bool check = _EntitySharedComponentStorage->RemoveSharedComponent<T>(entity);
		if (found != check) Debug::Error("Error in RemoveSharedComponent!");
		return check;
	}
	template<typename T>
	bool EntityManager::HasSharedComponent(Entity entity)
	{
		if (entity.IsNull()) return false;
		for (auto& element : _EntityInfos->at(entity.Index).SharedComponentElements)
		{
			if (element.TypeID == typeid(T).hash_code())
			{
				return true;
			}
		}
		return false;
	}
	template <typename T>
	std::unique_ptr<T>* EntityManager::GetPrivateComponent(Entity entity)
	{
		if (entity.IsNull()) return nullptr;
		int i = 0;
		for (auto& element : _EntityInfos->at(entity.Index).PrivateComponentElements)
		{
			if (element.TypeID == typeid(T).hash_code())
			{
				return reinterpret_cast<std::unique_ptr<T>*>(&element.PrivateComponentData);
			}
			i++;
		}
		return nullptr;
	}
	template <typename T>
	void EntityManager::SetPrivateComponent(Entity entity, std::unique_ptr<T> value)
	{
		if (entity.IsNull()) return;
		bool found = false;
		size_t i = 0;
		for (auto& element : _EntityInfos->at(entity.Index).PrivateComponentElements)
		{
			if (element.TypeID == typeid(T).hash_code())
			{
				found = true;
				element.PrivateComponentData = std::move(value);
				element.ResetOwner(entity);
				element.PrivateComponentData->Init();
			}
			i++;
		}
		if (!found)
		{
			_EntityPrivateComponentStorage->SetPrivateComponent<T>(entity);
			_EntityInfos->at(entity.Index).PrivateComponentElements.push_back(PrivateComponentElement(typeid(T).name(), typeid(T).hash_code(), std::move(value), entity));
		}
		
	}
	template <typename T>
	bool EntityManager::RemovePrivateComponent(Entity entity)
	{
		if (entity.IsNull()) return false;
		bool found = false;
		for (auto i = 0; i < _EntityInfos->at(entity.Index).PrivateComponentElements.size(); i++)
		{
			if (_EntityInfos->at(entity.Index).PrivateComponentElements[i].TypeID == typeid(T).hash_code())
			{
				found = true;
				_EntityPrivateComponentStorage->RemovePrivateComponent<T>(entity);
				_EntityInfos->at(entity.Index).PrivateComponentElements.erase(_EntityInfos->at(entity.Index).PrivateComponentElements.begin() + i);
			}
		}
		
		return found;
	}
	template <typename T>
	bool EntityManager::HasPrivateComponent(Entity entity)
	{

		if (entity.IsNull()) return false;
		for (auto& element : _EntityInfos->at(entity.Index).PrivateComponentElements)
		{
			if (element.TypeID == typeid(T).hash_code())
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	std::vector<Entity>* EntityManager::GetSharedComponentEntities(std::shared_ptr<T> value)
	{
		return _EntitySharedComponentStorage->GetOwnersList<T>(value);
	}
#pragma endregion
#pragma region SharedQuery
	template<typename T>
	std::vector<std::shared_ptr<T>>* EntityManager::GetSharedComponentDataArray()
	{
		return _EntitySharedComponentStorage->GetSCList<T>();
	}

	template<typename T, typename ...Ts>
	void EntityManager::SetEntityQueryAllFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
		_EntityQueryInfos->at(index).AllComponentTypes = CollectComponentTypes(arg, args...);
		RefreshEntityQueryInfos(index);
	}

	template<typename T, typename ...Ts>
	inline void EntityManager::SetEntityQueryAnyFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
		_EntityQueryInfos->at(index).AnyComponentTypes = CollectComponentTypes(arg, args...);
		RefreshEntityQueryInfos(index);
	}

	template<typename T, typename ...Ts>
	inline void EntityManager::SetEntityQueryNoneFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
		_EntityQueryInfos->at(index).NoneComponentTypes = CollectComponentTypes(arg, args...);
		RefreshEntityQueryInfos(index);
	}
#pragma endregion
#pragma region For Each
	template<typename T1>
	inline void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*)>& func, bool checkEnable)
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func, bool checkEnable) {
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			ForEachStorage(i, func, checkEnable);
		}
	}
#pragma endregion
	template<typename T>
	void EntityManager::GetComponentDataArray(EntityQuery entityQuery, std::vector<T>& container)
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
		for (const auto& i : _EntityQueryInfos->at(index).QueriedStorages) {
			GetComponentDataArrayStorage(i, container);
		}
	}

	template <typename T1, typename T2>
	void EntityManager::GetComponentDataArray(EntityQuery entityQuery, std::vector<T1>& container,
		const std::function<bool(T2&)>& filterFunc)
	{
		std::vector<T2> componentDataList;
		std::vector<T1> targetDataList;
		GetComponentDataArray(entityQuery, componentDataList);
		GetComponentDataArray(entityQuery, targetDataList);
		if (targetDataList.size() != componentDataList.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = componentDataList.size();
		std::vector<std::vector<T1>> collectedDataLists;
		for (int i = 0; i < _ThreadPool->Size(); i++) {
			collectedDataLists.push_back(std::vector<T1>());
		}
		for (int i = 0; i < collectedDataLists.size(); i++) {
			std::vector<T1>* collectedDataList = &collectedDataLists[i];
			futures.push_back(_ThreadPool->Push([&targetDataList, &componentDataList, size, collectedDataList, i, filterFunc](int id) {
				for (int j = 0; j < size / 8; j++) {
					if (filterFunc(componentDataList[j * 8 + i])) {
						collectedDataList->push_back(targetDataList[j * 8 + i]);
					}
				}
				}).share());
		}
		for (auto i : futures) i.wait();
		for (int i = 0; i < collectedDataLists.size(); i++) {
			auto listSize = collectedDataLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T1));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(componentDataList[size - remainder + i])) {
				container.push_back(targetDataList[size - remainder + i]);
			}
		}
	}

	template <typename T1, typename T2, typename T3>
	void EntityManager::GetComponentDataArray(EntityQuery entityQuery, std::vector<T1>& container,
		const std::function<bool(T2&, T3&)>& filterFunc)
	{
		std::vector<T3> componentDataList2;
		std::vector<T2> componentDataList1;
		std::vector<T1> targetDataList;
		GetComponentDataArray(entityQuery, componentDataList2);
		GetComponentDataArray(entityQuery, componentDataList1);
		GetComponentDataArray(entityQuery, targetDataList);
		if (targetDataList.size() != componentDataList1.size() || componentDataList1.size() != componentDataList2.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = componentDataList1.size();
		std::vector<std::vector<T1>> collectedDataLists;
		for (int i = 0; i < _ThreadPool->Size(); i++) {
			collectedDataLists.push_back(std::vector<T1>());
		}
		for (int i = 0; i < collectedDataLists.size(); i++) {
			std::vector<T1>* collectedDataList = &collectedDataLists[i];
			futures.push_back(_ThreadPool->Push([&targetDataList, &componentDataList1, &componentDataList2, size, collectedDataList, i, filterFunc](int id) {
				for (int j = 0; j < size / 8; j++) {
					if (filterFunc(componentDataList1[j * 8 + i], componentDataList2[j * 8 + i])) {
						collectedDataList->push_back(targetDataList[j * 8 + i]);
					}
				}
				}).share());
		}
		for (auto i : futures) i.wait();
		for (int i = 0; i < collectedDataLists.size(); i++) {
			auto listSize = collectedDataLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T1));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(componentDataList1[size - remainder + i], componentDataList2[size - remainder + i])) {
				container.push_back(targetDataList[size - remainder + i]);
			}
		}
	}

	template<typename T1, typename T2>
	void EntityManager::GetComponentDataArray(EntityQuery entityQuery, T1 filter, std::vector<T2>& container)
	{
		std::vector<T1> componentDataList;
		std::vector<T2> targetDataList;
		GetComponentDataArray(entityQuery, componentDataList);
		GetComponentDataArray(entityQuery, targetDataList);
		if (targetDataList.size() != componentDataList.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = componentDataList.size();
		std::vector<std::vector<T2>> collectedDataLists;
		for (int i = 0; i < _ThreadPool->Size(); i++) {
			collectedDataLists.push_back(std::vector<T2>());
		}
		for (int i = 0; i < collectedDataLists.size(); i++) {
			std::vector<T2>* collectedDataList = &collectedDataLists[i];
			futures.push_back(_ThreadPool->Push([&targetDataList, &componentDataList, size, filter, collectedDataList, i](int id) {
				for (int j = 0; j < size / 8; j++) {
					if (filter == componentDataList[j * 8 + i]) {
						collectedDataList->push_back(targetDataList[j * 8 + i]);
					}
				}
				}).share());
		}
		for (auto i : futures) i.wait();
		for (int i = 0; i < collectedDataLists.size(); i++) {
			auto listSize = collectedDataLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T2));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filter == componentDataList[size - remainder + i]) {
				container.push_back(targetDataList[size - remainder + i]);
			}
		}
	}

	template <typename T1>
	void EntityManager::GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container,
		const std::function<bool(Entity, T1&)>& filterFunc)
	{
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList;
		GetEntityArray(entityQuery, allEntities);
		GetComponentDataArray(entityQuery, componentDataList);
		if (allEntities.size() != componentDataList.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = allEntities.size();
		std::vector<std::vector<Entity>> collectedEntityLists;
		for (int i = 0; i < _ThreadPool->Size(); i++) {
			collectedEntityLists.push_back(std::vector<Entity>());
		}
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			std::vector<Entity>* collectedEntityList = &collectedEntityLists[i];
			futures.push_back(_ThreadPool->Push([&allEntities, &componentDataList, size, collectedEntityList, i, filterFunc](int id) {
				for (int j = 0; j < size / 8; j++) {
					if (filterFunc(allEntities[j * 8 + i], componentDataList[j * 8 + i])) {
						collectedEntityList->push_back(allEntities[j * 8 + i]);
					}
				}
				}).share());
		}
		for (auto i : futures) i.wait();
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			auto listSize = collectedEntityLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(allEntities[size - remainder + i], componentDataList[size - remainder + i])) {
				container.push_back(allEntities[size - remainder + i]);
			}
		}
	}

	template <typename T1, typename T2>
	void EntityManager::GetEntityArray(EntityQuery entityQuery, std::vector<Entity>& container,
		const std::function<bool(Entity, T1&, T2&)>& filterFunc)
	{
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList1;
		std::vector<T2> componentDataList2;
		GetEntityArray(entityQuery, allEntities);
		GetComponentDataArray(entityQuery, componentDataList1);
		GetComponentDataArray(entityQuery, componentDataList2);
		if (allEntities.size() != componentDataList1.size() || componentDataList1.size() != componentDataList2.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = allEntities.size();
		std::vector<std::vector<Entity>> collectedEntityLists;
		for (int i = 0; i < _ThreadPool->Size(); i++) {
			collectedEntityLists.push_back(std::vector<Entity>());
		}
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			std::vector<Entity>* collectedEntityList = &collectedEntityLists[i];
			futures.push_back(_ThreadPool->Push([&allEntities, &componentDataList1, &componentDataList2, size, collectedEntityList, i, filterFunc](int id) {
				for (int j = 0; j < size / 8; j++) {
					if (filterFunc(allEntities[j * 8 + i], componentDataList1[j * 8 + i], componentDataList2[j * 8 + i])) {
						collectedEntityList->push_back(allEntities[j * 8 + i]);
					}
				}
				}).share());
		}
		for (auto i : futures) i.wait();
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			auto listSize = collectedEntityLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(allEntities[size - remainder + i], componentDataList1[size - remainder + i], componentDataList2[size - remainder + i])) {
				container.push_back(allEntities[size - remainder + i]);
			}
		}
	}


	template<typename T1>
	void EntityManager::GetEntityArray(EntityQuery entityQuery, T1 filter, std::vector<Entity>& container)
	{
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList;
		GetEntityArray(entityQuery, allEntities);
		GetComponentDataArray(entityQuery, componentDataList);
		std::vector<std::shared_future<void>> futures;
		size_t size = allEntities.size();
		std::vector<std::vector<Entity>> collectedEntityLists;
		for (int i = 0; i < _ThreadPool->Size(); i++) {
			collectedEntityLists.push_back(std::vector<Entity>());
		}
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			std::vector<Entity>* collectedEntityList = &collectedEntityLists[i];
			futures.push_back(_ThreadPool->Push([&allEntities, &componentDataList, size, filter, collectedEntityList, i](int id) {
				for (int j = 0; j < size / 8; j++) {
					if (filter == componentDataList[j * 8 + i]) {
						collectedEntityList->push_back(allEntities[j * 8 + i]);
					}
				}
				}).share());
		}
		for (auto i : futures) i.wait();
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			auto listSize = collectedEntityLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filter == componentDataList[size - remainder + i]) {
				container.push_back(allEntities[size - remainder + i]);
			}
		}
	}

	template <typename T>
	const std::vector<Entity>* EntityManager::GetPrivateComponentOwnersList()
	{
		return _EntityPrivateComponentStorage->GetOwnersList<T>();
	}
	/*
	template <typename T1>
	void EntityManager::RegisterComponentDataCreator(const std::function<void(ComponentBase*)>& func)
	{
		ComponentCreateFunction ins;
		ins.ComponentSize = sizeof(T1);
		ins.Function = func;
		_ComponentCreationFunctionMap.insert_or_assign(typeid(T1).hash_code(), ins);
	}

	template <typename T1>
	void EntityManager::RegisterComponentDataDestroyer(const std::function<void(ComponentBase*)>& func)
	{
		ComponentDestroyFunction ins;
		ins.ComponentSize = sizeof(T1);
		ins.Function = func;
		_ComponentDestructionFunctionMap.insert_or_assign(typeid(T1).hash_code(), ins);
	}
	*/
	template <typename T>
	void Entity::SetComponentData(T value)
	{
		EntityManager::SetComponentData(*this, value);
	}

	template <typename T>
	T Entity::GetComponentData()
	{
		return EntityManager::GetComponentData<T>(*this);
	}

	template <typename T>
	bool Entity::HasComponentData()
	{
		return EntityManager::HasComponentData<T>(*this);
	}

	template <typename T>
	std::shared_ptr<T> Entity::GetSharedComponent()
	{
		return std::move(EntityManager::GetSharedComponent<T>(*this));
	}

	template <typename T>
	void Entity::SetSharedComponent(std::shared_ptr<T> value)
	{
		EntityManager::SetSharedComponent(*this, value);
	}

	template <typename T>
	bool Entity::RemoveSharedComponent()
	{
		return EntityManager::RemoveSharedComponent<T>();
	}

	template <typename T>
	bool Entity::HasSharedComponent()
	{
		return EntityManager::HasSharedComponent<T>();
	}

	template <typename T>
	void Entity::SetPrivateComponent(std::unique_ptr<T> value)
	{
		EntityManager::SetPrivateComponent(*this, std::move(value));
	}

	template <typename T>
	bool Entity::RemovePrivateComponent()
	{
		return EntityManager::RemovePrivateComponent<T>();
	}

	template <typename T>
	bool Entity::HasPrivateComponent() const
	{
		return EntityManager::HasPrivateComponent<T>(*this);
	}

	template <typename T>
	std::unique_ptr<T>* Entity::GetPrivateComponent()
	{
		return EntityManager::GetPrivateComponent<T>(*this);
	}

	template<typename T1>
	void EntityQuery::ToComponentDataArray(std::vector<T1>& container)
	{
		EntityManager::GetComponentDataArray<T1>(*this, container);
	}

	template <typename T1, typename T2>
	void EntityQuery::ToComponentDataArray(std::vector<T1>& container,
		const std::function<bool(T2&)>& filterFunc)
	{
		EntityManager::GetComponentDataArray(*this, container, filterFunc);
	}

	template <typename T1, typename T2, typename T3>
	void EntityQuery::ToComponentDataArray(std::vector<T1>& container,
		const std::function<bool(T2&, T3&)>& filterFunc)
	{
		EntityManager::GetComponentDataArray(*this, container, filterFunc);
	}

	template<typename T1, typename T2>
	void EntityQuery::ToComponentDataArray(T1 filter, std::vector<T2>& container)
	{
		EntityManager::GetComponentDataArray(*this, filter, container);
	}
	template<typename T1>
	void EntityQuery::ToEntityArray(T1 filter, std::vector<Entity>& container)
	{
		EntityManager::GetEntityArray(*this, filter, container);
	}

	template <typename T1>
	void EntityQuery::ToEntityArray(std::vector<Entity>& container, const std::function<bool(Entity, T1&)>& filterFunc)
	{
		EntityManager::GetEntityArray<T1>(*this, container, filterFunc);
	}
#pragma endregion

}
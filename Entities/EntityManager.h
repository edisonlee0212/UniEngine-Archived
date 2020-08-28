#pragma once
#include "ManagerBase.h"
#include "Entity.h"
#include "SharedComponentStorage.h"
#include "World.h"
namespace UniEngine {
#pragma region EntityManager
	struct WorldEntityStorage {
		size_t Index;
		size_t ParentHierarchyVersion = 0;
		std::vector<Entity> Entities;
		std::vector<Entity> ParentRoots;
		std::vector<EntityInfo> EntityInfos;
		//std::vector<std::queue<Entity>> EntityPool;
		std::vector<EntityComponentStorage> EntityComponentStorage;
		SharedComponentStorage EntitySharedComponentStorage;

		std::vector<EntityQuery> EntityQueries;
		std::vector<EntityQueryInfo> EntityQueryInfos;
		std::queue<EntityQuery> EntityQueryPools;
	};
	class ENTITIES_API EntityManager : public ManagerBase {
#pragma region Data Storage
		static std::vector<WorldEntityStorage*> _WorldEntityStorage;
		static WorldEntityStorage* _CurrentActivitedWorldEntityStorage;
		static std::vector<Entity>* _Entities;
		static std::vector<Entity>* _ParentRoots;
		static std::vector<EntityInfo>* _EntityInfos;
		static std::vector<EntityComponentStorage>* _EntityComponentStorage;
		//static std::vector<std::queue<Entity>>* _EntityPool;
		static SharedComponentStorage* _EntitySharedComponentStorage;
		static std::vector<EntityQuery>* _EntityQueries;
		static std::vector<EntityQueryInfo>* _EntityQueryInfos;
		static std::queue<EntityQuery>* _EntityQueryPools;
#pragma endregion

		static ThreadPool* _ThreadPool;
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
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
		static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func);

#pragma endregion
		template<typename T = ComponentBase>
		static void GetComponentDataArrayStorage(EntityComponentStorage storage, std::vector<T>* container);
		static void GetEntityStorage(EntityComponentStorage storage, std::vector<Entity>* container);
		static size_t SwapEntity(EntityComponentStorage storage, size_t index1, size_t index2);

		friend struct EntityQuery;
		template<typename T = ComponentBase>
		static void GetComponentDataArray(EntityQuery entityQuery, std::vector<T>* container);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void GetComponentDataArray(EntityQuery entityQuery, T1 filter, std::vector<T2>* container);
		static void GetEntityArray(EntityQuery entityQuery, std::vector<Entity>* container);
		template<typename T1 = ComponentBase>
		static void GetEntityArray(EntityQuery entityQuery, T1 filter, std::vector<Entity>* container);

		static size_t GetEntityAmount(EntityQuery entityQuery);
		friend struct Entity;
		//Enable or Disable an Entity. Note that the disable action will recursively disable the children of current entity. You are not allowed to enable an entity unless its parent(if exist) is enabled. 
		static void SetEnable(Entity entity, bool value);
		static bool IsEntityEnabled(Entity entity);

		static bool IsEntityDeleted(size_t index);

		//Unsafe zone, allow directly manipulation of entity data, which may result in data corruption.
		static std::vector<EntityComponentStorage> UnsafeQueryStorages(EntityQuery entityQuery);
		static ComponentDataChunkArray* UnsafeGetEntityComponentDataChunkArray(EntityArchetype entityArchetype);
		static std::vector<Entity>* GetAllEntitiesUnsafe();
		static std::vector<Entity>* GetParentRootsUnsafe();
	public:
		static void ForEachComponentUnsafe(Entity entity, const std::function<void(ComponentType type, void* data)>& func);
		static void ForEachEntityStorageUnsafe(const std::function<void(int i, EntityComponentStorage storage)>& func);


		static void Init(ThreadPool* threadPool);

		static void GetAllEntities(std::vector<Entity>* target);
		
		static void SetThreadPool(ThreadPool* pool);
		static void SetWorld(World* world);
		template<typename T = ComponentBase, typename... Ts>
		static EntityArchetype CreateEntityArchetype(std::string name, T arg, Ts... args);

		static Entity CreateEntity(EntityArchetype archetype);
		static void DeleteEntity(Entity entity);

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
		static T* GetSharedComponent(Entity entity);
		template <typename T = SharedComponentBase>
		static void SetSharedComponent(Entity entity, T* value);
		template <typename T = SharedComponentBase>
		static bool RemoveSharedComponent(Entity entity);
		template <typename T = SharedComponentBase>
		static bool HasSharedComponent(Entity entity);


		template <typename T = SharedComponentBase>
		static std::vector<Entity>* GetSharedComponentEntities(T* value);
		template <typename T = SharedComponentBase>
		static std::vector<T*>* GetSharedComponentDataArray();

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
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
		static void ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func);

		static void ForAllEntities(const std::function<void(int i, Entity entity)>& func);
		static void ForAllRootParent(const std::function<void(int i, Entity rootParent)>& func);
	};
#pragma endregion
#pragma region Functions
#pragma region Collectors
	template<typename T>
	inline size_t EntityManager::CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg)
	{
		ComponentType type = typeof<T>();
		componentTypes->push_back(type);
		return type.Size;
	}

	template<typename T, typename ...Ts>
	inline size_t EntityManager::CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg, Ts ...args)
	{
		auto offset = CollectComponentTypes(componentTypes, args...);
		ComponentType type = typeof<T>();
		componentTypes->push_back(type);
		return type.Size + offset;
	}

	template<typename T, typename ...Ts>
	inline std::vector<ComponentType> EntityManager::CollectComponentTypes(T arg, Ts ...args)
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
	inline void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*)>& func)
	{
		ComponentType targetType1 = typeof<T1>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	inline void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*)>& func)
	{
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
		}
		auto search3 = storage.ArchetypeInfo->ComponentTypes.find(targetType3.TypeID);
		if (search3 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType3 = search3->second;
			found3 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func) {
		ComponentType targetType1 = typeof<T1>();
		ComponentType targetType2 = typeof<T2>();
		ComponentType targetType3 = typeof<T3>();
		ComponentType targetType4 = typeof<T4>();
		size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
		}
		auto search3 = storage.ArchetypeInfo->ComponentTypes.find(targetType3.TypeID);
		if (search3 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType3 = search3->second;
			found3 = true;
		}
		auto search4 = storage.ArchetypeInfo->ComponentTypes.find(targetType4.TypeID);
		if (search4 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType4 = search4->second;
			found4 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func) {
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
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
		}
		auto search3 = storage.ArchetypeInfo->ComponentTypes.find(targetType3.TypeID);
		if (search3 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType3 = search3->second;
			found3 = true;
		}
		auto search4 = storage.ArchetypeInfo->ComponentTypes.find(targetType4.TypeID);
		if (search4 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType4 = search4->second;
			found4 = true;
		}
		auto search5 = storage.ArchetypeInfo->ComponentTypes.find(targetType5.TypeID);
		if (search5 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType5 = search5->second;
			found5 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, remainder](int id)
						{
							for (int i = 0; i < remainder; i++) {
								int index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func) {
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
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
		}
		auto search3 = storage.ArchetypeInfo->ComponentTypes.find(targetType3.TypeID);
		if (search3 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType3 = search3->second;
			found3 = true;
		}
		auto search4 = storage.ArchetypeInfo->ComponentTypes.find(targetType4.TypeID);
		if (search4 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType4 = search4->second;
			found4 = true;
		}
		auto search5 = storage.ArchetypeInfo->ComponentTypes.find(targetType5.TypeID);
		if (search5 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType5 = search5->second;
			found5 = true;
		}
		auto search6 = storage.ArchetypeInfo->ComponentTypes.find(targetType6.TypeID);
		if (search6 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType6 = search6->second;
			found6 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func) {
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
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
		}
		auto search3 = storage.ArchetypeInfo->ComponentTypes.find(targetType3.TypeID);
		if (search3 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType3 = search3->second;
			found3 = true;
		}
		auto search4 = storage.ArchetypeInfo->ComponentTypes.find(targetType4.TypeID);
		if (search4 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType4 = search4->second;
			found4 = true;
		}
		auto search5 = storage.ArchetypeInfo->ComponentTypes.find(targetType5.TypeID);
		if (search5 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType5 = search5->second;
			found5 = true;
		}
		auto search6 = storage.ArchetypeInfo->ComponentTypes.find(targetType6.TypeID);
		if (search6 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType6 = search6->second;
			found6 = true;
		}
		auto search7 = storage.ArchetypeInfo->ComponentTypes.find(targetType7.TypeID);
		if (search7 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType7 = search7->second;
			found7 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func) {
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
		auto search1 = storage.ArchetypeInfo->ComponentTypes.find(targetType1.TypeID);
		if (search1 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType1 = search1->second;
			found1 = true;
		}
		auto search2 = storage.ArchetypeInfo->ComponentTypes.find(targetType2.TypeID);
		if (search2 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType2 = search2->second;
			found2 = true;
		}
		auto search3 = storage.ArchetypeInfo->ComponentTypes.find(targetType3.TypeID);
		if (search3 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType3 = search3->second;
			found3 = true;
		}
		auto search4 = storage.ArchetypeInfo->ComponentTypes.find(targetType4.TypeID);
		if (search4 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType4 = search4->second;
			found4 = true;
		}
		auto search5 = storage.ArchetypeInfo->ComponentTypes.find(targetType5.TypeID);
		if (search5 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType5 = search5->second;
			found5 = true;
		}
		auto search6 = storage.ArchetypeInfo->ComponentTypes.find(targetType6.TypeID);
		if (search6 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType6 = search6->second;
			found6 = true;
		}
		auto search7 = storage.ArchetypeInfo->ComponentTypes.find(targetType7.TypeID);
		if (search7 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType7 = search7->second;
			found7 = true;
		}
		auto search8 = storage.ArchetypeInfo->ComponentTypes.find(targetType8.TypeID);
		if (search8 != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType8 = search8->second;
			found8 = true;
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
					_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8](int id)
						{
							for (size_t i = 0; i < capacity; i++) {
								size_t index = i + chunkIndex * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
					_ThreadPool->Push([entities, capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8, remainder](int id)
						{
							for (size_t i = 0; i < remainder; i++) {
								size_t index = i + chunkAmount * capacity;
								Entity entity = entities->at(index);
								if (!entity.Enabled()) continue;
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
	inline void EntityManager::GetComponentDataArrayStorage(EntityComponentStorage storage, std::vector<T>* container)
	{
		ComponentType targetType = typeof<T>();
		size_t entityCount = storage.ArchetypeInfo->EntityCount;
		auto search = storage.ArchetypeInfo->ComponentTypes.find(targetType.TypeID);
		if (search != storage.ArchetypeInfo->ComponentTypes.end()) {
			targetType = search->second;
			size_t amount = storage.ArchetypeInfo->EntityAliveCount;
			if (amount == 0) return;
			container->resize(container->size() + amount);
			size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
			size_t chunkAmount = amount / capacity;
			size_t remainAmount = amount % capacity;
			for (size_t i = 0; i < chunkAmount; i++) {
				memcpy(&container->at(container->size() - remainAmount - capacity * (chunkAmount - i)), (void*)((char*)storage.ChunkArray->Chunks[i].Data + capacity * targetType.Offset), capacity * targetType.Size);
			}
			if (remainAmount > 0) memcpy(&container->at(container->size() - remainAmount), (void*)((char*)storage.ChunkArray->Chunks[chunkAmount].Data + capacity * targetType.Offset), remainAmount * targetType.Size);
		}
	}

	template<typename T, typename ...Ts>
	inline EntityArchetype EntityManager::CreateEntityArchetype(std::string name, T arg, Ts ...args)
	{
		EntityArchetypeInfo* info = new EntityArchetypeInfo();
		info->Name = name;
		info->EntityCount = 0;
		std::vector<ComponentType> componentLists = CollectComponentTypes(arg, args...);
		info->EntitySize = componentLists.back().Offset + componentLists.back().Size;
		for (const auto& i : componentLists) info->ComponentTypes.insert({ i.TypeID, i });
		info->ChunkCapacity = ARCHETYPECHUNK_SIZE / info->EntitySize;
		int duplicateIndex = -1;
		for (size_t i = 1; i < _EntityComponentStorage->size(); i++) {
			EntityArchetypeInfo* compareInfo = _EntityComponentStorage->at(i).ArchetypeInfo;
			if (info->ChunkCapacity != compareInfo->ChunkCapacity) continue;
			if (info->EntitySize != compareInfo->EntitySize) continue;
			bool typeCheck = true;
			for (size_t j = 0; j < componentLists.size(); j++) {
				auto search = compareInfo->ComponentTypes.find(componentLists[j].TypeID);
				if (search == compareInfo->ComponentTypes.end()) typeCheck = false;
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
	inline void EntityManager::SetComponentData(Entity entity, T value)
	{
		if (entity.IsNull()) return;
		EntityInfo info;
		info = _EntityInfos->at(entity.Index);

		if (_Entities->at(entity.Index) == entity) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			auto search = chunkInfo->ComponentTypes.find(id);
			if (search != chunkInfo->ComponentTypes.end()) {
				chunk.SetData<T>((size_t)(search->second.Offset * chunkInfo->ChunkCapacity + chunkPointer * search->second.Size), value);
			}
			else {
				Debug::Log("ComponentData doesn't exist");
				return;
			}
		}
		else {
			Debug::Error("Entity already deleted!");
			return;
		}
	}
	template<typename T>
	inline void EntityManager::SetComponentData(size_t index, T value)
	{
		if (index > _EntityInfos->size()) return;
		EntityInfo info;
		info = _EntityInfos->at(index);

		if (_Entities->at(index).Version != 0) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			auto search = chunkInfo->ComponentTypes.find(id);
			if (search != chunkInfo->ComponentTypes.end()) {
				chunk.SetData<T>((size_t)(search->second.Offset * chunkInfo->ChunkCapacity + chunkPointer * search->second.Size), value);
			}
			else {
				Debug::Log("ComponentData doesn't exist");
				return;
			}
		}
		else {
			Debug::Error("Entity already deleted!");
			return;
		}
	}
	template<typename T>
	inline T EntityManager::GetComponentData(Entity entity)
	{
		if (entity.IsNull()) return T();
		EntityInfo info = _EntityInfos->at(entity.Index);
		if (_Entities->at(entity.Index) == entity) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			auto search = chunkInfo->ComponentTypes.find(id);
			if (search != chunkInfo->ComponentTypes.end()) {
				return chunk.GetData<T>((size_t)(search->second.Offset * chunkInfo->ChunkCapacity + chunkPointer * search->second.Size));
			}
			else {
				return T();
			}
		}
		else {
			Debug::Error("Entity already deleted!");
			return T();
		}
	}
	template<typename T>
	inline bool EntityManager::HasComponentData(Entity entity)
	{
		if (entity.IsNull()) return false;
		EntityInfo info = _EntityInfos->at(entity.Index);
		if (_Entities->at(entity.Index) == entity) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			auto search = chunkInfo->ComponentTypes.find(id);
			return search != chunkInfo->ComponentTypes.end();
		}
		else {
			Debug::Error("Entity already deleted!");
			return false;
		}
	}
	template<typename T>
	inline T EntityManager::GetComponentData(size_t index)
	{
		if (index > _EntityInfos->size()) return T();
		EntityInfo info = _EntityInfos->at(index);
		if (_Entities->at(index).Version != 0) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			auto search = chunkInfo->ComponentTypes.find(id);
			if (search != chunkInfo->ComponentTypes.end()) {
				return chunk.GetData<T>((size_t)(search->second.Offset * chunkInfo->ChunkCapacity + chunkPointer * search->second.Size));
			}
			else {
				return T();
			}
		}
		else {
			Debug::Error("Entity already deleted!");
			return T();
		}
	}
	template<typename T>
	inline bool EntityManager::HasComponentData(size_t index)
	{
		if (index > _EntityInfos->size()) return false;
		EntityInfo info = _EntityInfos->at(index);
		if (_Entities->at(index).Version != 0) {
			EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
			size_t chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
			size_t chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
			ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
			size_t id = typeid(T).hash_code();
			auto search = chunkInfo->ComponentTypes.find(id);
			return search != chunkInfo->ComponentTypes.end();
		}
		else {
			Debug::Error("Entity already deleted!");
			return false;
		}
	}
	template<typename T>
	inline T* EntityManager::GetSharedComponent(Entity entity)
	{
		if (entity.IsNull()) return nullptr;
		return _EntitySharedComponentStorage->GetSharedComponent<T>(entity);
	}
	template<typename T>
	inline void EntityManager::SetSharedComponent(Entity entity, T* value)
	{
		if (entity.IsNull()) return;
		_EntitySharedComponentStorage->SetSharedComponent<T>(entity, value);
	}
	template<typename T>
	inline bool EntityManager::RemoveSharedComponent(Entity entity)
	{
		if (entity.IsNull()) return false;
		return _EntitySharedComponentStorage->RemoveSharedComponent<T>(entity);
	}
	template<typename T>
	inline bool EntityManager::HasSharedComponent(Entity entity)
	{
		if (entity.IsNull()) return nullptr;
		return _EntitySharedComponentStorage->GetSharedComponent<T>(entity) != nullptr;
	}
	template<typename T>
	inline std::vector<Entity>* EntityManager::GetSharedComponentEntities(T* value)
	{
		return _EntitySharedComponentStorage->GetOwnersList<T>(value);
	}
#pragma endregion
#pragma region SharedQuery
	template<typename T>
	inline std::vector<T*>* EntityManager::GetSharedComponentDataArray()
	{
		return _EntitySharedComponentStorage->GetSCList<T>();
	}

	template<typename T, typename ...Ts>
	inline void EntityManager::SetEntityQueryAllFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
	inline void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*)>& func)
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2, typename T3>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func) {
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
			ForEachStorage(i, func);
		}
	}
#pragma endregion
	template<typename T>
	inline void EntityManager::GetComponentDataArray(EntityQuery entityQuery, std::vector<T>* container)
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
	template<typename T1, typename T2>
	inline void EntityManager::GetComponentDataArray(EntityQuery entityQuery, T1 filter, std::vector<T2>* container)
	{
		std::vector<T1> componentDataList;
		std::vector<T2> targetDataList;
		GetComponentDataArray(entityQuery, &componentDataList);
		GetComponentDataArray(entityQuery, &targetDataList);
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
			container->resize(container->size() + listSize);
			memcpy(&container->at(container->size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T2));
		}
		

		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filter == componentDataList[size - remainder + i]) {
				container->push_back(targetDataList[size - remainder + i]);
			}
		}
	}
	template<typename T1>
	inline void EntityManager::GetEntityArray(EntityQuery entityQuery, T1 filter, std::vector<Entity>* container)
	{
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList;
		GetEntityArray(entityQuery, &allEntities);
		GetComponentDataArray(entityQuery, &componentDataList);
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
			container->resize(container->size() + listSize);
			memcpy(&container->at(container->size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		size_t remainder = size % 8;
		for (int i = 0; i < remainder; i++) {
			if (filter == componentDataList[size - remainder + i]) {
				container->push_back(allEntities[size - remainder + i]);
			}
		}
	}
	template<typename T>
	inline void EntityQuery::ToComponentDataArray(std::vector<T>* container)
	{
		EntityManager::GetComponentDataArray(*this, container);
	}
	template<typename T1, typename T2>
	inline void EntityQuery::ToComponentDataArray(T1 filter, std::vector<T2>* container)
	{
		EntityManager::GetComponentDataArray(*this, filter, container);
	}
	template<typename T1>
	inline void EntityQuery::ToEntityArray(T1 filter, std::vector<Entity>* container)
	{
		EntityManager::GetEntityArray(*this, filter, container);
	}
#pragma endregion

}
#pragma once
#include "ManagerBase.h"
#include "Entity.h"
#include "SharedComponentStorage.h"
#include "World.h"
namespace UniEngine {
	namespace Entities {
#pragma region EntityManager
		struct ENTITIES_API WorldEntityStorage {
			size_t Index;
			std::vector<Entity> Entities;
			std::vector<Entity> ParentRoots;
			std::vector<EntityInfo> EntityInfos;
			std::vector<std::queue<Entity>> EntityPool;
			std::vector<EntityComponentStorage> EntityComponentStorage;
			SharedComponentStorage EntitySharedComponentStorage;

			std::vector<EntityQuery> EntityQueries;
			std::vector<EntityQueryInfo> EntityQueryInfos;
			std::queue<EntityQuery> EntityQueryPools;
		};
		class ENTITIES_API EntityManager : public ManagerBase {
			static std::vector<WorldEntityStorage*> _WorldEntityStorage;
			static std::vector<Entity>* _Entities;
			static std::vector<Entity>* _ParentRoots;
			static std::vector<EntityInfo>* _EntityInfos;
			static std::vector<EntityComponentStorage>* _EntityComponentStorage;
			static std::vector<std::queue<Entity>>* _EntityPool;
			static SharedComponentStorage* _EntitySharedComponentStorage;
			static std::vector<EntityQuery>* _EntityQueries;
			static std::vector<EntityQueryInfo>* _EntityQueryInfos;
			static std::queue<EntityQuery>* _EntityQueryPools;
			static ThreadPool* _ThreadPool;
			template<typename T = ComponentBase>
			static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg);
			template<typename T = ComponentBase, typename... Ts>
			static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg, Ts... args);
			template<typename T = ComponentBase, typename... Ts>
			static std::vector<ComponentType> CollectComponentTypes(T arg, Ts... args);
			static void DeleteEntityInternal(Entity entity);

			static void RefreshEntityQueryInfos(size_t index);

			template<typename T1 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
			static void ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func);

			template<typename T1 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
			static void ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func);

			template<typename T = ComponentBase>
			static void GetComponentDataArrayStorage(EntityComponentStorage storage, std::vector<T>* container);
			static void GetEntityStorage(EntityComponentStorage storage, std::vector<Entity>* container);
			static size_t SwapEntity(EntityComponentStorage storage, size_t index1, size_t index2);
			
		public:
			static void Init(ThreadPool* threadPool);

			static void GetAllEntities(std::vector<Entity>* target);
			static std::vector<Entity>* GetAllEntitiesUnsafe();
			static void SetThreadPool(ThreadPool* pool);
			static void SetWorld(World* world);
			template<typename T = ComponentBase, typename... Ts>
			static EntityArchetype CreateEntityArchetype(T arg, Ts... args);

			static Entity CreateEntity(EntityArchetype archetype);
			static void DeleteEntity(Entity entity);

			static void SetParent(Entity entity, Entity parent);
			static Entity GetParent(Entity entity);
			static std::vector<Entity> GetChildren(Entity entity);
			static void RemoveChild(Entity entity, Entity parent);
			static void GetParentRoots(std::vector<Entity>* container);
			static std::vector<Entity>* GetParentRootsUnsafe();

			template<typename T = ComponentBase>
			static void SetComponentData(Entity entity, T value);
			template<typename T = ComponentBase>
			static T GetComponentData(Entity entity);
			template<typename T = ComponentBase>
			static bool HasComponentData(Entity entity);

			template <typename T = SharedComponentBase>
			static T* GetSharedComponent(Entity entity);
			template <typename T = SharedComponentBase>
			static void SetSharedComponent(Entity entity, T* value);
			template <typename T = SharedComponentBase>
			static bool RemoveSharedComponent(Entity entity);
			template <typename T = SharedComponentBase>
			static bool HasSharedComponent(Entity entity);


			template <typename T = SharedComponentBase>
			static std::vector<Entity>* QueryEntities(T* value);
			template <typename T = SharedComponentBase>
			static std::vector<T*>* QuerySharedComponents();

			static EntityArchetype GetEntityArchetype(Entity entity);

			static EntityQuery CreateEntityQuery();
			static void DeleteEntityQuery(EntityQuery entityQuery);
			template<typename T = ComponentBase, typename... Ts>
			static void SetEntityQueryAllFilters(EntityQuery entityQuery, T arg, Ts... args);
			template<typename T = ComponentBase, typename... Ts>
			static void SetEntityQueryAnyFilters(EntityQuery entityQuery, T arg, Ts... args);
			template<typename T = ComponentBase, typename... Ts>
			static void SetEntityQueryNoneFilters(EntityQuery entityQuery, T arg, Ts... args);
			//Unsafe zone, allow directly manipulation of entity data, which may result in data corruption.
			static std::vector<EntityComponentStorage> UnsafeQueryStorages(EntityQuery entityQuery);
			static ComponentDataChunkArray* UnsafeGetEntityComponentDataChunkArray(EntityArchetype entityArchetype);

			template<typename T1 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
			static void ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func);

			template<typename T1 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func);
			template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase, typename T4 = ComponentBase, typename T5 = ComponentBase, typename T6 = ComponentBase, typename T7 = ComponentBase, typename T8 = ComponentBase>
			static void ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func);

			template<typename T = ComponentBase>
			static void GetComponentDataArray(EntityQuery entityQuery, std::vector<T>* container);
			static void GetEntityArray(EntityQuery entityQuery, std::vector<Entity>* container);
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
			for (int i = 1; i < retVal.size(); i++) {
				if (retVal[i] == prev) {
					retVal.erase(retVal.begin() + i);
					i--;
				}
				else {
					prev = retVal[i];
				}
			}
			for (int i = 0; i < retVal.size(); i++) {
				retVal[i].Offset = offset;
				offset += retVal[i].Size;
			}
			return retVal;
		}
#pragma endregion
#pragma region ForEachStorage
		template<typename T1>
		inline void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*)>& func)
		{
			ComponentType targetType1 = typeof<T1>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found = true;
					break;
				}
			}
			if (found) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size)
									);
								}
							}
					).share());
				}
				if (remainder != 0) {
					void* data = chunkArray->Chunks[chunkAmount].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2>
		inline void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*)>& func)
		{
			ComponentType targetType1 = typeof<T1>();
			ComponentType targetType2 = typeof<T2>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found1 = false;
			bool found2 = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
			}
			if (found1 && found2) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
										(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3>
		static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*)>& func) {
			ComponentType targetType1 = typeof<T1>();
			ComponentType targetType2 = typeof<T2>();
			ComponentType targetType3 = typeof<T3>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found1 = false;
			bool found2 = false;
			bool found3 = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
			}
			if (found1 && found2 && found3) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2, targetType3](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
										(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
										(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4>
		static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*)>& func) {
			ComponentType targetType1 = typeof<T1>();
			ComponentType targetType2 = typeof<T2>();
			ComponentType targetType3 = typeof<T3>();
			ComponentType targetType4 = typeof<T4>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found1 = false;
			bool found2 = false;
			bool found3 = false;
			bool found4 = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
			}
			if (found1 && found2 && found3 && found4) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
										(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
										(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
										(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
			}
			if (found1 && found2 && found3 && found4 && found5) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
				else if (targetType6 == type) {
					targetType6 = type;
					found6 = true;
				}
			}
			if (found1 && found2 && found3 && found4 && found5 && found6) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
				else if (targetType6 == type) {
					targetType6 = type;
					found6 = true;
				}
				else if (targetType7 == type) {
					targetType7 = type;
					found7 = true;
				}
			}
			if (found1 && found2 && found3 && found4 && found5 && found6 && found7) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static void EntityManager::ForEachStorage(EntityComponentStorage storage, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
				else if (targetType6 == type) {
					targetType6 = type;
					found6 = true;
				}
				else if (targetType7 == type) {
					targetType7 = type;
					found7 = true;
				}
				else if (targetType8 == type) {
					targetType8 = type;
					found8 = true;
				}
			}
			if (found1 && found2 && found3 && found4 && found5 && found6 && found7 && found8) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8](int id)
							{
								for (int i = 0; i < capacity; i++) {
									func(i + chunkIndex * capacity,
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
						_ThreadPool->Push([capacity, func, chunkAmount, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8, remainder](int id)
							{
								for (int i = 0; i < remainder; i++) {
									func(i + chunkAmount * capacity,
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}

		template<typename T1>
		inline void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*)>& func)
		{
			ComponentType targetType1 = typeof<T1>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found = true;
					break;
				}
			}
			if (found) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<Entity>* entities = &chunkArray->Entities;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2>
		inline void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*)>& func)
		{
			ComponentType targetType1 = typeof<T1>();
			ComponentType targetType2 = typeof<T2>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found1 = false;
			bool found2 = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
			}
			if (found1 && found2) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<Entity>* entities = &chunkArray->Entities;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
										(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3>
		static void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func) {
			ComponentType targetType1 = typeof<T1>();
			ComponentType targetType2 = typeof<T2>();
			ComponentType targetType3 = typeof<T3>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found1 = false;
			bool found2 = false;
			bool found3 = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
			}
			if (found1 && found2 && found3) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<Entity>* entities = &chunkArray->Entities;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
										(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
										(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4>
		static void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func) {
			ComponentType targetType1 = typeof<T1>();
			ComponentType targetType2 = typeof<T2>();
			ComponentType targetType3 = typeof<T3>();
			ComponentType targetType4 = typeof<T4>();
			size_t entityCount = storage.ArchetypeInfo->EntityAliveCount;
			bool found1 = false;
			bool found2 = false;
			bool found3 = false;
			bool found4 = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
			}
			if (found1 && found2 && found3 && found4) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<Entity>* entities = &chunkArray->Entities;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
										(T1*)((char*)data + targetType1.Offset * capacity + (i % capacity) * targetType1.Size),
										(T2*)((char*)data + targetType2.Offset * capacity + (i % capacity) * targetType2.Size),
										(T3*)((char*)data + targetType3.Offset * capacity + (i % capacity) * targetType3.Size),
										(T4*)((char*)data + targetType4.Offset * capacity + (i % capacity) * targetType4.Size)
									);
								}
							}
					).share());
				}
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		static void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
			}
			if (found1 && found2 && found3 && found4 && found5) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<Entity>* entities = &chunkArray->Entities;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
									func(index, entities->at(index),
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
				else if (targetType6 == type) {
					targetType6 = type;
					found6 = true;
				}
			}
			if (found1 && found2 && found3 && found4 && found5 && found6) {
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				int chunkAmount = entityCount / capacity;
				int remainder = entityCount % capacity;
				ComponentDataChunkArray* chunkArray = storage.ChunkArray;
				std::vector<Entity>* entities = &chunkArray->Entities;
				std::vector<std::shared_future<void>> results;
				for (int chunkIndex = 0; chunkIndex < chunkAmount; chunkIndex++) {
					void* data = chunkArray->Chunks[chunkIndex].Data;
					results.push_back(
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
				else if (targetType6 == type) {
					targetType6 = type;
					found6 = true;
				}
				else if (targetType7 == type) {
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
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
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
				for (int i = 0; i < results.size(); i++) {
					results[i].wait();
				}
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static void EntityManager::ForEachWithEntityStorage(EntityComponentStorage storage, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func) {
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
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType1 == type) {
					targetType1 = type;
					found1 = true;
				}
				else if (targetType2 == type) {
					targetType2 = type;
					found2 = true;
				}
				else if (targetType3 == type) {
					targetType3 = type;
					found3 = true;
				}
				else if (targetType4 == type) {
					targetType4 = type;
					found4 = true;
				}
				else if (targetType5 == type) {
					targetType5 = type;
					found5 = true;
				}
				else if (targetType6 == type) {
					targetType6 = type;
					found6 = true;
				}
				else if (targetType7 == type) {
					targetType7 = type;
					found7 = true;
				}
				else if (targetType8 == type) {
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
						_ThreadPool->Push([entities, capacity, func, chunkIndex, data, targetType1, targetType2, targetType3, targetType4, targetType5, targetType6, targetType7, targetType8](int id)
							{
								for (int i = 0; i < capacity; i++) {
									int index = i + chunkIndex * capacity;
									func(index, entities->at(index),
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
								for (int i = 0; i < remainder; i++) {
									int index = i + chunkAmount * capacity;
									func(index, entities->at(index),
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
				for (int i = 0; i < results.size(); i++) {
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
			bool found = false;
			for (auto type : storage.ArchetypeInfo->ComponentTypes) {
				if (targetType == type) {
					targetType = type;
					found = true;
					break;
				}
			}
			if (found) {
				size_t amount = storage.ArchetypeInfo->EntityAliveCount;
				if (amount == 0) return;
				container->resize(container->size() + amount);
				size_t capacity = storage.ArchetypeInfo->ChunkCapacity;
				size_t chunkAmount = amount / capacity;
				size_t remainAmount = amount % capacity;
				for (int i = 0; i < chunkAmount; i++) {
					memcpy(&container->at(container->size() - remainAmount - capacity * (chunkAmount - i)), (void*)((char*)storage.ChunkArray->Chunks[i].Data + capacity * targetType.Offset), capacity * targetType.Size);
				}
				if (remainAmount > 0) memcpy(&container->at(container->size() - remainAmount), (void*)((char*)storage.ChunkArray->Chunks[chunkAmount].Data + capacity * targetType.Offset), remainAmount * targetType.Size);
			}
		}

		template<typename T, typename ...Ts>
		inline EntityArchetype EntityManager::CreateEntityArchetype(T arg, Ts ...args)
		{
			EntityArchetypeInfo* info = new EntityArchetypeInfo();
			info->EntityCount = 0;
			info->ComponentTypes = CollectComponentTypes(arg, args...);
			info->EntitySize = info->ComponentTypes.back().Offset + info->ComponentTypes.back().Size;
			info->ChunkCapacity = ARCHETYPECHUNK_SIZE / info->EntitySize;
			int duplicateIndex = -1;
			for (auto i = 1; i < _EntityComponentStorage->size(); i++) {
				EntityArchetypeInfo* compareInfo = _EntityComponentStorage->at(i).ArchetypeInfo;
				if (info->ChunkCapacity != compareInfo->ChunkCapacity) continue;
				if (info->EntitySize != compareInfo->EntitySize) continue;
				bool typeCheck = true;
				for (auto j = 0; j < compareInfo->ComponentTypes.size(); j++) {
					if (info->ComponentTypes[j] != compareInfo->ComponentTypes[j]) typeCheck = false;
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
				_EntityPool->push_back(std::queue<Entity>());
			}
			else {
				retVal.Index = duplicateIndex;
			}
			for (int i = 0; i < _EntityQueryInfos->size(); i++) {
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
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
				unsigned offset = 0;
				bool found = false;
				size_t id = typeid(T).hash_code();
				for (int i = 0; i < chunkInfo->ComponentTypes.size(); i++) {
					if (id == chunkInfo->ComponentTypes[i].TypeID) {
						offset += chunkInfo->ComponentTypes[i].Offset * chunkInfo->ChunkCapacity;
						offset += chunkPointer * chunkInfo->ComponentTypes[i].Size;
						found = true;
						break;
					}
				}
				if (found) {
					chunk.SetData<T>(offset, value);
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
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
				unsigned offset = 0;
				bool found = false;
				size_t id = typeid(T).hash_code();
				for (int i = 0; i < chunkInfo->ComponentTypes.size(); i++) {
					if (id == chunkInfo->ComponentTypes[i].TypeID) {
						offset += chunkInfo->ComponentTypes[i].Offset * chunkInfo->ChunkCapacity;
						offset += chunkPointer * chunkInfo->ComponentTypes[i].Size;
						found = true;
						break;
					}
				}
				if (found) {
					return chunk.GetData<T>(offset);
				}
				else {
					Debug::Log("ComponentData doesn't exist");
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
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
				unsigned offset = 0;
				bool found = false;
				size_t id = typeid(T).hash_code();
				for (int i = 0; i < chunkInfo->ComponentTypes.size(); i++) {
					if (id == chunkInfo->ComponentTypes[i].TypeID) {
						offset += chunkInfo->ComponentTypes[i].Offset * chunkInfo->ChunkCapacity;
						offset += chunkPointer * chunkInfo->ComponentTypes[i].Size;
						found = true;
						break;
					}
				}
				if (found) {
					return true;
				}
				else {
					return false;
				}
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
		inline std::vector<Entity>* EntityManager::QueryEntities(T* value)
		{
			return _EntitySharedComponentStorage->GetOwnersList<T>(value);
		}
#pragma endregion
#pragma region SharedQuery
		template<typename T>
		inline std::vector<T*>* EntityManager::QuerySharedComponents()
		{
			return _EntitySharedComponentStorage->GetSCList<T>();
		}

		template<typename T, typename ...Ts>
		inline void EntityManager::SetEntityQueryAllFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
			_EntityQueryInfos->at(index).AllComponentTypes = CollectComponentTypes(arg, args...);
			RefreshEntityQueryInfos(index);
		}

		template<typename T, typename ...Ts>
		inline void EntityManager::SetEntityQueryAnyFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
			_EntityQueryInfos->at(index).AnyComponentTypes = CollectComponentTypes(arg, args...);
			RefreshEntityQueryInfos(index);
		}

		template<typename T, typename ...Ts>
		inline void EntityManager::SetEntityQueryNoneFilters(EntityQuery entityQuery, T arg, Ts ...args)
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
			_EntityQueryInfos->at(index).NoneComponentTypes = CollectComponentTypes(arg, args...);
			RefreshEntityQueryInfos(index);
		}
#pragma endregion
#pragma region For Each
		template<typename T1>
		inline void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*)>& func)
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static void EntityManager::ForEach(EntityQuery entityQuery, const std::function<void(int i, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachStorage(i, func);
			}
		}

		template<typename T1>
		inline void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*)>& func)
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static void EntityManager::ForEachWithEntity(EntityQuery entityQuery, const std::function<void(int i, Entity entity, T1*, T2*, T3*, T4*, T5*, T6*, T7*, T8*)>& func) {
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				ForEachWithEntityStorage(i, func);
			}
		}
#pragma endregion
		template<typename T>
		inline void EntityManager::GetComponentDataArray(EntityQuery entityQuery, std::vector<T>* container)
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
			for (auto i : _EntityQueryInfos->at(index).QueriedStorages) {
				GetComponentDataArrayStorage(i, container);
			}
		}

#pragma endregion
	}
}
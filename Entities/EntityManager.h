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
			std::vector<EntityInfo> Entities;
			std::vector<std::queue<Entity>> EntityPool;
			std::vector<EntityComponentStorage> EntityComponentStorage;
			SharedComponentStorage EntitySharedComponentStorage;
		};
		class ENTITIES_API EntityManager : public ManagerBase {
			static std::vector<WorldEntityStorage*> _WorldEntityStorage;
			static std::vector<EntityInfo>* _Entities;
			static std::vector<EntityComponentStorage>* _EntityComponentStorage;
			static std::vector<std::queue<Entity>>* _EntityPool;
			static SharedComponentStorage* _EntitySharedComponentStorage;
			template<typename T>
			static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg);
			template<typename T, typename... Ts>
			static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg, Ts... args);
			template<typename T, typename... Ts>
			static std::vector<ComponentType> CollectComponentTypes(T arg, Ts... args);
		public:
			static std::vector<EntityInfo>* GetAllEntities();

			static void SetWorld(World* world);
			template<typename T, typename... Ts>
			static EntityArchetype CreateEntityArchetype(T arg, Ts... args);

			static Entity CreateEntity(EntityArchetype archetype);
			static void DeleteEntity(Entity entity);

			template<typename T>
			static void SetComponentData(Entity entity, T value);
			template<typename T>
			static T GetComponentData(Entity entity);

			template <typename T>
			static T* GetSharedComponent(Entity entity);
			template <typename T>
			static void SetSharedComponent(Entity entity, T* value);
			template <typename T>
			static void RemoveSharedComponent(Entity entity);

			template <typename T>
			static std::vector<Entity>* QueryEntities(T* value);
			template <typename T>
			static std::vector<std::pair<SharedComponentBase*, OC*>*>* QuerySharedComponents();

			static EntityArchetype GetEntityArchetype(Entity entity);
		};
#pragma endregion
#pragma region Functions
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
			for (int i = 0; i < retVal.size(); i++) {
				retVal[i].Offset = offset;
				offset += retVal[i].Size;
			}
			return retVal;
		}

		template<typename T, typename ...Ts>
		inline EntityArchetype EntityManager::CreateEntityArchetype(T arg, Ts ...args)
		{
			EntityArchetypeInfo* info = new EntityArchetypeInfo();
			info->EntityCount = 0;
			info->ComponentTypes = CollectComponentTypes(arg, args...);
			info->EntitySize = info->ComponentTypes.back().Offset + info->ComponentTypes.back().Size;
			info->ChunkCapacity = ARCHETYPECHUNK_SIZE / info->EntitySize;
			EntityArchetype retVal;
			retVal.Index = _EntityComponentStorage->size();
			info->Index = retVal.Index;
			_EntityComponentStorage->push_back(EntityComponentStorage(info, new ComponentDataChunkArray()));
			_EntityPool->push_back(std::queue<Entity>());
			return retVal;
		}


		template<typename T>
		inline void EntityManager::SetComponentData(Entity entity, T value)
		{
			EntityInfo info = _Entities->at(entity.Index);
			if (info.Entity == entity) {
				EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
				unsigned offset = 0;
				size_t id = typeid(T).hash_code();
				for (int i = 0; i < chunkInfo->ComponentTypes.size(); i++) {
					if (id == chunkInfo->ComponentTypes[i].TypeID) {
						offset += chunkInfo->ComponentTypes[i].Offset * chunkInfo->ChunkCapacity;
						offset += chunkPointer * chunkInfo->ComponentTypes[i].Size;
						break;
					}
				}
				chunk.SetData<T>(offset, value);
			}
			else {
				Debug::Error("Entity already deleted!");
				return;
			}
		}
		template<typename T>
		inline T EntityManager::GetComponentData(Entity entity)
		{
			EntityInfo info = _Entities->at(entity.Index);
			if (info.Entity == entity) {
				EntityArchetypeInfo* chunkInfo = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ArchetypeInfo;
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityComponentStorage->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
				unsigned offset = 0;
				size_t id = typeid(T).hash_code();
				for (int i = 0; i < chunkInfo->ComponentTypes.size(); i++) {
					if (id == chunkInfo->ComponentTypes[i].TypeID) {
						offset += chunkInfo->ComponentTypes[i].Offset * chunkInfo->ChunkCapacity;
						offset += chunkPointer * chunkInfo->ComponentTypes[i].Size;
						break;
					}
				}
				return chunk.GetData<T>(offset);
			}
			else {
				Debug::Error("Entity already deleted!");
				return T();
			}
		}
		template<typename T>
		inline T* EntityManager::GetSharedComponent(Entity entity)
		{
			return _EntitySharedComponentStorage->GetSC<T>(entity);
		}
		template<typename T>
		inline void EntityManager::SetSharedComponent(Entity entity, T* value)
		{
			_EntitySharedComponentStorage->SetSC<T>(entity, value);
		}
		template<typename T>
		inline void EntityManager::RemoveSharedComponent(Entity entity)
		{
			_EntitySharedComponentStorage->RemoveSC<T>(entity);
		}
		template<typename T>
		inline std::vector<Entity>* EntityManager::QueryEntities(T* value)
		{
			return _EntitySharedComponentStorage->GetOsList<T>(value);
		}
		template<typename T>
		inline std::vector<std::pair<SharedComponentBase*, OC*>*>* EntityManager::QuerySharedComponents()
		{
			return _EntitySharedComponentStorage->GetSCOCsList<T>();
		}

#pragma endregion
	}
}
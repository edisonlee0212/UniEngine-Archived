#pragma once
#include "EntitiesAPI.h"
namespace UniEngine {
	namespace Entities {
#pragma region Structs
		struct ENTITIES_API Entity {
			//Position in Entity Array
			unsigned Index;
			unsigned Version;
			bool operator==(const Entity& other) const {
				return (other.Index == Index) && (other.Version == Version);
			}
		};

		struct ENTITIES_API ComponentType {
			size_t TypeID;
			//Size of component
			size_t Size;
			//Starting point of the component
			size_t Offset;
		};

		const size_t ARCHETYPECHUNK_SIZE = 16384;

		struct ComponentDataChunk {
			//16k raw data
			void* Data;
			template<typename T>
			T GetData(unsigned offset);

			template<typename T>
			void SetData(unsigned offset, T data);
		};

		struct ComponentDataChunkArray {
			std::vector<Entity> Entities;
			std::vector<ComponentDataChunk> Chunks;
		};

		struct ENTITIES_API EntityArchetype {
			size_t Index;
		};

		struct EntityInfo {
			Entity Entity;
			size_t ArchetypeIndex;
			size_t ChunkIndex;
		};

		struct EntityArchetypeInfo {
			size_t Index;
			std::vector<ComponentType> ComponentTypes;
			//The size of a single entity
			size_t EntitySize;
			//How many entites can fit into one chunk
			size_t ChunkCapacity;
			//Current allocated entity count.
			size_t EntityCount;
		};

		struct ENTITIES_API EntityQuery {
			size_t ComponentsSize;
			std::vector<ComponentType> ComponentTypes;
		};

#pragma endregion	
		typedef std::pair<EntityArchetypeInfo*, ComponentDataChunkArray*> EntityArchetypeStorage;
		class ENTITIES_API EntityManager : ManagerBase {
			std::vector<EntityInfo> _Entities;
			std::vector<EntityArchetypeStorage> _EntityArchetypes;
			std::vector<std::queue<Entity>> _EntityPool;
#pragma region EntityArchetypeHelpers
			template<typename T>
			size_t GenerateEntityArchetype(EntityArchetypeInfo* entityArchetypeInfo, T arg);
			template<typename T, typename... Ts>
			size_t GenerateEntityArchetype(EntityArchetypeInfo* entityArchetypeInfo, T arg, Ts... args);
			template<typename T>
			size_t GenerateEntityQuery(EntityQuery* entityQuery, T arg);
			template<typename T, typename... Ts>
			size_t GenerateEntityQuery(EntityQuery* entityQuery, T arg, Ts... args);
#pragma endregion
		public:
			template<typename T, typename... Ts>
			EntityArchetype CreateEntityArchetype(T arg, Ts... args);
			template<typename T, typename... Ts>
			EntityQuery CreateEntityQuery(T arg, Ts... args);


			Entity CreateEntity(EntityArchetype archetype);
			void DeleteEntity(Entity entity);

			template<typename T>
			void SetComponentData(Entity entity, T value);
			template<typename T>
			T GetComponentData(Entity entity);

			EntityArchetype GetEntityArchetype(Entity entity);


		};
		template<typename T>
		inline size_t EntityManager::GenerateEntityArchetype(EntityArchetypeInfo* entityArchetypeInfo, T arg)
		{
			auto componentSize = sizeof(T);
			ComponentType type;
			type.TypeID = typeid(T).hash_code();
			type.Size = componentSize;
			type.Offset = 0;
			entityArchetypeInfo->ComponentTypes.push_back(type);
			return componentSize;
		}

		template<typename T, typename ...Ts>
		inline size_t EntityManager::GenerateEntityArchetype(EntityArchetypeInfo* entityArchetypeInfo, T arg, Ts ...args)
		{
			auto offset = GenerateEntityArchetype(entityArchetypeInfo, args...);
			auto componentSize = sizeof(T);
			ComponentType type;
			type.TypeID = typeid(T).hash_code();
			type.Size = componentSize;
			type.Offset = offset;
			entityArchetypeInfo->ComponentTypes.push_back(type);
			return componentSize + offset;
		}

		template<typename T>
		inline size_t EntityManager::GenerateEntityQuery(EntityQuery* entityQuery, T arg)
		{
			auto componentSize = sizeof(T);
			ComponentType type;
			type.TypeID = typeid(T).hash_code();
			type.Size = componentSize;
			type.Offset = 0;
			entityQuery->ComponentTypes.push_back(type);
			return componentSize;
		}

		template<typename T, typename ...Ts>
		inline size_t EntityManager::GenerateEntityQuery(EntityQuery* entityQuery, T arg, Ts ...args)
		{
			auto offset = GenerateEntityArchetype(entityQuery, args...);
			auto componentSize = sizeof(T);
			ComponentType type;
			type.TypeID = typeid(T).hash_code();
			type.Size = componentSize;
			type.Offset = offset;
			entityQuery->ComponentTypes.push_back(type);
			return componentSize + offset;
		}

		template<typename T, typename ...Ts>
		inline EntityArchetype EntityManager::CreateEntityArchetype(T arg, Ts ...args)
		{
			EntityArchetypeInfo* info = new EntityArchetypeInfo();
			info->EntityCount = 0;
			info->ComponentTypes = std::vector<ComponentType>();
			info->EntitySize = GenerateEntityArchetype(info, arg, args...);
			info->ChunkCapacity = ARCHETYPECHUNK_SIZE / info->EntitySize;
			EntityArchetype retVal;
			retVal.Index = _EntityArchetypes.size();
			info->Index = retVal.Index;
			_EntityArchetypes.push_back(EntityArchetypeStorage(info, new ComponentDataChunkArray()));
			_EntityPool.push_back(std::queue<Entity>());
			return retVal;
		}

		template<typename T, typename ...Ts>
		inline EntityQuery EntityManager::CreateEntityQuery(T arg, Ts ...args)
		{
			EntityQuery retVal;
			retVal.ComponentsSize = GenerateEntityQuery(&retVal, arg, args...);
			return retVal;
		}

		template<typename T>
		inline void EntityManager::SetComponentData(Entity entity, T value)
		{
			EntityInfo info = _Entities[entity.Index];
			if (info.Entity == entity) {
				EntityArchetypeInfo* chunkInfo = _EntityArchetypes[info.ArchetypeIndex].first;
				unsigned chunkIndex = info.ChunkIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityArchetypes[info.ArchetypeIndex].second->Chunks[chunkIndex];
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
			EntityInfo info = _Entities[entity.Index];
			if (info.Entity == entity) {
				EntityArchetypeInfo* chunkInfo = _EntityArchetypes[info.ArchetypeIndex].first;
				unsigned chunkIndex = info.ChunkIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityArchetypes[info.ArchetypeIndex].second->Chunks[chunkIndex];
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
		inline T ComponentDataChunk::GetData(unsigned offset)
		{
			return T(*(T*)((char*)Data + offset));
		}
		template<typename T>
		inline void ComponentDataChunk::SetData(unsigned offset, T data)
		{
			*(T*)((char*)Data + offset) = data;
		}
}
}
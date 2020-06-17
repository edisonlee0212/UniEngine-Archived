#pragma once
#include "EntitiesAPI.h"
namespace UniEngine {
	namespace Entities {
#pragma region Structs
		struct ENTITIES_API Entity {
			//Position in Entity Array
			unsigned Index;
			unsigned Version;
			bool operator ==(const Entity& other) const {
				return (other.Index == Index) && (other.Version == Version);
			}
			bool operator !=(const Entity& other) const {
				return (other.Index != Index) || (other.Version != Version);
			}
		};

		struct ENTITIES_API ComponentType {
			size_t TypeID;
			//Size of component
			size_t Size;
			//Starting point of the component
			size_t Offset;
		};

		template<typename T>
		ComponentType typeof() {
			ComponentType type;
			type.Size = sizeof(T);
			type.Offset = 0;
			type.TypeID = typeid(T).hash_code();
			return type;
		}

		bool ComponentTypeComparator(ComponentType a, ComponentType b) {
			return a.TypeID < b.TypeID;
		}

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
			size_t ArchetypeInfoIndex;
			size_t ChunkArrayIndex;
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
			std::vector<ComponentType> AllComponentTypes;
			std::vector<ComponentType> AnyComponentTypes;
			std::vector<ComponentType> NoneComponentTypes;
		};

#pragma endregion	
		struct ENTITIES_API EntityArchetypeStorage {
			EntityArchetypeInfo* ArchetypeInfo;
			ComponentDataChunkArray* ChunkArray;
			EntityArchetypeStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array);
		};

		struct ENTITIES_API EntityComponentStorage {
			size_t Index;
			std::vector<EntityInfo> Entities;
			std::vector<EntityArchetypeStorage> EntityArchetypes;
			std::vector<std::queue<Entity>> EntityPool;
		};

		class ENTITIES_API EntityManager : public ManagerBase {
			static std::vector<EntityComponentStorage*> _EntityComponentStorage;
			static std::vector<EntityInfo>* _Entities;
			static std::vector<EntityArchetypeStorage>* _EntityArchetypes;
			static std::vector<std::queue<Entity>>* _EntityPool;
#pragma region EntityArchetypeHelpers
			template<typename T>
			static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg);
			template<typename T, typename... Ts>
			static size_t CollectComponentTypes(std::vector<ComponentType>* componentTypes, T arg, Ts... args);
			template<typename T, typename... Ts>
			static std::vector<ComponentType> CollectComponentTypes(T arg, Ts... args);
#pragma endregion
		public:
			static void SetWorld(World* world);
			template<typename T, typename... Ts>
			static EntityArchetype CreateEntityArchetype(T arg, Ts... args);

			static Entity CreateEntity(EntityArchetype archetype);
			static void DeleteEntity(Entity entity);

			template<typename T>
			static void SetComponentData(Entity entity, T value);
			template<typename T>
			static T GetComponentData(Entity entity);

			static EntityArchetype GetEntityArchetype(Entity entity);
		};
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
			retVal.Index = _EntityArchetypes->size();
			info->Index = retVal.Index;
			_EntityArchetypes->push_back(EntityArchetypeStorage(info, new ComponentDataChunkArray()));
			_EntityPool->push_back(std::queue<Entity>());
			return retVal;
		}


		template<typename T>
		inline void EntityManager::SetComponentData(Entity entity, T value)
		{
			EntityInfo info = _Entities->at(entity.Index);
			if (info.Entity == entity) {
				EntityArchetypeInfo* chunkInfo = _EntityArchetypes->at(info.ArchetypeInfoIndex).ArchetypeInfo;
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityArchetypes->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
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
				EntityArchetypeInfo* chunkInfo = _EntityArchetypes->at(info.ArchetypeInfoIndex).ArchetypeInfo;
				unsigned chunkIndex = info.ChunkArrayIndex / chunkInfo->ChunkCapacity;
				unsigned chunkPointer = info.ChunkArrayIndex % chunkInfo->ChunkCapacity;
				ComponentDataChunk chunk = _EntityArchetypes->at(info.ArchetypeInfoIndex).ChunkArray->Chunks[chunkIndex];
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
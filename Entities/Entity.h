#pragma once
#include "EntitiesAPI.h"
namespace UniEngine {
	namespace Entities {
#pragma region EntityManager
#pragma region Entity
		struct ENTITIES_API ComponentBase {
		};


		class ENTITIES_API SharedComponentBase {
		public:
			virtual size_t GetHashCode() = 0;
		};

		struct ENTITIES_API Entity {
			//Position in _Entity Array
			unsigned Index = 0;
			unsigned Version = 0;

			bool operator ==(const Entity& other) const {
				return (other.Index == Index) && (other.Version == Version);
			}
			bool operator !=(const Entity& other) const {
				return (other.Index != Index) || (other.Version != Version);
			}
			size_t operator() (Entity const& key) const
			{
				return (size_t)Index;
			}

			
		};
#pragma region Storage

		struct ENTITIES_API ComponentType {
			size_t TypeID;
			//Size of component
			size_t Size;
			//Starting point of the component, this part is not comparable
			size_t Offset;
			bool operator ==(const ComponentType& other) const {
				return (other.TypeID == TypeID) && (other.Size == Size);
			}
			bool operator !=(const ComponentType& other) const {
				return (other.TypeID != TypeID) || (other.Size != Size);
			}
		};

		template<typename T>
		ComponentType typeof() {
			ComponentType type;
			type.Size = sizeof(T);
			type.Offset = 0;
			type.TypeID = typeid(T).hash_code();
			return type;
		}



		const size_t ARCHETYPECHUNK_SIZE = 16384;

		struct ENTITIES_API ComponentDataChunk {
			//16k raw data
			void* Data;
			template<typename T>
			T GetData(unsigned offset);
			template<typename T>
			void SetData(unsigned offset, T data);
		};

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

		struct ENTITIES_API ComponentDataChunkArray {
			std::vector<Entity> Entities;
			std::vector<ComponentDataChunk> Chunks;
		};

		struct ENTITIES_API EntityArchetype {
			size_t Index;
		};

		struct ENTITIES_API EntityInfo {
			EntityInfo* Parent = nullptr;
			std::vector<Entity> Children;
			//Entity _Entity;
			size_t ArchetypeInfoIndex;
			size_t ChunkArrayIndex;
		};

		struct ENTITIES_API EntityArchetypeInfo {
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
		struct ENTITIES_API EntityComponentStorage {
			EntityArchetypeInfo* ArchetypeInfo;
			ComponentDataChunkArray* ChunkArray;
			EntityComponentStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array);
		};
#pragma endregion
#pragma endregion
#pragma region Predefined Componenets
		struct ENTITIES_API Position : ComponentBase {
			glm::vec3 value;
		};
		struct ENTITIES_API Scale : ComponentBase {
			glm::vec3 value;
		};
		struct ENTITIES_API Rotation : ComponentBase {
			glm::quat value;
		};
		struct ENTITIES_API LocalPosition : ComponentBase
		{
			glm::vec3 value;
		};
		struct ENTITIES_API LocalScale : ComponentBase {
			glm::vec3 value;
		};
		struct ENTITIES_API LocalRotation : ComponentBase {
			glm::quat value;
		};
		struct ENTITIES_API LocalToWorld : ComponentBase {
			glm::mat4 value;
		};
		struct ENTITIES_API LocalToParent : ComponentBase {
			glm::mat4 value;
		};
		struct ENTITIES_API CameraMask : ComponentBase
		{
			unsigned value;
			CameraMask() { value = 0; }
		};
#pragma endregion

#pragma endregion
	}
}
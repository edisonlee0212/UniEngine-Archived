#pragma once
#include "UniEngineAPI.h"
#include "Serializable.h"
namespace UniEngine {
#pragma region EntityManager
#pragma region Entity
	struct UNIENGINE_API ComponentType final {
		const char* Name;
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

	struct UNIENGINE_API ComponentBase {
	};
	
	class UNIENGINE_API SharedComponentBase : public SerializableClass {
		friend class EditorManager;
		bool _Enabled = false;
	public:
		void SetEnabled(bool value)
		{
			if(_Enabled != value)
			{
				if(value)
				{
					OnEnable();
				}else
				{
					OnDisable();
				}
				_Enabled = value;
			}
		}
		bool IsEnabled() const { return _Enabled; }
		virtual void OnEnable(){}
		virtual void OnDisable(){}
		virtual size_t GetHashCode() = 0;
		virtual void OnGui() {}
		virtual ~SharedComponentBase() = default;
	};
	class PrivateComponentBase;
	struct UNIENGINE_API Entity final {
		//Position in _Entity Array
		unsigned Index = 0;
		unsigned Version = 0;

		Entity() {
			Index = 0;
			Version = 0;
		}

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

		bool Enabled() const;

		void SetEnabled(bool value) const;

		bool IsNull() const;

		bool IsDeleted() const;
		bool IsValid() const;
		template<typename T = ComponentBase>
		void SetComponentData(T value) const;
		template<typename T = ComponentBase>
		T GetComponentData() const;
		template<typename T = ComponentBase>
		bool HasComponentData() const;
		template <typename T = SharedComponentBase>
		auto GetSharedComponent() const;
		template <typename T = SharedComponentBase>
		void SetSharedComponent(std::shared_ptr<T> value) const;
		template <typename T = SharedComponentBase>
		bool RemoveSharedComponent() const;
		template <typename T = SharedComponentBase>
		bool HasSharedComponent() const;
		
		template <typename T = PrivateComponentBase>
		auto& GetPrivateComponent() const;
		template <typename T = PrivateComponentBase>
		void SetPrivateComponent(std::unique_ptr<T> value) const;
		template <typename T = PrivateComponentBase>
		bool RemovePrivateComponent() const;
		template <typename T = PrivateComponentBase>
		bool HasPrivateComponent() const;
		
		inline std::string GetName() const;
		inline void SetName(std::string name) const;
	};
#pragma region Storage

	class UNIENGINE_API PrivateComponentBase : public SerializableClass {
		friend class EntityManager;
		friend class EditorManager;
		friend class PrivateComponentElement;
		bool _Enabled = false;
		Entity _Owner;
	public:
		Entity GetOwner() const { return _Owner; }
		void SetEnabled(bool value)
		{
			if (_Enabled != value)
			{
				if (value)
				{
					OnEnable();
				}
				else
				{
					OnDisable();
				}
				_Enabled = value;
			}
		}
		bool IsEnabled() const { return _Enabled; }
		virtual void Init() {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}
		virtual void OnEntityEnable() {}
		virtual void OnEntityDisable() {}
		virtual void OnGui() {}
		virtual ~PrivateComponentBase() = default;
	};

	template<typename T>
	ComponentType typeof() {
		ComponentType type;
		type.Name = typeid(T).name();
		type.Size = sizeof(T);
		type.Offset = 0;
		type.TypeID = typeid(T).hash_code();
		return type;
	}

	const size_t ARCHETYPECHUNK_SIZE = 16384;

	struct ComponentDataChunk {
		//16k raw data
		void* Data;
		template<typename T>
		T GetData(size_t offset)
		{
			return T(*reinterpret_cast<T*>(static_cast<char*>(Data) + offset));
		}
		ComponentBase* GetDataPointer(size_t offset) const
		{
			return reinterpret_cast<ComponentBase*>(static_cast<char*>(Data) + offset);
		}
		template<typename T>
		void SetData(size_t offset, T data)
		{
			*reinterpret_cast<T*>(static_cast<char*>(Data) + offset) = data;
		}
		void SetData(size_t offset, size_t size, ComponentBase* data) const
		{
			memcpy(static_cast<void*>(static_cast<char*>(Data) + offset), data, size);
		}
		void ClearData(size_t offset, size_t size) const
		{
			memset(static_cast<void*>(static_cast<char*>(Data) + offset), 0, size);
		}
	};

	struct ComponentDataChunkArray {
		std::vector<Entity> Entities;
		std::vector<ComponentDataChunk> Chunks;
	};

	struct UNIENGINE_API EntityArchetype {
		size_t Index;
		bool IsNull() {
			return Index == 0;
		}
	};

	struct SharedComponentElement
	{
		const char* Name;
		size_t TypeID;
		std::shared_ptr<SharedComponentBase> SharedComponentData;
		SharedComponentElement(const char* name, size_t id, std::shared_ptr<SharedComponentBase> data)
		{
			Name = name;
			TypeID = id;
			SharedComponentData = std::move(data);
		}
	};

	struct PrivateComponentElement
	{
		const char* Name;
		size_t TypeID;
		std::unique_ptr<PrivateComponentBase> PrivateComponentData;
		PrivateComponentElement(const char* name, size_t id, std::unique_ptr<PrivateComponentBase> data, Entity owner)
		{
			Name = name;
			TypeID = id;
			PrivateComponentData = std::move(data);
			PrivateComponentData->_Owner = owner;
			PrivateComponentData->Init();
		}
		void ResetOwner(Entity newOwner) const { PrivateComponentData->_Owner = newOwner; }
	};
	
	struct EntityInfo {
		friend class PrivateComponentStorage;
		friend class SharedComponentStorage;
		std::string Name;
		size_t Version;
		bool Enabled = true;
		Entity Parent;
		std::vector<SharedComponentElement> SharedComponentElements;
		std::vector<PrivateComponentElement> PrivateComponentElements;
		std::vector<Entity> Children;
		size_t ArchetypeInfoIndex;
		size_t ChunkArrayIndex;
	};

	struct UNIENGINE_API EntityArchetypeInfo {
		std::string Name;
		size_t Index;
		std::vector<ComponentType> ComponentTypes;
		//The size of a single entity
		size_t EntitySize;
		//How many entities can fit into one chunk
		size_t ChunkCapacity;
		//Current allocated entity count.
		size_t EntityCount = 0;
		//Current live entity count.
		size_t EntityAliveCount = 0;
		template<typename T>
		bool HasType();
		bool HasType(size_t typeID);
	};

	struct UNIENGINE_API EntityQuery final {
		size_t Index = 0;
		bool operator ==(const EntityQuery& other) const {
			return other.Index == Index;
		}
		bool operator !=(const EntityQuery& other) const {
			return other.Index != Index;
		}
		size_t operator() (EntityQuery const& key) const
		{
			return Index;
		}
		bool IsNull() const
		{
			return Index == 0;
		}
		template<typename T = ComponentBase, typename... Ts>
		void SetAllFilters(T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		void SetAnyFilters(T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		void SetNoneFilters(T arg, Ts... args);

		
		template<typename T1 = ComponentBase>
		void ToComponentDataArray(std::vector<T1>& container);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		void ToComponentDataArray(std::vector<T1>& container, const std::function<bool(T2&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		void ToComponentDataArray(std::vector<T1>& container, const std::function<bool(T2&, T3&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		void ToComponentDataArray(T1 filter, std::vector<T2>& container);
		void ToEntityArray(std::vector<Entity>& container);
		template<typename T1 = ComponentBase>
		void ToEntityArray(T1 filter, std::vector<Entity>& container);
		template<typename T1 = ComponentBase>
		void ToEntityArray(std::vector<Entity>& container, const std::function<bool(Entity, T1&)>& filterFunc);
		size_t GetEntityAmount();
	};



	struct UNIENGINE_API EntityComponentStorage {
		EntityArchetypeInfo* ArchetypeInfo;
		ComponentDataChunkArray* ChunkArray;
		EntityComponentStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array);
	};

	struct EntityQueryInfo {
		std::vector<ComponentType> AllComponentTypes;
		std::vector<ComponentType> AnyComponentTypes;
		std::vector<ComponentType> NoneComponentTypes;
		std::vector<EntityComponentStorage> QueriedStorages;
	};
#pragma endregion
#pragma endregion

#pragma endregion
	template<typename T>
	bool EntityArchetypeInfo::HasType()
	{
		for (auto i : ComponentTypes) {
			if (i.TypeID == typeid(T).hash_code()) return true;
		}
		return false;
	}
}
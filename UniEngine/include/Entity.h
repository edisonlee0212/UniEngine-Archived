#pragma once
#include "UniEngineAPI.h"
#include "Serializable.h"
namespace UniEngine {
#pragma region EntityManager
#pragma region Entity
	struct UNIENGINE_API ComponentType final {
		std::string m_name;
		size_t m_typeId = 0;
		size_t m_size = 0;
		size_t m_offset = 0;
		ComponentType() = default;
		ComponentType(const std::string& name, const size_t& id, const size_t& size);
		bool operator ==(const ComponentType& other) const;
		bool operator !=(const ComponentType& other) const;
	};
	struct UNIENGINE_API ComponentBase {
	};
	class PrivateComponentBase;
	struct UNIENGINE_API Entity final {
		unsigned m_index = 0;
		unsigned m_version = 0;
		Entity();
		bool operator ==(const Entity& other) const;
		bool operator !=(const Entity& other) const;
		size_t operator()(Entity const& key) const;
		[[nodiscard]] bool IsEnabled() const;
		void SetStatic(const bool& value) const;
		void SetEnabled(const bool& value) const;
		void SetEnabledSingle(const bool& value) const;
		[[nodiscard]] bool IsNull() const;
		[[nodiscard]] bool IsStatic() const;
		[[nodiscard]] bool IsDeleted() const;
		[[nodiscard]] bool IsValid() const;
		template<typename T = ComponentBase>
		void SetComponentData(const T& value) const;
		template<typename T = ComponentBase>
		T GetComponentData() const;
		template<typename T = ComponentBase>
		[[nodiscard]] bool HasComponentData() const;
		template <typename T = PrivateComponentBase>
		std::unique_ptr<T>& GetPrivateComponent() const;
		template <typename T = PrivateComponentBase>
		void SetPrivateComponent(std::unique_ptr<T> value) const;
		template <typename T = PrivateComponentBase>
		[[nodiscard]] bool RemovePrivateComponent() const;
		template <typename T = PrivateComponentBase>
		[[nodiscard]] bool HasPrivateComponent() const;
		[[nodiscard]] inline std::string GetName() const;
		inline void SetName(const std::string& name) const;
	};
#pragma region Storage

	class UNIENGINE_API PrivateComponentBase : public Serializable {
		friend class EntityManager;
		friend class EditorManager;
		friend struct PrivateComponentElement;
		friend class SerializationManager;
		bool m_enabled = false;
		Entity m_owner;
	public:
		[[nodiscard]] Entity GetOwner() const;
		void SetEnabled(const bool& value);
		[[nodiscard]] bool IsEnabled() const;
		virtual void Init();
		virtual void OnEnable();
		virtual void OnDisable();
		virtual void OnEntityEnable();
		virtual void OnEntityDisable();
		virtual void OnGui();
		void Serialize(YAML::Emitter& out) override;
		void Deserialize(const YAML::Node& in) override;
		~PrivateComponentBase() override;
	};

	template<typename T>
	ComponentType Typeof() {
		ComponentType type;
		type.m_name = std::string(typeid(T).name());
		type.m_size = sizeof(T);
		type.m_offset = 0;
		type.m_typeId = typeid(T).hash_code();
		return type;
	}

	const size_t ARCHETYPECHUNK_SIZE = 16384;

	struct ComponentDataChunk {
		void* m_data;
		template<typename T>
		T GetData(const size_t& offset);
		[[nodiscard]] ComponentBase* GetDataPointer(const size_t& offset) const;
		template<typename T>
		void SetData(const size_t& offset, const T& data);
		void SetData(const size_t& offset, const size_t& size, ComponentBase* data) const;
		void ClearData(const size_t& offset, const size_t& size) const;
	};

	struct ComponentDataChunkArray {
		std::vector<Entity> Entities;
		std::vector<ComponentDataChunk> Chunks;
	};

	struct UNIENGINE_API EntityArchetype final {
		size_t m_index;
		[[nodiscard]] bool IsNull() const;
		[[nodiscard]] bool IsValid() const;
		[[nodiscard]] std::string GetName() const;
	};

	struct UNIENGINE_API PrivateComponentElement
	{
		std::string m_name;
		size_t m_typeId;
		std::unique_ptr<PrivateComponentBase> m_privateComponentData;
		PrivateComponentElement(const std::string& name, const size_t& id, std::unique_ptr<PrivateComponentBase> data, const Entity& owner);
		void ResetOwner(const Entity& newOwner) const;
	};

	struct EntityInfo {
		friend class PrivateComponentStorage;
		std::string m_name;
		unsigned m_version = 1;
		bool m_static = false;
		bool m_enabled = true;
		Entity m_parent = Entity();
		std::vector<PrivateComponentElement> m_privateComponentElements;
		std::vector<Entity> m_children;
		size_t m_archetypeInfoIndex;
		size_t m_chunkArrayIndex;
	};

	struct UNIENGINE_API EntityArchetypeInfo {
		std::string m_name;
		size_t m_index = 0;
		std::vector<ComponentType> m_componentTypes;
		size_t m_entitySize = 0;
		size_t m_chunkCapacity = 0;
		size_t m_entityCount = 0;
		size_t m_entityAliveCount = 0;
		template<typename T>
		bool HasType();
		bool HasType(const size_t& typeID);
	};

	struct UNIENGINE_API EntityQuery final {
		size_t m_index = 0;
		bool operator ==(const EntityQuery& other) const;
		bool operator !=(const EntityQuery& other) const;
		size_t operator()(const EntityQuery& key) const;
		[[nodiscard]] bool IsNull() const;
		template<typename T = ComponentBase, typename... Ts>
		void SetAllFilters(T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		void SetAnyFilters(T arg, Ts... args);
		template<typename T = ComponentBase, typename... Ts>
		void SetNoneFilters(T arg, Ts... args);
		template<typename T1 = ComponentBase>
		void ToComponentDataArray(std::vector<T1>& container);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		void ToComponentDataArray(std::vector<T1>& container, const std::function<bool(const T2&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase, typename T3 = ComponentBase>
		void ToComponentDataArray(std::vector<T1>& container, const std::function<bool(const T2&, const T3&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		void ToComponentDataArray(const T1& filter, std::vector<T2>& container);
		void ToEntityArray(std::vector<Entity>& container) const;
		template<typename T1 = ComponentBase>
		void ToEntityArray(const T1& filter, std::vector<Entity>& container);
		template<typename T1 = ComponentBase>
		void ToEntityArray(std::vector<Entity>& container, const std::function<bool(const Entity&, const T1&)>& filterFunc);
		template<typename T1 = ComponentBase, typename T2 = ComponentBase>
		void ToEntityArray(std::vector<Entity>& container, const std::function<bool(const Entity&, const T1&, const T2&)>& filterFunc);
		[[nodiscard]] size_t GetEntityAmount() const;
	};
	struct UNIENGINE_API EntityComponentStorage {
		EntityArchetypeInfo* m_archetypeInfo;
		ComponentDataChunkArray* m_chunkArray;
		EntityComponentStorage(EntityArchetypeInfo* info, ComponentDataChunkArray* array);
	};
	struct EntityQueryInfo {
		std::vector<ComponentType> m_allComponentTypes;
		std::vector<ComponentType> m_anyComponentTypes;
		std::vector<ComponentType> m_noneComponentTypes;
		std::vector<EntityComponentStorage> m_queriedStorage;
	};
#pragma endregion
#pragma endregion
#pragma endregion
	template<typename T>
	bool EntityArchetypeInfo::HasType()
	{
		for (const auto& i : m_componentTypes) {
			if (i.m_typeId == typeid(T).hash_code()) return true;
		}
		return false;
	}
}
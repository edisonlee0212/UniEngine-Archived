#pragma once
#include "Core.h"
#include "FixedDataStorage.h"
#include "SharedComponentStorage.h"
#include "ComponentStorage.h"
namespace UniEngine {
	class EntityCollection
	{
		std::vector<Entity*> _Entities;
		FixedDataStorage* _FixedDataStorage;
		SharedComponentStorage* _SharedComponentStorage;
		ComponentStorage* _ComponentStorage;
		friend class World;
		EntityCollection();

		template<typename T>
		size_t GetArchetypeSize(T arg);
		template<typename T, typename... Ts>
		size_t GetArchetypeSize(T arg, Ts... args);


	public:
		template<typename T, typename... Ts>
		void CreateEntityArchetype(T arg, Ts... args);


		void SetParent(Entity* child, Entity* parent);
		std::vector<Entity*>* Entities();
		Entity* CreateEntity();
		void DeleteEntity(Entity* entity);
		void DeleteEntity(unsigned key);
		Entity* GetEntity(unsigned key);
		size_t GetEntitiesAmount();

		template <typename T>
		T* GetSharedComponent(Entity* entity);
		template <typename T>
		void SetSharedComponent(Entity* entity, T* value);

		template <typename T>
		T GetComponent(Entity* entity);
		template <typename T>
		void SetComponent(Entity* entity, T value);

		template <typename T>
		void SetFixedData(Entity* entity, T value);
		template <typename T>
		T GetFixedData(Entity* entity);

		template <typename T>
		std::vector<Entity*>* QueryEntities(T* value);
		template <typename T>
		std::vector<std::pair<SharedComponentBase*, OC*>*>* QuerySharedComponents();
	};

#pragma region EntityArchetype
	template<typename T>
	inline size_t EntityCollection::GetArchetypeSize(T arg)
	{
		return sizeof(T);
	}

	template<typename T, typename ...Ts>
	inline size_t EntityCollection::GetArchetypeSize(T arg, Ts... args)
	{
		return sizeof(T) + GetArchetypeSize(args...);
	}

	template<typename T, typename ...Ts>
	inline void EntityCollection::CreateEntityArchetype(T arg, Ts... args)
	{
		size_t archetypeSize = GetArchetypeSize(arg, args...);

	}
#pragma endregion

#pragma region Get & Set
	template<typename T>
	inline T* EntityCollection::GetSharedComponent(Entity* entity)
	{
		return _SharedComponentStorage->GetSC<T>(entity);
	}
	template<typename T>
	inline void EntityCollection::SetSharedComponent(Entity* entity, T* value)
	{
		_SharedComponentStorage->SetSC<T>(entity, value);
	}
	template<typename T>
	inline T EntityCollection::GetComponent(Entity* entity)
	{
		return T();
	}
	template<typename T>
	inline void EntityCollection::SetComponent(Entity* entity, T value)
	{
	}
	template<typename T>
	inline void EntityCollection::SetFixedData(Entity* entity, T value)
	{
		_FixedDataStorage->SetFixedData(entity->_Key, value);
	}
	template<typename T>
	inline T EntityCollection::GetFixedData(Entity* entity)
	{
		return _FixedDataStorage->GetFixedData<T>(entity->_Key);
	}
#pragma endregion
	
#pragma region Query
	template<typename T>
	inline std::vector<Entity*>* EntityCollection::QueryEntities(T* value)
	{
		return _SharedComponentStorage->GetOsList<T>(value);
	}

	template<typename T>
	inline std::vector<std::pair<SharedComponentBase*, OC*>*>* EntityCollection::QuerySharedComponents()
	{
		return _SharedComponentStorage->GetSCOCsList<T>();
	}
#pragma endregion
}
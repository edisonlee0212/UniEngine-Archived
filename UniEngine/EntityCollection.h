#pragma once
#include "Core.h"
#include "FixedDataStorage.h"
namespace UniEngine {
	class EntityCollection
	{
		std::vector<Entity*> _Entities;
		FixedDataStorage* _FixedDataStorage;
		friend class World;
		EntityCollection();
	public:
		void SetParent(Entity* child, Entity* parent);
		std::vector<Entity*>* Entities();
		Entity* CreateEntity();
		void DeleteEntity(Entity* entity);
		void DeleteEntity(unsigned key);
		Entity* GetEntity(unsigned key);
		size_t GetEntitiesAmount();
		template <typename T>
		T GetComponent(Entity* entity);
		template <typename T>
		void SetComponent(Entity* entity, T value);
		template <typename T>
		void SetFixedData(Entity* entity, T value);
		template <typename T>
		T GetFixedData(Entity* entity);
	};
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
}
#pragma once
#include "Misc.h"
#include "Core.h"
namespace UniEngine {
	class EntityManager
	{
		std::vector<Entity*> _Entities;
		FixedDataStorage* _FixedDataStorage;

		friend class World;
		EntityManager();
	public:
		Entity* CreateEntity();
		void DeleteEntity(Entity* entity);
		void DeleteEntity(uint key);
		Entity* GetEntity(uint key);
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
	inline T EntityManager::GetComponent(Entity* entity)
	{
		return T();
	}
	template<typename T>
	inline void EntityManager::SetComponent(Entity* entity, T value)
	{
	}
	template<typename T>
	inline void EntityManager::SetFixedData(Entity* entity, T value)
	{
		_FixedDataStorage.SetFixedData(entity->_Key, value);
	}
	template<typename T>
	inline T EntityManager::GetFixedData(Entity* entity)
	{
		return _FixedDataStorage.GetFixedData<T>(entity->_Key);
	}
}
#pragma once
#include "Core.h"
#include "FixedDataStorage.h"
#include "SharedComponentStorage.h"
namespace UniEngine {
	class EntityCollection
	{
		std::vector<Entity*> _Entities;
		FixedDataStorage* _FixedDataStorage;
		SharedComponentStorage* _SharedComponentStorage;
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
		std::vector<Entity*> QueryEntityBySharedComponent(T* value);
		template <typename T>
		std::vector<T*> QuerySharedComponent();
	};
	template<typename T>
	inline T* EntityCollection::GetSharedComponent(Entity* entity)
	{
		return _SharedComponentStorage->GetSharedComponent<T>(entity);
	}
	template<typename T>
	inline void EntityCollection::SetSharedComponent(Entity* entity, T* value)
	{
		_SharedComponentStorage->SetSharedComponent<T>(entity, value);
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
	template<typename T>
	inline std::vector<Entity*> EntityCollection::QueryEntityBySharedComponent(T* value)
	{
		auto list = std::vector<Entity*>();
		SharedComponentBase* in = dynamic_cast<SharedComponentBase*>(value);
		auto key = typeid(T).hash_code();
		auto search = _SharedComponentStorage->_SharedComponentsStorage.find(key);
		if (search != _SharedComponentStorage->_SharedComponentsStorage.end()) {
			//If we find the shared component class, we look for the specific shared component
			std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* result = search->second;
			auto insearch = result->find(in->GetHashCode());
			if (insearch != result->end()) {
				//If we find the specific shared component, we insert the entity to the list. Note that 
				std::unordered_map<unsigned, Entity*>* elist = insearch->second->second;
				for (std::pair<unsigned, Entity*> i : *elist) {
					list.push_back(i.second);
				}
			}
		}

		return list;
	}
	template<typename T>
	inline std::vector<T*> EntityCollection::QuerySharedComponent()
	{
		auto list = std::vector<T*>();

		auto key = typeid(T).hash_code();
		auto search = _SharedComponentStorage->_SharedComponentsStorage.find(key);
		if (search != _SharedComponentStorage->_SharedComponentsStorage.end()) {
			//If we find the shared component class, we look for the specific shared component
			std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* result = search->second;
			for (std::pair<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*> i : *result) {
				list.push_back(dynamic_cast<T*>(i.second->first));
			}
		}

		return list;
	}
}
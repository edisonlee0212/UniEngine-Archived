#pragma once
#include "Core.h"
namespace UniEngine {
	class SharedComponentStorage
	{
		friend class EntityCollection;
		//<classtypekey, <objkey, pair<obj, entities>>>
		std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>*> _SharedComponentsStorage;

	public:
		SharedComponentStorage();

		template <typename T>
		T* GetSharedComponent(Entity* entity);

		template <typename T>
		void SetSharedComponent(Entity* entity, T* value);
	};
	template<typename T>
	inline T* SharedComponentStorage::GetSharedComponent(Entity* entity)
	{
		//Get the hashcode of the object class
		auto key = typeid(T).hash_code();
		auto search = _SharedComponentsStorage.find(key);
		if (search != _SharedComponentsStorage.end()) {
			//If we find the shared component class, we look for the specific shared component
			std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* result = search->second;
			for (std::pair<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*> i : *result)
			{
				std::unordered_map<unsigned, Entity*>* map = i.second->second;
				auto insearch = map->find(entity->Key());
				if (insearch != map->end()) {
					return dynamic_cast<T*>(i.second->first);
				}
			}
		}
		return nullptr;
	}
	template<typename T>
	inline void SharedComponentStorage::SetSharedComponent(Entity* entity, T* value)
	{
		SharedComponentBase* in = dynamic_cast<SharedComponentBase*>(value);
		//Get the hashcode of the object class
		auto key = typeid(T).hash_code();
		auto search = _SharedComponentsStorage.find(key);
		if (search != _SharedComponentsStorage.end()) {
			//If we find the shared component class, we look for the specific shared component
			std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* result = search->second;
			auto insearch = result->find(in->GetHashCode());
			if (insearch != result->end()) {
				//If we find the specific shared component, we insert the entity to the list. Note that 
				std::unordered_map<unsigned, Entity*>* list = insearch->second->second;
				auto esearch = list->find(entity->Key());
				list->insert({entity->Key(), entity});
			}
			else {
				//If we can't find the specific shared component.
				auto map = new std::unordered_map<unsigned, Entity*>();
				map->insert({ entity->Key(), entity });
				auto pair = new std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>(in, map);
				result->insert({ in->GetHashCode(), pair });
			}
		}
		else {
			//If we cant find the class at all.
			auto map = new std::unordered_map<unsigned, Entity*>();
			map->insert({ entity->Key(), entity });
			auto pair = new std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>(in, map);
			auto cmap = new std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>();
			cmap->insert({in->GetHashCode(), pair});
			_SharedComponentsStorage.insert({key, cmap});
		}
	}
}
#pragma once
#include "Core.h"
namespace UniEngine {
	class SharedComponentStorage
	{
		friend class EntityCollection;
		//umap<classtypehashcode, umap<sharedcomponenthashcode, pair<sharedcomponent, umap<entitykey, entity>>>>
		std::unordered_map<std::size_t, 
			std::unordered_map<std::size_t, 
				std::pair<SharedComponentBase*, 
					std::unordered_map<unsigned, Entity*>*>*>*> _SharedComponentsStorage;

	public:
		SharedComponentStorage();

		void DeleteEntity(Entity* entity);

		template <typename T>
		std::unordered_map<std::size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* GetSharedComponentMap();

		template <typename T>
		std::unordered_map<unsigned, Entity*>* GetEntitiesMap(T* value);

		template <typename T>
		T* GetSharedComponent(Entity* entity);

		template <typename T>
		void SetSharedComponent(Entity* entity, T* value);
	};

	template<typename T>
	inline std::unordered_map<std::size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* SharedComponentStorage::GetSharedComponentMap()
	{
		auto key = typeid(T).hash_code();
		auto search = _SharedComponentsStorage.find(key);
		if (search != _SharedComponentsStorage.end()) {
			return search->second;
		}
		return nullptr;
	}

	template<typename T>
	inline std::unordered_map<unsigned, Entity*>* SharedComponentStorage::GetEntitiesMap(T* value)
	{
		SharedComponentBase* in = dynamic_cast<SharedComponentBase*>(value);
		std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>* result = GetSharedComponentMap<T>();
		if (result != nullptr) {
			auto insearch = result->find(in->GetHashCode());
			if (insearch != result->end()) {
				return insearch->second->second;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline T* SharedComponentStorage::GetSharedComponent(Entity* entity)
	{
		auto result = GetSharedComponentMap<T>();
		if (result != nullptr) {
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
		auto key = typeid(T).hash_code();
		auto result = GetSharedComponentMap<T>();
		if (result != nullptr) {
			auto insearch = result->find(in->GetHashCode());
			if (insearch != result->end()) {
				//If we find the specific shared component, we insert the entity to the list. Note that 
				std::unordered_map<unsigned, Entity*>* list = insearch->second->second;
				auto esearch = list->find(entity->Key());
				list->insert({ entity->Key(), entity });
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
			auto map = new std::unordered_map<unsigned, Entity*>();
			map->insert({ entity->Key(), entity });
			auto pair = new std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>(in, map);
			auto cmap = new std::unordered_map<size_t, std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>();
			cmap->insert({ in->GetHashCode(), pair });
			_SharedComponentsStorage.insert({ key, cmap });
		}
	}
}
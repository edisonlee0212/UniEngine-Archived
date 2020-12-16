#pragma once
#include "Entity.h"
#include "Debug.h"
namespace UniEngine
{
	struct POwnersCollection {
		std::unordered_map<Entity, size_t, Entity> _OwnersMap;
		std::vector<Entity> _OwnersList;
		POwnersCollection() {
			_OwnersList = std::vector<Entity>();
			_OwnersMap = std::unordered_map<Entity, size_t, Entity>();
		}
	};
	class PrivateComponentStorage
	{
		std::unordered_map<std::size_t, size_t> _POwnersCollectionsMap;
		std::vector<std::pair<size_t, std::unique_ptr<POwnersCollection>>> _POwnersCollectionsList;
	public:
		void RemovePrivateComponent(Entity entity, size_t typeID);
		void DeleteEntity(Entity entity);
		template <typename T = PrivateComponentBase>
		void SetPrivateComponent(Entity entity);
		void SetPrivateComponent(Entity entity, size_t id);
		template <typename T = PrivateComponentBase>
		void RemovePrivateComponent(Entity entity);
		template <typename T>
		const std::vector<Entity>* GetOwnersList();
	};

	template <typename T>
	void PrivateComponentStorage::SetPrivateComponent(Entity entity)
	{
		size_t id = typeid(T).hash_code();
		auto search = _POwnersCollectionsMap.find(id);
		if (search != _POwnersCollectionsMap.end())
		{
			auto insearch = _POwnersCollectionsList[search->second].second->_OwnersMap.find(entity);
			if (insearch == _POwnersCollectionsList[search->second].second->_OwnersMap.end()) {
				_POwnersCollectionsList[search->second].second->_OwnersMap.insert({ entity, _POwnersCollectionsList[search->second].second->_OwnersList.size() });
				_POwnersCollectionsList[search->second].second->_OwnersList.push_back(entity);
			}
		}else
		{
			std::unique_ptr<POwnersCollection> collection = std::make_unique<POwnersCollection>();
			collection->_OwnersMap.insert({ entity, 0 });
			collection->_OwnersList.push_back(entity);
			_POwnersCollectionsMap.insert({ id, _POwnersCollectionsList.size() });
			_POwnersCollectionsList.push_back(std::make_pair(id, std::move(collection)));
		}
	}

	template <typename T>
	void PrivateComponentStorage::RemovePrivateComponent(Entity entity)
	{
		RemovePrivateComponent(entity, typeid(T).hash_code());
	}

	template <typename T>
	const std::vector<Entity>* PrivateComponentStorage::GetOwnersList()
	{
		auto search = _POwnersCollectionsMap.find(typeid(T).hash_code());
		if(search != _POwnersCollectionsMap.end())
		{
			return &_POwnersCollectionsList[search->second].second->_OwnersList;
		}
		return nullptr;
	}
}



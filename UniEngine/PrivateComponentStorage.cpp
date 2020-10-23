#include "pch.h"
#include "EntityManager.h"
#include "PrivateComponentStorage.h"

void UniEngine::PrivateComponentStorage::RemovePrivateComponent(Entity entity, size_t typeID)
{
	auto search = _POwnersCollectionsMap.find(typeID);
	if (search != _POwnersCollectionsMap.end())
	{
		auto& collection = _POwnersCollectionsList[search->second].second;
		const auto entitySearch = collection->_OwnersMap.find(entity);
		if (entitySearch != collection->_OwnersMap.end())
		{
			if (entity != entitySearch->first) {
				Debug::Error("Entity already deleted!");
				return;
			}
			if(collection->_OwnersList.size() == 1)
			{
				const auto eraseHash = typeID;
				const auto eraseIndex = search->second;
				const auto backHash = _POwnersCollectionsList.back().first;
				_POwnersCollectionsMap[backHash] = eraseIndex;
				std::swap(_POwnersCollectionsList[eraseIndex], _POwnersCollectionsList.back());
				_POwnersCollectionsMap.erase(eraseHash);
				_POwnersCollectionsList.pop_back();
			}else
			{
				const auto eraseIndex = entitySearch->second;
				const auto backEntity = collection->_OwnersList.back();
				collection->_OwnersMap[backEntity] = eraseIndex;
				collection->_OwnersMap.erase(entity);
				collection->_OwnersList[eraseIndex] = backEntity;
				collection->_OwnersList.pop_back();
			}
		}
	}
}

void UniEngine::PrivateComponentStorage::DeleteEntity(Entity entity)
{
	for (auto& element : EntityManager::_EntityInfos->at(entity.Index).PrivateComponentElements)
	{
		size_t id = element.TypeID;
		RemovePrivateComponent(entity, id);
	}
}

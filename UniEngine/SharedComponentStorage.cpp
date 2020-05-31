#include "SharedComponentStorage.h"

UniEngine::SharedComponentStorage::SharedComponentStorage()
{
	_SharedComponentsStorage = std::unordered_map<std::size_t,
		std::unordered_map<std::size_t,
		std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>*>();
}

void UniEngine::SharedComponentStorage::DeleteEntity(Entity* entity)
{
	for (auto i : _SharedComponentsStorage) {
		for (auto j : *i.second) {
			j.second->second->erase(entity->Key());
		}
	}
}

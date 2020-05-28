#include "SharedComponentStorage.h"

UniEngine::SharedComponentStorage::SharedComponentStorage()
{
	_SharedComponentsStorage = std::unordered_map<std::size_t,
		std::unordered_map<std::size_t,
		std::pair<SharedComponentBase*, std::unordered_map<unsigned, Entity*>*>*>*>();
}

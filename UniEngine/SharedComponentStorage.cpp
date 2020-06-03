#include "SharedComponentStorage.h"

UniEngine::SharedComponentStorage::SharedComponentStorage()
{
	_SCsStorage = SCOCsStorage();
}

bool UniEngine::SharedComponentStorage::RemoveSC(SCOCC* scocc, Entity* entity)
{
	SCOCsList* list = scocc->second;
	for (SCOC* i : *list) {
		//Go through each sc
		OsIMap* inmap = i->second->first;
		auto search = inmap->find(entity);
		if (search != inmap->end()) {
			//We find the entity
			OsList* inlist = i->second->second;
			Index inindex = search->second;
			Entity* backEntity = inlist->back();
			inmap->at(backEntity) = inindex;
			inlist->at(inindex) = inlist->back();
			inlist->pop_back();
			inmap->erase(entity);
			if (inlist->empty()) {
				//If the sc doesn't belong to any entity, we remove the sc
				delete inmap;
				delete inlist;
				delete i->second;
				SCOCsIMap* map = scocc->first;
				Index index = map->at(i->first->GetHashCode());
				SCOC* backScoc = list->back();
				map->at(backScoc->first->GetHashCode()) = index;
				list->at(index) = list->back();
				list->pop_back();
				map->erase(i->first->GetHashCode());
				delete i;
			}
			return true;
		}
	}
	return false;
}

void UniEngine::SharedComponentStorage::DeleteEntity(Entity* entity)
{
	for (auto i : _SCsStorage) {
		RemoveSC(i.second, entity);
	}
}

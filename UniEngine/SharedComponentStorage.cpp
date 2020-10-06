#include "pch.h"
#include "SharedComponentStorage.h"

#include "Debug.h"

bool UniEngine::ComponentTypeComparator(ComponentType a, ComponentType b)
{
	return a.TypeID < b.TypeID;
}

#pragma region SharedComponentStorage

UniEngine::SharedComponentStorage::SharedComponentStorage()
{
	_SCCollectionsMap = std::unordered_map<std::size_t, Index>();
	_SCCollectionsList = std::vector<std::unique_ptr<SCCollection>>();
}


void UniEngine::SharedComponentStorage::DeleteEntity(Entity entity)
{
	for (auto& scc : _SCCollectionsList) {
		for (size_t i = 0; i < scc->_OwnersCollectionsList.size(); i++) {
			std::unique_ptr<OwnersCollection>* oc = &scc->_OwnersCollectionsList[i];
			auto entitySearch = oc->get()->_OwnersMap.find(entity);
			if (entitySearch != oc->get()->_OwnersMap.end()) {
				if (entity != entitySearch->first) {
					Debug::Error("Entity already deleted!");
				}
				if (oc->get()->_OwnersList.size() == 1) {
					auto eraseHash = scc->_SCList[i].get()->GetHashCode();
					Index index = scc->_OwnersCollectionsMap.at(eraseHash);
					scc->_OwnersCollectionsMap.at(scc->_SCList.back().get()->GetHashCode()) = index;
					scc->_OwnersCollectionsMap.erase(eraseHash);
					scc->_SCList[index] = scc->_SCList.back();
					scc->_OwnersCollectionsList[index] = std::move(scc->_OwnersCollectionsList.back());
					scc->_SCList.pop_back();
					scc->_OwnersCollectionsList.pop_back();
				}
				else {
					Index index = entitySearch->second;
					oc->get()->_OwnersMap.at(oc->get()->_OwnersList.back()) = index;
					oc->get()->_OwnersMap.erase(entity);
					oc->get()->_OwnersList[index] = oc->get()->_OwnersList.back();
					oc->get()->_OwnersList.pop_back();
				}
			}
		}
	}
}
#pragma endregion

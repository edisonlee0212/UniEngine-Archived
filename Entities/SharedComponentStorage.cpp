#include "pch.h"
#include "SharedComponentStorage.h"

bool UniEngine::ComponentTypeComparator(ComponentType a, ComponentType b)
{
	return a.TypeID < b.TypeID;
}

#pragma region SharedComponentStorage

UniEngine::SharedComponentStorage::SharedComponentStorage()
{
	_SCCollectionsMap = std::unordered_map<std::size_t, Index>();
	_SCCollectionsList = std::vector<SCCollection*>();
}


void UniEngine::SharedComponentStorage::DeleteEntity(Entity entity)
{
	for (auto scc : _SCCollectionsList) {
		size_t ocSize = scc->_OwnersCollectionsList.size();
		for (size_t i = 0; i < ocSize; i++) {
			OwnersCollection* oc = scc->_OwnersCollectionsList[i];
			auto entitySearch = oc->_OwnersMap.find(entity);
			if (entitySearch != oc->_OwnersMap.end()) {
				if (entity != entitySearch->first) {
					Debug::Error("Entity already deleted!");
				}
				if (oc->_OwnersList.size() == 1) {
					auto eraseHash = dynamic_cast<SharedComponentBase*>(scc->_SCList[i])->GetHashCode();
					Index index = scc->_OwnersCollectionsMap.at(eraseHash);
					scc->_OwnersCollectionsMap.at(dynamic_cast<SharedComponentBase*>(scc->_SCList.back())->GetHashCode()) = index;
					scc->_OwnersCollectionsMap.erase(eraseHash);
					scc->_SCList[index] = scc->_SCList.back();
					scc->_OwnersCollectionsList[index] = scc->_OwnersCollectionsList.back();
					scc->_SCList.pop_back();
					scc->_OwnersCollectionsList.pop_back();
					delete oc;
				}
				else {
					Index index = entitySearch->second;
					oc->_OwnersMap.at(oc->_OwnersList.back()) = index;
					oc->_OwnersMap.erase(entity);
					oc->_OwnersList[index] = oc->_OwnersList.back();
					oc->_OwnersList.pop_back();
				}
			}
		}
	}
}
#pragma endregion

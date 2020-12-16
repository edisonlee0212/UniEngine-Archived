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
					auto eraseHash = scc->_SCList[i]->GetHashCode();
					Index index = scc->_OwnersCollectionsMap.at(eraseHash);
					scc->_OwnersCollectionsMap.at(scc->_SCList.back()->GetHashCode()) = index;
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

std::unique_ptr<UniEngine::SCCollection>* UniEngine::SharedComponentStorage::GetSCCollection(size_t hashCode)
{
	auto search = _SCCollectionsMap.find(hashCode);
	if (search != _SCCollectionsMap.end()) {
		Index index = search->second;
		return &_SCCollectionsList[index];
	}
	return nullptr;
}

void UniEngine::SharedComponentStorage::SetSharedComponent(Entity entity, const std::string& name, size_t id,
                                                           std::shared_ptr<SharedComponentBase>& value)
{
	RemoveSharedComponent(entity, id);
	std::unique_ptr<SCCollection>* scc = GetSCCollection(id);
	std::shared_ptr<SharedComponentBase> scp = value;
	if (scc == nullptr) {
		std::unique_ptr<SCCollection> nscc = std::make_unique<SCCollection>(name);
		std::unique_ptr<OwnersCollection> noc = std::make_unique<OwnersCollection>();
		noc->_OwnersMap.insert({ entity, 0 });
		noc->_OwnersList.push_back(entity);

		nscc->_OwnersCollectionsMap.insert({ scp->GetHashCode(), 0 });
		nscc->_OwnersCollectionsList.push_back(std::move(noc));
		nscc->_SCList.push_back(std::move(scp));

		_SCCollectionsMap.insert({ id, _SCCollectionsList.size() });
		_SCCollectionsList.push_back(std::move(nscc));
	}
	else {
		const auto key = scp->GetHashCode();
		const auto search = scc->get()->_OwnersCollectionsMap.find(key);
		if (search == scc->get()->_OwnersCollectionsMap.end()) {
			std::unique_ptr<OwnersCollection> noc = std::make_unique<OwnersCollection>();
			noc->_OwnersMap.insert({ entity, 0 });
			noc->_OwnersList.push_back(entity);

			scc->get()->_OwnersCollectionsMap.insert({ scp->GetHashCode(), scc->get()->_OwnersCollectionsList.size() });
			scc->get()->_OwnersCollectionsList.push_back(std::move(noc));
			scc->get()->_SCList.push_back(std::move(scp));
		}
		else {
			const Index index = search->second;
			std::unique_ptr<OwnersCollection>* oc = &scc->get()->_OwnersCollectionsList[index];
			const auto entitySearch = oc->get()->_OwnersMap.find(entity);
			if (entitySearch == oc->get()->_OwnersMap.end()) {
				oc->get()->_OwnersMap.insert({ entity, oc->get()->_OwnersList.size() });
				oc->get()->_OwnersList.push_back(entity);
			}
		}
	}
}

bool UniEngine::SharedComponentStorage::RemoveSharedComponent(Entity entity, size_t hashCode)
{
	std::unique_ptr<SCCollection>* scc = GetSCCollection(hashCode);
	if (scc == nullptr) return false;
	const auto ocSize = scc->get()->_OwnersCollectionsList.size();
	for (size_t i = 0; i < ocSize; i++) {
		std::unique_ptr<OwnersCollection>* oc = &scc->get()->_OwnersCollectionsList[i];
		auto entitySearch = oc->get()->_OwnersMap.find(entity);
		if (entitySearch != oc->get()->_OwnersMap.end()) {
			if (entity != entitySearch->first) {
				Debug::Error("Entity already deleted!");
				return false;
			}
			if (oc->get()->_OwnersList.size() == 1) {
				const auto eraseHash = scc->get()->_SCList[i]->GetHashCode();
				const auto index = scc->get()->_OwnersCollectionsMap.at(eraseHash);
				scc->get()->_OwnersCollectionsMap.at(scc->get()->_SCList.back()->GetHashCode()) = index;
				scc->get()->_OwnersCollectionsMap.erase(eraseHash);
				scc->get()->_SCList[index] = std::move(scc->get()->_SCList.back());
				scc->get()->_OwnersCollectionsList[index] = std::move(scc->get()->_OwnersCollectionsList.back());
				scc->get()->_SCList.pop_back();
				scc->get()->_OwnersCollectionsList.pop_back();
			}
			else {
				const Index index = entitySearch->second;
				oc->get()->_OwnersMap.at(oc->get()->_OwnersList.back()) = index;
				oc->get()->_OwnersMap.erase(entity);
				oc->get()->_OwnersList[index] = oc->get()->_OwnersList.back();
				oc->get()->_OwnersList.pop_back();
			}
			return true;
		}
	}
	return false;
}
#pragma endregion

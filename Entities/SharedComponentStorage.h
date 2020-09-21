#pragma once
#include "Entity.h"
namespace UniEngine {
	ENTITIES_API bool ComponentTypeComparator(ComponentType a, ComponentType b);
#pragma region SharedComponentStorage
	typedef std::size_t Index;

	typedef std::unordered_map<Entity, Index, Entity> OwnersMap;
	struct OwnersCollection {
		OwnersMap _OwnersMap;
		std::vector<Entity> _OwnersList;
		OwnersCollection() {
			_OwnersList = std::vector<Entity>();
			_OwnersMap = OwnersMap();
		}
	};

	struct SCCollection {
		std::unordered_map<std::size_t, Index> _OwnersCollectionsMap;
		std::vector<std::shared_ptr<SharedComponentBase>> _SCList;
		std::vector<std::unique_ptr<OwnersCollection>> _OwnersCollectionsList;
		SCCollection() {
			_OwnersCollectionsMap = std::unordered_map<std::size_t, Index>();
			_SCList = std::vector<std::shared_ptr<SharedComponentBase>>();
			_OwnersCollectionsList = std::vector<std::unique_ptr<OwnersCollection>>();
		}
	};

	class SharedComponentStorage
	{
		std::unordered_map<std::size_t, Index> _SCCollectionsMap;
		std::vector<std::unique_ptr<SCCollection>> _SCCollectionsList;

	public:
		SharedComponentStorage();

		void DeleteEntity(Entity entity);

		template <typename T>
		std::unique_ptr<SCCollection>* GetSCCollection();

		template <typename T>
		std::unordered_map<std::size_t, Index>* GetOwnersCollectionsMap();

		template <typename T>
		std::vector<std::unique_ptr<OwnersCollection>>* GetOwnersCollectionsList();

		template <typename T>
		std::vector<std::shared_ptr<T>>* GetSCList();

		template <typename T>
		std::unique_ptr<OwnersCollection>* GetOwnersCollection(std::shared_ptr<T> value);

		template <typename T>
		OwnersMap* GetOwnersMap(std::shared_ptr<T> value);

		template <typename T>
		std::vector<Entity>* GetOwnersList(std::shared_ptr<T> value);

		template <typename T>
		void SetSharedComponent(Entity entity, std::shared_ptr<T> value);

		template <typename T>
		bool RemoveSharedComponent(Entity entity);

		template <typename T>
		std::shared_ptr<T> GetSharedComponent(Entity entity);


	};

	template<typename T>
	std::unique_ptr<SCCollection>* SharedComponentStorage::GetSCCollection()
	{
		auto key = typeid(T).hash_code();
		auto search = _SCCollectionsMap.find(key);
		if (search != _SCCollectionsMap.end()) {
			Index index = search->second;
			return &_SCCollectionsList[index];
		}
		return nullptr;
	}


	template<typename T>
	std::unordered_map<std::size_t, Index>* SharedComponentStorage::GetOwnersCollectionsMap()
	{
		std::unique_ptr<SCCollection>* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		return &scc->get()->_OwnersCollectionsMap;
	}

	template<typename T>
	std::vector<std::unique_ptr<OwnersCollection>>* SharedComponentStorage::GetOwnersCollectionsList()
	{
		std::unique_ptr<SCCollection>* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		return &scc->get()->_OwnersCollectionsList;
	}

	template<typename T>
	std::vector<std::shared_ptr<T>>* SharedComponentStorage::GetSCList()
	{
		std::unique_ptr<SCCollection>* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		return reinterpret_cast<std::vector<std::shared_ptr<T>>*>(&scc->get()->_SCList);
	}

	template<typename T>
	std::unique_ptr<OwnersCollection>* SharedComponentStorage::GetOwnersCollection(std::shared_ptr<T> value)
	{
		std::unique_ptr<SCCollection>* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		auto key = dynamic_cast<SharedComponentBase*>(value.get())->GetHashCode();
		auto search = scc->get()->_OwnersCollectionsMap.find(key);
		if (search != scc->get()->_OwnersCollectionsMap.end()) {
			Index index = search->second;
			return &scc->get()->_OwnersCollectionsList[index];
		}
		return nullptr;
	}

	template<typename T>
	OwnersMap* SharedComponentStorage::GetOwnersMap(std::shared_ptr<T> value)
	{
		std::unique_ptr<OwnersCollection>* oc = GetOwnersCollection<T>(value);
		if (oc == nullptr) return nullptr;
		return &oc->get()->_OwnersMap;
	}

	template<typename T>
	std::vector<Entity>* SharedComponentStorage::GetOwnersList(std::shared_ptr<T> value)
	{
		std::unique_ptr<OwnersCollection>* oc = GetOwnersCollection<T>(value);
		if (oc == nullptr) return nullptr;
		return &oc->get()->_OwnersList;
	}

	template<typename T>
	void SharedComponentStorage::SetSharedComponent(Entity entity, std::shared_ptr<T> value)
	{
		RemoveSharedComponent<T>(entity);
		std::unique_ptr<SCCollection>* scc = GetSCCollection<T>();
		std::shared_ptr<SharedComponentBase> scp = std::dynamic_pointer_cast<SharedComponentBase>(value);
		if (scc == nullptr) {
			std::unique_ptr<SCCollection> nscc = std::make_unique<SCCollection>();
			std::unique_ptr<OwnersCollection> noc = std::make_unique<OwnersCollection>();
			noc.get()->_OwnersMap.insert({ entity, 0 });
			noc.get()->_OwnersList.push_back(entity);

			nscc.get()->_OwnersCollectionsMap.insert({ scp->GetHashCode(), 0 });
			nscc.get()->_OwnersCollectionsList.push_back(std::move(noc));
			nscc.get()->_SCList.push_back(std::move(scp));

			_SCCollectionsMap.insert({ typeid(T).hash_code(), _SCCollectionsList.size() });
			_SCCollectionsList.push_back(std::move(nscc));
		}
		else {
			auto key = scp->GetHashCode();
			auto search = scc->get()->_OwnersCollectionsMap.find(key);
			if (search == scc->get()->_OwnersCollectionsMap.end()) {
				std::unique_ptr<OwnersCollection> noc = std::make_unique<OwnersCollection>();
				noc.get()->_OwnersMap.insert({ entity, 0 });
				noc.get()->_OwnersList.push_back(entity);

				scc->get()->_OwnersCollectionsMap.insert({ scp->GetHashCode(), scc->get()->_OwnersCollectionsList.size() });
				scc->get()->_OwnersCollectionsList.push_back(std::move(noc));
				scc->get()->_SCList.push_back(std::move(scp));
			}
			else {
				Index index = search->second;
				std::unique_ptr<OwnersCollection>* oc = &scc->get()->_OwnersCollectionsList[index];
				auto entitySearch = oc->get()->_OwnersMap.find(entity);
				if (entitySearch == oc->get()->_OwnersMap.end()) {
					oc->get()->_OwnersMap.insert({ entity, oc->get()->_OwnersList.size() });
					oc->get()->_OwnersList.push_back(entity);
				}
			}
		}
	}

	template<typename T>
	bool SharedComponentStorage::RemoveSharedComponent(Entity entity)
	{
		std::unique_ptr<SCCollection>* scc = GetSCCollection<T>();
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
					const auto eraseHash = (scc->get()->_SCList[i]).get()->GetHashCode();
					const auto index = scc->get()->_OwnersCollectionsMap.at(eraseHash);
					scc->get()->_OwnersCollectionsMap.at((scc->get()->_SCList.back()).get()->GetHashCode()) = index;
					scc->get()->_OwnersCollectionsMap.erase(eraseHash);
					scc->get()->_SCList[index] = std::move(scc->get()->_SCList.back());
					scc->get()->_OwnersCollectionsList[index] = std::move(scc->get()->_OwnersCollectionsList.back());
					scc->get()->_SCList.pop_back();
					scc->get()->_OwnersCollectionsList.pop_back();
				}
				else {
					Index index = entitySearch->second;
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

	template<typename T>
	std::shared_ptr<T> SharedComponentStorage::GetSharedComponent(Entity entity)
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		const auto ocSize = scc->_OwnersCollectionsList.size();
		for (size_t i = 0; i < ocSize; i++) {
			std::unique_ptr<OwnersCollection>* oc = &scc->get()->_OwnersCollectionsList[i];
			auto entitySearch = oc->get()->_OwnersMap.find(entity);
			if (entitySearch != oc->get()->_OwnersMap.end()) {
				return std::dynamic_pointer_cast<T>(scc->_SCList[i]);
			}
		}
		return nullptr;
	}
#pragma endregion
}
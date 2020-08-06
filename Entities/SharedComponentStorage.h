#pragma once
#include "Entity.h"
namespace UniEngine {
	ENTITIES_API bool ComponentTypeComparator(ComponentType a, ComponentType b);
#pragma region SharedComponentStorage
	typedef std::size_t Index;

	typedef std::unordered_map<Entity, Index, Entity> OwnersMap;
	typedef std::vector<Entity> OwnersList;
	struct OwnersCollection {
		OwnersMap _OwnersMap;
		OwnersList _OwnersList;
		OwnersCollection() {
			_OwnersList = OwnersList();
			_OwnersMap = OwnersMap();
		}
	};

	struct SCCollection {
		std::unordered_map<std::size_t, Index> _OwnersCollectionsMap;
		std::vector<SharedComponentBase*> _SCList;
		std::vector<OwnersCollection*> _OwnersCollectionsList;
		SCCollection() {
			_OwnersCollectionsMap = std::unordered_map<std::size_t, Index>();
			_SCList = std::vector<SharedComponentBase*>();
			_OwnersCollectionsList = std::vector<OwnersCollection*>();
		}
	};

	class SharedComponentStorage
	{
		std::unordered_map<std::size_t, Index> _SCCollectionsMap;
		std::vector<SCCollection*> _SCCollectionsList;

	public:
		SharedComponentStorage();

		void DeleteEntity(Entity entity);

		template <typename T>
		SCCollection* GetSCCollection();

		template <typename T>
		std::unordered_map<std::size_t, Index>* GetOwnersCollectionsMap();

		template <typename T>
		std::vector<OwnersCollection*>* GetOwnersCollectionsList();

		template <typename T>
		std::vector<T*>* GetSCList();

		template <typename T>
		OwnersCollection* GetOwnersCollection(T* value);

		template <typename T>
		OwnersMap* GetOwnersMap(T* value);

		template <typename T>
		OwnersList* GetOwnersList(T* value);

		template <typename T>
		void SetSharedComponent(Entity entity, T* value);

		template <typename T>
		bool RemoveSharedComponent(Entity entity);

		template <typename T>
		T* GetSharedComponent(Entity entity);


	};

	template<typename T>
	inline SCCollection* SharedComponentStorage::GetSCCollection()
	{
		auto key = typeid(T).hash_code();
		auto search = _SCCollectionsMap.find(key);
		if (search != _SCCollectionsMap.end()) {
			Index index = search->second;
			return (SCCollection*)_SCCollectionsList[index];
		}
		return nullptr;
	}


	template<typename T>
	inline std::unordered_map<std::size_t, Index>* SharedComponentStorage::GetOwnersCollectionsMap()
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		return &scc->_OwnersCollectionsMap;
	}

	template<typename T>
	inline std::vector<OwnersCollection*>* SharedComponentStorage::GetOwnersCollectionsList()
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		return &scc->_OwnersCollectionsList;
	}

	template<typename T>
	inline std::vector<T*>* SharedComponentStorage::GetSCList()
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		return (std::vector<T*>*) (void*) & scc->_SCList;
	}

	template<typename T>
	inline OwnersCollection* SharedComponentStorage::GetOwnersCollection(T* value)
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		auto key = dynamic_cast<SharedComponentBase*>(value)->GetHashCode();
		auto search = scc->_OwnersCollectionsMap.find(key);
		if (search != scc->_OwnersCollectionsMap.end()) {
			Index index = search->second;
			return (OwnersCollection*)scc->_OwnersCollectionsList[index];
		}
		return nullptr;
	}

	template<typename T>
	inline OwnersMap* SharedComponentStorage::GetOwnersMap(T* value)
	{
		OwnersCollection* oc = GetOwnersCollection<T>(value);
		if (oc == nullptr) return nullptr;
		return &oc->_OwnersMap;
	}

	template<typename T>
	inline OwnersList* SharedComponentStorage::GetOwnersList(T* value)
	{
		OwnersCollection* oc = GetOwnersCollection<T>(value);
		if (oc == nullptr) return nullptr;
		return &oc->_OwnersList;
	}

	template<typename T>
	inline void SharedComponentStorage::SetSharedComponent(Entity entity, T* value)
	{
		SCCollection* scc = GetSCCollection<T>();
		SharedComponentBase* scp = dynamic_cast<SharedComponentBase*>(value);
		if (scc == nullptr) {
			scc = new SCCollection();
			OwnersCollection* oc = new OwnersCollection();
			oc->_OwnersMap.insert({ entity, 0 });
			oc->_OwnersList.push_back(entity);

			scc->_OwnersCollectionsMap.insert({ scp->GetHashCode(), 0 });
			scc->_OwnersCollectionsList.push_back(oc);
			scc->_SCList.push_back(scp);

			_SCCollectionsMap.insert({ typeid(T).hash_code(), _SCCollectionsList.size() });
			_SCCollectionsList.push_back(scc);
		}
		else {
			auto key = scp->GetHashCode();
			auto search = scc->_OwnersCollectionsMap.find(key);
			if (search == scc->_OwnersCollectionsMap.end()) {
				OwnersCollection* oc = new OwnersCollection();
				oc->_OwnersMap.insert({ entity, 0 });
				oc->_OwnersList.push_back(entity);

				scc->_OwnersCollectionsMap.insert({ scp->GetHashCode(), scc->_OwnersCollectionsList.size() });
				scc->_OwnersCollectionsList.push_back(oc);
				scc->_SCList.push_back(value);
			}
			else {
				Index index = search->second;
				OwnersCollection* oc = scc->_OwnersCollectionsList[index];
				auto entitySearch = oc->_OwnersMap.find(entity);
				if (entitySearch == oc->_OwnersMap.end()) {
					oc->_OwnersMap.insert({ entity, oc->_OwnersList.size() });
					oc->_OwnersList.push_back(entity);
				}
			}
		}
	}

	template<typename T>
	inline bool SharedComponentStorage::RemoveSharedComponent(Entity entity)
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return false;
		size_t ocSize = scc->_OwnersCollectionsList.size();
		for (size_t i = 0; i < ocSize; i++) {
			OwnersCollection* oc = scc->_OwnersCollectionsList[i];
			auto entitySearch = oc->_OwnersMap.find(entity);
			if (entitySearch != oc->_OwnersMap.end()) {
				if (entity != entitySearch->first) {
					Debug::Error("Entity already deleted!");
					return false;
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
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline T* SharedComponentStorage::GetSharedComponent(Entity entity)
	{
		SCCollection* scc = GetSCCollection<T>();
		if (scc == nullptr) return nullptr;
		size_t ocSize = scc->_OwnersCollectionsList.size();
		for (size_t i = 0; i < ocSize; i++) {
			OwnersCollection* oc = scc->_OwnersCollectionsList[i];
			auto entitySearch = oc->_OwnersMap.find(entity);
			if (entitySearch != oc->_OwnersMap.end()) {
				return dynamic_cast<T*>(scc->_SCList[i]);
			}
		}
		return nullptr;
	}
#pragma endregion
}
#pragma once
#include "Core.h"
namespace UniEngine {

	typedef std::size_t Index;
	
	typedef std::unordered_map<Entity*, Index> OsIMap;
	typedef std::vector<Entity*> OsList;
	typedef std::pair<OsIMap*, OsList*> OC;

	typedef std::pair<SharedComponentBase*, OC*> SCOC;
	typedef std::unordered_map<std::size_t, Index> SCOCsIMap;
	typedef std::vector<SCOC*> SCOCsList;

	typedef std::pair<SCOCsIMap*, SCOCsList*> SCOCC;
	typedef std::unordered_map<std::size_t, SCOCC*> SCOCsStorage;
	class UECORE_API SharedComponentStorage
	{
		friend class EntityCollection;
		SCOCsStorage _SCsStorage;
	public:
		SharedComponentStorage();

		void DeleteEntity(Entity* entity);

		bool RemoveSC(SCOCC* scocc, Entity* entity);

		template <typename T>
		SCOCC* GetSCOCC();
		
		template <typename T>
		SCOCsIMap* GetSCOCsIMap();

		template <typename T>
		SCOCsList* GetSCOCsList();

		template <typename T>
		SCOCsIMap* GetSCOCsIMap(SCOCC* scocc);

		template <typename T>
		SCOCsList* GetSCOCsList(SCOCC* scocc);

		template <typename T>
		SCOC* GetSCOC(T* value);

		template <typename T>
		SCOC* GetSCOC(T* value, SCOCC* scocc);

		template <typename T>
		OC* GetOC(T* value);

		template <typename T>
		OsIMap* GetOsIMap(T* value);

		template <typename T>
		OsList* GetOsList(T* value);

		template <typename T>
		bool SetSC(Entity* entity, T* value);

		template <typename T>
		T* GetSC(Entity* entity);

		

		template <typename T>
		bool RemoveSC(Entity* entity);

	};
	
	template<typename T>
	inline SCOCC* SharedComponentStorage::GetSCOCC()
	{
		auto key = typeid(T).hash_code();
		auto search = _SCsStorage.find(key);
		if (search != _SCsStorage.end()) {
			return search->second;
		}
		return nullptr;
	}

	template<typename T>
	inline SCOCsIMap* SharedComponentStorage::GetSCOCsIMap()
	{
		SCOCC* scocc = GetSCOCC<T>();
		if (scocc == nullptr) return nullptr;
		return scocc->first;
	}

	template<typename T>
	inline SCOCsList* SharedComponentStorage::GetSCOCsList()
	{
		SCOCC* scocc = GetSCOCC<T>();
		if (scocc == nullptr) return nullptr;
		return scocc->second;
	}

	template<typename T>
	inline SCOCsIMap* SharedComponentStorage::GetSCOCsIMap(SCOCC* scocc)
	{
		return scocc->first;
	}

	template<typename T>
	inline SCOCsList* SharedComponentStorage::GetSCOCsList(SCOCC* scocc)
	{
		return scocc->second;
	}

	template<typename T>
	inline SCOC* SharedComponentStorage::GetSCOC(T* value)
	{
		SCOCC* scocc = GetSCOCC<T>();
		if (scocc == nullptr) return nullptr;
		SCOCsIMap* map = scocc->first;
		SCOCsList* list = scocc->second;
		auto key = dynamic_cast<SharedComponentBase*>(value)->GetHashCode();
		auto search = map->find(key);
		if (search != map->end()) {
			return list->at(search->second);
		}
		return nullptr;
	}

	template<typename T>
	inline SCOC* SharedComponentStorage::GetSCOC(T* value, SCOCC* scocc)
	{
		SCOCsIMap* map = scocc->first;
		SCOCsList* list = scocc->second;
		auto key = dynamic_cast<SharedComponentBase*>(value)->GetHashCode();
		auto search = map->find(key);
		if (search != map->end()) {
			return list->at(search->second);
		}
		return nullptr;
	}

	template<typename T>
	inline OC* SharedComponentStorage::GetOC(T* value)
	{
		SCOC* scoc = GetSCOC<T>(value);
		if (scoc == nullptr) return nullptr;
		return scoc->second;
	}

	template<typename T>
	inline OsIMap* SharedComponentStorage::GetOsIMap(T* value)
	{
		OC* oc = GetOC<T>(value);
		if (oc == nullptr) return nullptr;
		return oc->first;
	}

	template<typename T>
	inline OsList* SharedComponentStorage::GetOsList(T* value)
	{
		OC* oc = GetOC<T>(value);
		if (oc == nullptr) return nullptr;
		return oc->second;
	}

	template<typename T>
	inline bool SharedComponentStorage::SetSC(Entity* entity, T* value)
	{
		//Firstly we make sure this entity doesn't contain same type of sc.
		RemoveSC<T>(entity);

		SCOCC* scocc = GetSCOCC<T>();
		if (scocc == nullptr) {
			//If we cant find the type of class
			OsIMap* map = new OsIMap();
			map->insert({entity, 0});
			OsList* list = new OsList();
			list->push_back(entity);
			OC* oc = new OC(map, list);
			SCOC* scoc = new SCOC(dynamic_cast<SharedComponentBase*>(value), oc);
			SCOCsIMap* scmap = new SCOCsIMap();
			scmap->insert({ dynamic_cast<SharedComponentBase*>(value)->GetHashCode(), 0 });
			SCOCsList* sclist = new SCOCsList();
			sclist->push_back(scoc);
			_SCsStorage.insert({ typeid(T).hash_code(), new SCOCC(scmap, sclist)});
		}
		else {
			SCOC* scoc = GetSCOC<T>(value, scocc);
			if (scoc == nullptr) {
				//If we can't find the sc
				OsIMap* map = new OsIMap();
				map->insert({ entity, 0 });
				OsList* list = new OsList();
				list->push_back(entity);
				OC* oc = new OC(map, list);
				SCOC* scoc = new SCOC(dynamic_cast<SharedComponentBase*>(value), oc);
				scocc->first->insert({ dynamic_cast<SharedComponentBase*>(value)->GetHashCode(), scocc->second->size() });
				scocc->second->push_back(scoc);
			}
			else {
				auto map = scoc->second->first;
				auto list = scoc->second->second;
				auto search = map->find(entity);
				if (search == map->end()) {
					//if we can't find the entity
					map->insert({ entity, list->size() });
					list->push_back(entity);
				}
			}
		}
		return true;
	}

	template<typename T>
	inline T* SharedComponentStorage::GetSC(Entity* entity)
	{
		SCOCC* scocc = GetSCOCC<T>();
		SCOCsList* list = scocc->second;
		for (SCOC* i : *list) {
			OsIMap* map = i->second->first;
			auto search = map->find(entity);
			if (search != map->end()) {
				return dynamic_cast<T*>(i->first);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline bool SharedComponentStorage::RemoveSC(Entity* entity)
	{
		SCOCC* scocc = GetSCOCC<T>();
		if (scocc != nullptr) {
			return RemoveSC(scocc, entity);
		}
		else {
			return false;
		}
	}

}
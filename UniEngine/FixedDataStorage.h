#pragma once
#include "Math.h"
#include "FixedData.h"
namespace UniEngine {
	class FixedDataStorage
	{
		std::unordered_map<size_t, void*> _FixedDataStorage;
		std::vector<Translation> _Translations;
		std::vector<Rotation> _Rotations;
		std::vector<Scale> _Scales;
		std::vector<LocalPosition> _LocalPositions;
		std::vector<LocalRotation> _LocalRotations;
		std::vector<LocalScale> _LocalScales;
		std::vector<LocalToWorld> _LocalToWorlds;
		std::vector<LocalToParent> _LocalToParents;

		friend class EntityManager;
		FixedDataStorage();
		void PushBack();
		void RemoveSwapBack(uint key);
		template <typename T>
		void SetFixedData(uint key, T value);
		template <typename T>
		T GetFixedData(uint key);
	};
	
	template<typename T>
	inline void FixedDataStorage::SetFixedData(uint key, T value)
	{
		auto code = typeid(T).hash_code();
		auto search = _FixedDataStorage.find(code);
		if (search != _FixedDataStorage.end()) {
			std::vector<T>* list = (std::vector<T>*) search->second;
			list->at(key) = value;
		}
		return;
	}

	template<typename T>
	inline T FixedDataStorage::GetFixedData(uint key)
	{
		auto code = typeid(T).hash_code();
		auto search = _FixedDataStorage.find(code);
		if (search != _FixedDataStorage.end()) {
			std::vector<T>* list = (std::vector<T>*) search->second;
			return list->at(key);
		}
		return T();
	}

}

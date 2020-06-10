#pragma once
#include "Core.h"
namespace UniEngine {
	class FixedDataStorage
	{
		std::unordered_map<size_t, void*> _FixedDataStorage;
		std::vector<Position> _Translations;
		std::vector<Rotation> _Rotations;
		std::vector<Scale> _Scales;
		std::vector<LocalPosition> _LocalPositions;
		std::vector<LocalRotation> _LocalRotations;
		std::vector<LocalScale> _LocalScales;
		std::vector<LocalToWorld> _LocalToWorlds;
		std::vector<LocalToParent> _LocalToParents;
		std::vector<CameraMask> _CameraMasks;

		friend class EntityCollection;
		FixedDataStorage();
		void PushBack();
		void DeleteEntity(unsigned key);
		template <typename T>
		void SetFixedData(unsigned key, T value);
		template <typename T>
		T GetFixedData(unsigned key);
	};
	
	template<typename T>
	inline void FixedDataStorage::SetFixedData(unsigned key, T value)
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
	inline T FixedDataStorage::GetFixedData(unsigned key)
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

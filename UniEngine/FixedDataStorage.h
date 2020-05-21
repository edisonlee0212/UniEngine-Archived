#pragma once
#include "Math.h"
#include "FixedData.h"
namespace UniEngine {
	class FixedDataStorage
	{
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
		switch (typeid(T).hash_code())
		{
		case typeid(Translation).hash_code():
			_Translations[key] = dynamic_cast<T>(value);
			break;
		case typeid(Rotation).hash_code():
			_Rotations[key] = dynamic_cast<T>(value);
			break;
		case typeid(Scale).hash_code():
			_Scales[key] = dynamic_cast<T>(value);
			break;
		case typeid(LocalPosition).hash_code():
			_LocalPositions[key] = dynamic_cast<T>(value);
			break;
		case typeid(LocalRotation).hash_code():
			_LocalRotations[key] = dynamic_cast<T>(value);
			break;
		case typeid(LocalScale).hash_code():
			_LocalScales[key] = dynamic_cast<T>(value);
			break;
		case typeid(LocalToWorld).hash_code():
			_LocalToWorlds[key] = dynamic_cast<T>(value);
			break;
		case typeid(LocalToParent).hash_code():
			_LocalToParents[key] = dynamic_cast<T>(value);
			break;
		}
	}

	template<typename T>
	inline T FixedDataStorage::GetFixedData(uint key)
	{
		switch (typeid(T).hash_code())
		{
		case typeid(Translation).hash_code():
			return _Translations[key];
			break;
		case typeid(Rotation).hash_code():
			return _Rotations[key];
			break;
		case typeid(Scale).hash_code():
			return _Scales[key];
			break;
		case typeid(LocalPosition).hash_code():
			return _LocalPositions[key];
			break;
		case typeid(LocalRotation).hash_code():
			return _LocalRotations[key];
			break;
		case typeid(LocalScale).hash_code():
			return _LocalScales[key];
			break;
		case typeid(LocalToWorld).hash_code():
			return _LocalToWorlds[key];
			break;
		case typeid(LocalToParent).hash_code():
			return _LocalToParents[key];
			break;
		}
	}

}

#include "pch.h"
#include "FixedDataStorage.h"
using namespace UniEngine;
UniEngine::FixedDataStorage::FixedDataStorage()
{
	_Translations = std::vector<Position>();
	_Rotations = std::vector<Rotation>() ;
	_Scales = std::vector<Scale>();
	_LocalPositions = std::vector<LocalPosition>();
	_LocalRotations = std::vector<LocalRotation>();
	_LocalScales = std::vector<LocalScale>();
	_LocalToWorlds = std::vector<LocalToWorld>();
	_LocalToParents = std::vector<LocalToParent>();
	_CameraMasks = std::vector<CameraMask>();
	_FixedDataStorage.insert({ typeid(Position).hash_code(), (void*)&_Translations });
	_FixedDataStorage.insert({ typeid(Rotation).hash_code(), (void*)&_Rotations });
	_FixedDataStorage.insert({ typeid(Scale).hash_code(), (void*)&_Scales });
	_FixedDataStorage.insert({ typeid(LocalPosition).hash_code(), (void*)&_LocalPositions });
	_FixedDataStorage.insert({ typeid(LocalRotation).hash_code(), (void*)&_LocalRotations });
	_FixedDataStorage.insert({ typeid(LocalScale).hash_code(), (void*)&_LocalScales });
	_FixedDataStorage.insert({ typeid(LocalToWorld).hash_code(), (void*)&_LocalToWorlds });
	_FixedDataStorage.insert({ typeid(LocalToParent).hash_code(), (void*)&_LocalToParents });
	_FixedDataStorage.insert({ typeid(CameraMask).hash_code(), (void*)&_CameraMasks });
}
void UniEngine::FixedDataStorage::PushBack()
{
	_Translations.push_back(Position());
	_Rotations.push_back(Rotation());
	_Scales.push_back(Scale());
	_LocalPositions.push_back(LocalPosition());
	_LocalRotations.push_back(LocalRotation());
	_LocalScales.push_back(LocalScale());
	_LocalToWorlds.push_back(LocalToWorld());
	_LocalToParents.push_back(LocalToParent());
	_CameraMasks.push_back(CameraMask());
}

void UniEngine::FixedDataStorage::DeleteEntity(unsigned key)
{
	_Translations[key] = _Translations.back();
	_Translations.pop_back();

	_Rotations[key] = _Rotations.back();
	_Rotations.pop_back();

	_Scales[key] = _Scales.back();
	_Scales.pop_back();

	_LocalPositions[key] = _LocalPositions.back();
	_LocalPositions.pop_back();

	_LocalRotations[key] = _LocalRotations.back();
	_LocalRotations.pop_back();

	_LocalScales[key] = _LocalScales.back();
	_LocalScales.pop_back();

	_LocalToWorlds[key] = _LocalToWorlds.back();
	_LocalToWorlds.pop_back();

	_LocalToParents[key] = _LocalToParents.back();
	_LocalToParents.pop_back();

	_CameraMasks[key] = _CameraMasks.back();
	_CameraMasks.pop_back();
}

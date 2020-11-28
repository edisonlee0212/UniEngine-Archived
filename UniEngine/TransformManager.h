#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Transforms.h"
namespace UniEngine {
	struct ChildInfo {
		Entity Child;
		LocalToParent LastLTP;
		LocalToWorld LastPLTW;
	};
	class UNIENGINE_API TransformManager :
		public ManagerBase
	{
		static bool _AddCheck;
		static size_t _CurrentStoredHierarchyVersion;
		static EntityQuery _TransformQuery;
		static std::vector<std::pair<Entity, ChildInfo>> _CachedParentHierarchies;
		static void CalculateLtwRecursive(LocalToWorld pltw, Entity entity);
		static void CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity);
	public:
		static void Init();
		static void LateUpdate();
	};

}
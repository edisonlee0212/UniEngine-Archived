#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	struct ChildInfo {
		Entity Child;
		LocalToParent LastLTP;
		LocalToWorld LastPLTW;
	};
	class UNIENGINE_API ParentSystem :
		public SystemBase
	{
		size_t _CurrentStoredHierarchyVersion = INT_MAX;
		std::vector<std::pair<Entity, ChildInfo>> _CachedParentHierarchies;
		void CalculateLTWRecursive(LocalToWorld pltw, Entity entity);
		void CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity);
	public:
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API ParentSystem :
		public SystemBase
	{
		size_t _CurrentStoredHierarchyVersion = INT_MAX;
		std::vector<std::vector<std::pair<Entity, Entity>>> _CachedParentHierarchies;
		void CalculateLTWRecursive(LocalToWorld pltw, Entity entity);
		void CollectHierarchy(std::vector<std::pair<Entity, Entity>>* container, Entity entity);
	public:
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

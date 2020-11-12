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
		public SystemBase
	{
		bool _AddCheck;
		EntityQuery _ERR;
		EntityQuery _LERR;
		
		EntityQuery _P;
		EntityQuery _PR;
		EntityQuery _PS;
		EntityQuery _PRS;
		EntityQuery _R;
		EntityQuery _RS;
		EntityQuery _S;

		EntityQuery _LP;
		EntityQuery _LPR;
		EntityQuery _LPS;
		EntityQuery _LPRS;
		EntityQuery _LR;
		EntityQuery _LRS;
		EntityQuery _LS;

		size_t _CurrentStoredHierarchyVersion = INT_MAX;
		std::vector<std::pair<Entity, ChildInfo>> _CachedParentHierarchies;
		void CalculateLtwRecursive(LocalToWorld pltw, Entity entity);
		void CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity);
	public:
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
	};

}
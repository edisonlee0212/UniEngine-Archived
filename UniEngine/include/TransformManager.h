#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Transforms.h"
namespace UniEngine {
	class UNIENGINE_API TransformManager :
		public Singleton<TransformManager>
	{
		static EntityQuery _TransformQuery;
		static void CalculateLtwRecursive(GlobalTransform* pltw, Entity entity);
	public:
		static void Init();
		static void LateUpdate();
	};
}
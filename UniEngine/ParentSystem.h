#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API ParentSystem :
		public SystemBase
	{
		void CalculateLTW(LocalToWorld pltw, Entity entity);
	public:
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

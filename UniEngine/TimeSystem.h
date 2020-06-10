#pragma once
#include "Core.h"
namespace UniEngine {
	class TimeSystem : public SystemBase
	{
		float _TimeStep;
	public:
		TimeSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}


#pragma once
#include "Core.h"
namespace UniEngine {
	class TimeSystem : public SystemBase
	{
	public:
		TimeSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}


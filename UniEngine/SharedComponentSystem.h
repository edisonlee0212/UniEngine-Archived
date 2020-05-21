#pragma once
#include "Core.h"
namespace UniEngine {
	class SharedComponentSystem :
		public SystemBase
	{
	public:
		SharedComponentSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};

}
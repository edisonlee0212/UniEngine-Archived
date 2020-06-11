#pragma once
#include "Core.h"
namespace UniEngine {
	class UECORE_API  SharedComponentSystem :
		public SystemBase
	{
	public:
		SharedComponentSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
		void FixedUpdate();
	};

}
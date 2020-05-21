#pragma once
#include "SystemBase.h"
namespace UniEngine {
	class InputSystem :
		public SystemBase
	{
	public:
		InputSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

#pragma once
#include "Core.h"
namespace UniEngine {
	class InputSystem :
		public SystemBase
	{
		
		float _LastX = 0, _LastY = 0, _LastScrollY = 0;
		bool startMouse = false;
		bool startScroll = false;
	public:
		InputSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

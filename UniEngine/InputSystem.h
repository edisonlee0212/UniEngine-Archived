#pragma once
#include "SystemBase.h"
namespace UniEngine {
	class InputSystem :
		public SystemBase
	{
		unsigned _CameraMatricesBufferID;
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

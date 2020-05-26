#pragma once
#include "Core.h"
namespace UniEngine {
	class TransformSystem :
		public SystemBase
	{
	public:
		TransformSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

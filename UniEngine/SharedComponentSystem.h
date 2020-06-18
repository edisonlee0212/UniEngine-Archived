#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API SharedComponentSystem :
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
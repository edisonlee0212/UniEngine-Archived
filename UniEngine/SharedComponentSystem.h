#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API SharedComponentSystem :
		public SystemBase
	{
	public:
		SharedComponentSystem();
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
		void FixedUpdate() override;
	};

}
#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API TransformSystem :
		public SystemBase
	{
		EntityQuery _P;
		EntityQuery _PR;
		EntityQuery _PS;
		EntityQuery _PRS;
		EntityQuery _R;
		EntityQuery _RS;
		EntityQuery _S;

		EntityQuery _LP;
		EntityQuery _LPR;
		EntityQuery _LPS;
		EntityQuery _LPRS;
		EntityQuery _LR;
		EntityQuery _LRS;
		EntityQuery _LS;
	public:
		TransformSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};

}
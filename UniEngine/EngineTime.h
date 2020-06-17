#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UECORE_API EngineTime
	{
	private:
		double _WorldTime;
		double _FixedDeltaTime;
		double _DeltaTime;
		double _LastFrameTime;
		float _TimeStep;
		friend class TimeSystem;
		friend class World;
		void AddWorldTime(double value);
		void AddFixedDeltaTime(double value);
	public:
		float TimeStep();
		double WorldTime();
		float FixedDeltaTime();
		float DeltaTime();
		float LastFrameTime();
	};

}
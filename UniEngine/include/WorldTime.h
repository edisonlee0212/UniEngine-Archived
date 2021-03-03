#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API WorldTime {
	private:
		friend class World;
		friend class Application;
		double m_frameStartTime;
		double m_fixedDeltaTime;
		double m_deltaTime;
		double m_lastFrameTime;
		float m_timeStep;
		void AddFixedDeltaTime(double value);
	public:
		float TimeStep();
		float FixedDeltaTime();
		float DeltaTime();
		float LastFrameTime();
	};
}
#pragma once
#include "EntitiesAPI.h"
namespace UniEngine {
	namespace Entities {
		class ENTITIES_API WorldTime {
		private:
			friend class World;
			double _WorldTime;
			double _FixedDeltaTime;
			double _DeltaTime;
			double _LastFrameTime;
			float _TimeStep;


			void AddWorldTime(double value);
			void AddFixedDeltaTime(double value);
		public:
			float TimeStep();
			double Time();
			float FixedDeltaTime();
			float DeltaTime();
			float LastFrameTime();
		};
	}
}
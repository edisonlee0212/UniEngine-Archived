#pragma once
#include "Core.h"
namespace UniEngine {
	class TransformSystem :
		public SystemBase
	{
		void CalculateTransform(Entity* parent);

	public:
		TransformSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

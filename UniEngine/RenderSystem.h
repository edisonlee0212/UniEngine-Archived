#pragma once
#include "Core.h"
namespace UniEngine {
	class RenderSystem : public SystemBase
	{
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

#pragma once
#include "Core.h"
namespace UniEngine {
	class RenderSystem : public SystemBase
	{
		void DrawEntity(Entity* entity);
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

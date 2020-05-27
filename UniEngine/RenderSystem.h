#pragma once
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class RenderSystem : public SystemBase
	{
		void DrawEntity(Entity* entity, Camera* camera);
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

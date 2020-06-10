#pragma once
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {

	class RenderSystem : public SystemBase
	{
		void RenderToCamera(CameraComponent* camera, Entity* cameraEntity);
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

#pragma once
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class UECORE_API  RenderSystem : public SystemBase
	{
		void RenderToCamera(CameraComponent* camera, Entity* cameraEntity);
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

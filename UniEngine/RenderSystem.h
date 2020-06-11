#pragma once
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class UECORE_API  RenderSystem : public SystemBase
	{
		static bool _EnableWireFrame;
		void RenderToCamera(CameraComponent* camera, Entity* cameraEntity);
	public:
		static void SetWireFrameMode(bool value);
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

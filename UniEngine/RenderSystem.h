#pragma once
#include "UniEngineAPI.h"
#include "RenderManager.h"
namespace UniEngine {
	class UNIENGINE_API RenderSystem : public SystemBase
	{
		static bool _EnableWireFrame;
		void RenderToMainCamera(CameraComponent* camera, Entity cameraEntity);
	public:
		static void SetWireFrameMode(bool value);
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};

}

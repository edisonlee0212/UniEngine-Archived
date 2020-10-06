#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderManager.h"
#include "SystemBase.h"

namespace UniEngine {
	class UNIENGINE_API RenderSystem : public SystemBase
	{
		static bool _EnableWireFrame;
		void RenderToMainCamera(CameraComponent* camera, Entity cameraEntity);
	public:
		static void SetWireFrameMode(bool value);
		RenderSystem();
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
	};

}

#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderManager.h"
#include "SystemBase.h"

//#define DEFERRED_RENDERING
namespace UniEngine {
	class UNIENGINE_API RenderSystem : public SystemBase
	{
		friend class RenderManager;

		
		
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

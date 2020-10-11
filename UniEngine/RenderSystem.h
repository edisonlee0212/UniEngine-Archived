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
#ifdef DEFERRED_RENDERING
		std::shared_ptr<GLProgram> _GBufferLightingPass;
		std::shared_ptr<RenderTarget> _GBuffer;
		std::shared_ptr<GLRenderBuffer> _GDepthBuffer;
		std::shared_ptr<Texture2D> _GPositionBuffer;
		std::shared_ptr<Texture2D> _GNormalBuffer;
		std::shared_ptr<Texture2D> _GColorSpecularBuffer;
		
#endif
		
		
		static bool _EnableWireFrame;
		void RenderToMainCamera(CameraComponent* camera, Entity cameraEntity);
	public:
		static void SetWireFrameMode(bool value);
		RenderSystem();
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
#ifdef DEFERRED_RENDERING
		void ResizeGBuffer(int x, int y);
#endif
	};

}

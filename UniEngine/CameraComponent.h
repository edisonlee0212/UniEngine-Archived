#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Camera.h"
#include "Cubemap.h"

namespace UniEngine {
	class UNIENGINE_API CameraComponent :
		public PrivateComponentBase
	{
		friend class RenderManager;
		std::unique_ptr<Camera> _Camera;
		
		std::unique_ptr<RenderTarget> _SSAO;
		std::unique_ptr<RenderTarget> _SSAOBlurFilter;
		std::unique_ptr<GLTexture2D> _SSAONoise;
		std::unique_ptr<GLTexture2D> _SSAOColor;
		std::unique_ptr<GLTexture2D> _SSAOBlur;

		std::unique_ptr<RenderTarget> _GBuffer;
		std::unique_ptr<GLRenderBuffer> _GDepthBuffer;
		std::unique_ptr<GLTexture2D> _GPositionBuffer;
		std::unique_ptr<GLTexture2D> _GNormalBuffer;
		std::unique_ptr<GLTexture2D> _GColorSpecularBuffer;
		int _ResolutionX;
		int _ResolutionY;
	public:
		void ResizeResolution(int x, int y);
		CameraComponent();
		bool DrawSkyBox = true;
		glm::vec3 ClearColor;
		std::shared_ptr<Cubemap> SkyBox;
		void OnGui() override;
		std::unique_ptr<Camera>& GetCamera();
	};

}

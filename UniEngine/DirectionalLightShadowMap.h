#pragma once
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine {
	class UNIENGINE_API DirectionalLightShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthMapArray;
		GLTexture* _DepthMapDepthArray;
		bool _EnableEVSM;
		bool _EnableVSM;
		size_t _LightAmount;
	public:
		DirectionalLightShadowMap(size_t amount, float resolutionX = 1024.0f, float resolutionY = 1024.0f, bool enableVSM = false, bool enableEVSM = false);
		void SetVSM(bool enabled);
		void SetEVSM(bool enabled);
		void SetLightAmount(size_t value);
		GLTexture* DepthMapArray();
		void Bind();
	};
}

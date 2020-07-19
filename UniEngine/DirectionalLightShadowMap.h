#pragma once
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine {
	class UNIENGINE_API DirectionalLightShadowMap :
		public RenderTarget
	{
		GLTexture2DArray* _DepthMapArray;
		GLTexture2DArray* _DepthMapDepthArray;
		bool _EnableVSM;
		size_t _LightAmount;
		void Allocate();
	public:
		DirectionalLightShadowMap(size_t amount, float resolutionX = 1024.0f, float resolutionY = 1024.0f, bool enableVSM = false);
		void SetVSM(bool enabled);
		void SetLightAmount(size_t value);
		GLTexture2DArray* DepthMapArray();
		void Bind();
	};
}

#pragma once
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine {
	class UNIENGINE_API DirectionalLightShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthMapArray;
		GLTexture* _DepthMapDepthArray;
	public:
		DirectionalLightShadowMap(size_t amount, float resolutionX = 1024.0f, float resolutionY = 1024.0f);
		GLTexture* DepthMapArray();
		void Bind();
	};
}

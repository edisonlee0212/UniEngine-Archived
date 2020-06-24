#pragma once
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine {
	class UNIENGINE_API DirectionalLightShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthMapArray;
		
	public:
		DirectionalLightShadowMap(size_t amount, float resolutionX = 4096.0f, float resolutionY = 4096.0f);
		GLTexture* DepthCubeMapArray();
		void Bind(GLint layer);
	};
}

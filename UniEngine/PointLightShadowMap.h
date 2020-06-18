#pragma once
#include "RenderTarget.h"
#include "UniEngineAPI.h"

namespace UniEngine {

	class UNIENGINE_API PointLightShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthCubeMapArray;
	public:
		PointLightShadowMap(size_t amount, float resolutionX = 2048.0f, float resolutionY = 2048.0f);
		GLTexture* DepthCubeMapArray();
		void Bind(GLint layer);
	};

}
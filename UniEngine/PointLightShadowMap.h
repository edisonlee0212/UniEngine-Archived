#pragma once
#include "RenderTarget.h"
#include "UniEngineAPI.h"

namespace UniEngine {

	class UNIENGINE_API PointLightShadowMap :
		public RenderTarget
	{
		GLTextureCubeMapArray* _DepthCubeMapArray;
	public:
		PointLightShadowMap(size_t amount, float resolutionX = 2048.0f, float resolutionY = 2048.0f);
		GLTextureCubeMapArray* DepthCubeMapArray();
		void Bind();
	};

}
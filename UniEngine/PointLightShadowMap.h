#pragma once
#include "RenderTarget.h"
#include "UniEngineAPI.h"

namespace UniEngine {

	class UNIENGINE_API PointLightShadowMap :
		public RenderTarget
	{
		GLTextureCubeMapArray* _DepthCubeMapArray;
	public:
		PointLightShadowMap(size_t amount, size_t resolutionX = 2048, size_t resolutionY = 2048);
		GLTextureCubeMapArray* DepthCubeMapArray();
		void Bind();
	};

}
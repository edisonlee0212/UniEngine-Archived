#pragma once
#include "RenderTarget.h"
#include "Core.h"

namespace UniEngine {

	class PointLightShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthCubeMapArray;
	public:
		PointLightShadowMap(size_t amount, float resolutionX = 2048.0f, float resolutionY = 2048.0f);
		GLTexture* DepthCubeMapArray();
		void Bind(GLint layer);
	};

}
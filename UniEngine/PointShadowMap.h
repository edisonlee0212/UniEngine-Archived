#pragma once
#include "RenderTarget.h"
#include "Core.h"

namespace UniEngine {

	class PointShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthCubeMap;
	public:
		PointShadowMap(float resolutionX = 2048.0f, float resolutionY = 2048.0f);
		GLTexture* DepthCubeMap();
	};

}
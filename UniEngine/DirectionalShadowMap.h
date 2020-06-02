#pragma once
#include "RenderTarget.h"
namespace UniEngine {
	class DirectionalShadowMap :
		public RenderTarget
	{
		GLTexture* _DepthMap;
		
	public:
		DirectionalShadowMap(float resolutionX = 2048.0f, float resolutionY = 2048.0f);
		GLTexture* DepthMap();
	};
}

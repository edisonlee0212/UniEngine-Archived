#pragma once
#include "Core.h"
#include "RenderTarget.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API SpotLightShadowMap : public RenderTarget
	{
		std::unique_ptr<GLTexture2D> m_depthMap;
		void Allocate();
	public:
		SpotLightShadowMap(size_t resolution);
		void SetResolution(size_t resolution);
		std::unique_ptr<GLTexture2D>& DepthMap();
		void Bind();
	};
}


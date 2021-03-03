#pragma once
#include "Core.h"
#include "RenderTarget.h"
#include "UniEngineAPI.h"

namespace UniEngine {

	class UNIENGINE_API PointLightShadowMap :
		public RenderTarget
	{
		std::unique_ptr<GLTexture2DArray> m_depthMapArray;
		void Allocate();
	public:
		PointLightShadowMap(size_t resolution);
		void SetResolution(size_t resolution);
		std::unique_ptr<GLTexture2DArray>& DepthMapArray();
		void Bind();
	};

}
#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine {
	class UNIENGINE_API DirectionalLightShadowMap :
		public RenderTarget
	{
		std::unique_ptr<GLTexture2DArray> _DepthMapDepthArray;
		void Allocate();
	public:
		DirectionalLightShadowMap(size_t resolution);
		void SetResolution(size_t resolution);
		std::unique_ptr<GLTexture2DArray>& DepthMapDepthArray();
		void Bind();
	};
}

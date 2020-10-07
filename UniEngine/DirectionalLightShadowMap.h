#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine {
	class UNIENGINE_API DirectionalLightShadowMap :
		public RenderTarget
	{
		GLTexture2DArray* _DepthMapArray;
		GLTexture2DArray* _DepthMapDepthArray;
		void Allocate();
	public:
		DirectionalLightShadowMap(size_t resolution);
		void SetResolution(size_t resolution);
		GLTexture2DArray* DepthMapArray() const;
		GLTexture2DArray* DepthMapDepthArray() const;
		void Bind();
	};
}

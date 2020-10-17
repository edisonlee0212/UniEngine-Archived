#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API Cubemap
	{
		std::unique_ptr<GLTextureCubeMap> _Texture;
		std::vector<std::string> _Paths;
	public:
		std::unique_ptr<GLTextureCubeMap>& Texture() { return _Texture; }
		void LoadCubeMap(std::vector<std::string> paths);
		std::vector<std::string> Paths();
	};
}


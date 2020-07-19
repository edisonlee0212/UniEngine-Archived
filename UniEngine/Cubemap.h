#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API Cubemap
	{
		GLTextureCubeMap* _Texture;
		std::vector<std::string> _Paths;
	public:
		Cubemap();
		~Cubemap();
		void LoadCubeMap(std::vector<std::string> paths);
		std::vector<std::string> Paths();
	};
}


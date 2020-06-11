#pragma once
#include "Core.h"
namespace UniEngine {
	class UECORE_API Cubemap
	{
		GLTexture* _Texture;
		std::vector<std::string> _Paths;
	public:
		Cubemap();
		void LoadCubeMap(std::vector<std::string> paths);
		std::vector<std::string> Paths();
	};
}


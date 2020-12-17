#pragma once
#include "Core.h"
#include "EditorManager.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API Cubemap : public ResourceBehaviour
	{
		friend class ResourceManager;
		std::unique_ptr<GLTextureCubeMap> _Texture;
		std::vector<std::string> _Paths;
	public:
		Cubemap();
		std::unique_ptr<GLTextureCubeMap>& Texture() { return _Texture; }
		std::vector<std::string> Paths() const;
	};
}


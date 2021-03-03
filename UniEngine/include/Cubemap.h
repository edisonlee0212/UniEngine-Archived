#pragma once
#include "Core.h"
#include "EditorManager.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API Cubemap : public ResourceBehaviour
	{
		friend class ResourceManager;
		std::unique_ptr<GLTextureCubeMap> m_texture;
		std::vector<std::string> m_paths;
	public:
		Cubemap();
		std::unique_ptr<GLTextureCubeMap>& Texture() { return m_texture; }
		std::vector<std::string> Paths() const;
	};
}


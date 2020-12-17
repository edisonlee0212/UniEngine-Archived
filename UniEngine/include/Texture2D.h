#pragma once
#include "Core.h"
#include "EditorManager.h"
#include "UniEngineAPI.h"
namespace UniEngine {
    enum class UNIENGINE_API TextureType {
        NONE = 0,
        DIFFUSE = 1,
        SPECULAR = 2,
        AMBIENT = 3,
        EMISSIVE = 4,
        HEIGHT = 5,
        NORMAL = 6,
        SHININESS = 7,
        OPACITY = 8,
        DISPLACEMENT = 9,
        LIGHTMAP = 10,
        REFLECTION = 11,

        BASE_COLOR = 12,
        NORMAL_CAMERA = 13,
        EMISSION_COLOR = 14,
        METALNESS = 15,
        DIFFUSE_ROUGHNESS = 16,
        AMBIENT_OCCLUSION = 17,

        UNKNOWN = 18
    };
	class UNIENGINE_API Texture2D : public ResourceBehaviour
	{
        std::shared_ptr<GLTexture2D> _Texture;
        std::string _Path;

        friend class ResourceManager;
    public:
        Texture2D();
        std::shared_ptr<GLTexture2D> Texture() const;
        std::string Path() const;
	};
}

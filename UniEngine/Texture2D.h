#pragma once
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
	class UNIENGINE_API Texture2D
	{
        TextureType _Type;
        GLTexture2D* _Texture;
        std::string _Path;
    public:
        Texture2D(TextureType type);
        ~Texture2D();
        GLTexture2D* Texture();
        TextureType Type();
        void LoadTexture(std::string path, const std::string& directory);
        std::string Path();
	};
}

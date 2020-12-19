#pragma once
#include "Core.h"
#include "EditorManager.h"
#include "UniEngineAPI.h"
namespace UniEngine {
    enum class UNIENGINE_API TextureType {
        ALBEDO,
        NORMAL,
        METALLIC,
        ROUGHNESS,
        AO,
    	AMBIENT,
    	DIFFUSE,
    	SPECULAR,
    	EMISSIVE,
    	DISPLACEMENT
    };
	class UNIENGINE_API Texture2D : public ResourceBehaviour
	{
        friend class Material;
        friend class RenderManager;
        TextureType _Type;
        std::shared_ptr<GLTexture2D> _Texture;
        std::string _Path;
        friend class ResourceManager;
        friend class CameraComponent;
    public:
        Texture2D(TextureType type = TextureType::DIFFUSE);
        void SetType(TextureType type);
        TextureType GetType() const;
        glm::vec2 GetResolution() const;
        void StoreToPng(const std::string& path, int resizeX = -1, int resizeY = -1) const;
        void StoreToJpg(const std::string& path, int resizeX = -1, int resizeY = -1) const;
        std::shared_ptr<GLTexture2D> Texture() const;
        std::string Path() const;
	};
}

#pragma once
#include "Misc.h"
#include "Core.h"
#include "Scene.h"
#include "SceneNode.h"
namespace UniEngine {
    class AssimpImporter {
    public:
        static void LoadScene(Scene* destination, std::string const& path);
    private:
        static void ProcessNode(std::string directory, aiNode* node, SceneNode* sceneNode, const aiScene* scene);

        static void ReadMesh(aiMesh* src, Mesh* dest);

        static void ReadMaterial(std::string directory, aiMaterial* src, Material* dest, std::vector<Texture2D*>* texturesLoaded);

        static inline std::vector<Texture2D*> LoadMaterialTexture2Ds(std::string directory, std::vector<Texture2D*>* texturesLoaded, aiMaterial* mat, aiTextureType type, TextureType typeName);
    };
}

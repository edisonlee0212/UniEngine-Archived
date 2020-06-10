#pragma once
#include "Core.h"
#include "Texture2D.h"
#include "MeshMaterialComponent.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
namespace UniEngine {
    class ModelManager : public ManagerBase
    {
    public:
        static void LoadModelAsEntity(Entity* root, std::string const& path, GLProgram* shader = nullptr, bool gamma = false);
    private:
        static std::vector<Entity*> entities;
        static void ProcessNode(std::string, GLProgram* shader, Entity*, std::vector<Texture2D*>*, aiNode*, const aiScene*);
        static Entity* ReadMesh(std::string, GLProgram* shader, std::vector<Texture2D*>* texturesLoaded, aiMesh* mesh, const aiScene* scene);
        static std::vector<Texture2D*> LoadMaterialTextures(std::string, std::vector<Texture2D*>* texturesLoaded, aiMaterial* mat, aiTextureType type, TextureType typeName);
    };
}

#pragma once
#include "UniEngineAPI.h"
#include "Texture2D.h"
#include "MeshMaterialComponent.h"
#include "Model.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
namespace UniEngine {
    class UNIENGINE_API ModelManager : public ManagerBase
    {
        static std::vector<Entity> entities;
        static void ProcessNode(std::string, GLProgram* shader, ModelNode* modelNode, std::vector<Texture2D*>*, aiNode*, const aiScene*);
        static void ReadMesh(unsigned meshIndex, ModelNode* modelNode, std::string, GLProgram* shader, std::vector<Texture2D*>* texturesLoaded, aiMesh* mesh, const aiScene* scene);
        static std::vector<Texture2D*> LoadMaterialTextures(std::string, std::vector<Texture2D*>* texturesLoaded, aiMaterial* mat, aiTextureType type, TextureType typeName);
        static void AttachChildren(EntityArchetype archetype, ModelNode* modelNode, Entity parentEntity);
    public:
        static Model* LoadModel(std::string const& path, GLProgram* shader = nullptr, bool gamma = false);
        static Entity ToEntity(EntityArchetype archetype, Model* model);
    };
}

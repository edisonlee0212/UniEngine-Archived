#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Texture2D.h"
#include "MeshRenderer.h"
#include "Model.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "FileBrowser.h"

namespace UniEngine {
    class UNIENGINE_API ModelManager : public ManagerBase
    {
        static bool _EnableListMenu;
        static FileBrowser _FileBrowser;
        static std::vector<std::shared_ptr<Model>> _Models;
        static void ProcessNode(std::string, std::shared_ptr<GLProgram> shader, ModelNode* modelNode, std::vector<std::shared_ptr<Texture2D>>&, aiNode*, const aiScene*);
        static void ReadMesh(unsigned meshIndex, ModelNode* modelNode, std::string directory, std::shared_ptr<GLProgram> shader, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene);
        static void AttachChildren(EntityArchetype archetype, ModelNode* modelNode, Entity parentEntity);
    public:
        static void RemoveModel(int index);
        static void OnGui();
        static std::shared_ptr<Model> LoadModel(std::string const& path, std::shared_ptr<GLProgram> shader, bool gamma = false);
        static Entity ToEntity(EntityArchetype archetype, std::shared_ptr<Model> model);
    };
}

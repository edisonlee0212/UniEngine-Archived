#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace TreeCreator {
    class TreeManager :
        public ManagerBase
    {
        friend class TreeBudSystem;
        static bool _Ready;
        static EntityQuery _TreeQuery;
        static void Init(EntityQuery treeQuery);

    public:
        static void GetAllTrees(std::vector<Entity>* container);
        static void GenerateMeshForAllTrees();
        static Mesh* GetMeshFromTree(Entity treeEntity);
        static void GenerateMeshForTree(Entity treeEntity);
    };

}
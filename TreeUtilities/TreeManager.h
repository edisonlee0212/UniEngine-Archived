#pragma once
#include "TreeUtilitiesAPI.h"
#include "TreeBudSystem.h"
using namespace UniEngine;
namespace TreeUtilities {
    class TREEUTILITIES_API TreeManager :
        public ManagerBase
    {
        friend class TreeBudSystem;
        static TreeBudSystem* _TreeBudSystem;
        static bool _Ready;
        static EntityQuery _TreeQuery;
    public:
        static void Init();
        static void GetAllTrees(std::vector<Entity>* container);
        static void GenerateMeshForAllTrees();
        static Mesh* GetMeshFromTree(Entity treeEntity);
        static void GenerateMeshForTree(Entity treeEntity);
    };
}

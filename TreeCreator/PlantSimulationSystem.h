#pragma once
#include "UniEngine.h"
#include "TreeManager.h"
using namespace UniEngine;
using namespace TreeUtilities;
namespace TreeUtilities {
    enum PlantSimulationSystemConfigFlags {
        PlantSimulationSystem_None = 0,
    };

    struct Branch {
        bool Activated;
        Entity BranchEntity;
    };

    struct Branches {
        Entity TreeEntity;
        std::vector<Branch> Branches;
    };

    class PlantSimulationSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;

        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        std::vector<Branches> _TreeActivatedBranchesLists;

        void DeactivateBranch(size_t listIndex, size_t index);
        bool GenerateShootsFromBud(Entity budEntity, Entity branchEntity, bool isLateral);
        void DrawGUI();
        void DestroyedTreeCheck();
        void GrowTree(size_t index);
    public:
        void GrowAllTrees();
        void GrowTree(Entity treeEntity);
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        Entity CreateTree(TreeColor color, glm::vec3 position, bool enabled = false);
    };
}

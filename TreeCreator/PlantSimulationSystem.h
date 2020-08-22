#pragma once
#include "UniEngine.h"
#include "TreeManager.h"
using namespace UniEngine;
using namespace TreeUtilities;
namespace TreeUtilities {
    enum PlantSimulationSystemConfigFlags {
        PlantSimulationSystem_None = 0,
    };

    struct BranchNode {
        bool Activated;
        Entity BranchNodeEntity;
    };

    struct BranchNodesCollection {
        Entity TreeEntity;
        std::vector<BranchNode> BranchNodes;
    };

    class PlantSimulationSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;

        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        std::vector<BranchNodesCollection> _TreeActivatedBranchNodesLists;
        void DeactivateBud(Entity bud, Entity branchNode, BudInfo* budInfo, BranchNodeInfo* branchNodeInfo);
        void DeactivateBranch(size_t listIndex, size_t index);
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

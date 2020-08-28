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

        std::queue<Entity> _TreeLeafPrunineQueue;
        bool _NeedRefresh;
        float GetApicalControl(BranchNodeInfo* branchNodeInfo, TreeParameters* tps, TreeAge* treeAge, int level);
        void DeactivateBud(Entity bud, Entity branchNode, BudInfo* budInfo, BranchNodeInfo* branchNodeInfo);
        void DeactivateBranch(size_t listIndex, size_t index);
        void DrawGUI();
        void DestroyedTreeCheck();
        bool GrowTree(size_t index);
        void ProneLeaves();
    public:
        void GrowAllTrees();
        void CompleteAllTrees();
        void CompleteTree(Entity treeEntity);
        void GrowTree(Entity treeEntity);
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        Entity CreateTree(TreeParameters parameters, TreeColor color, glm::vec3 position, bool enabled = false);
        Entity CreateExampleTree(TreeColor color, glm::vec3 position, int index, bool enabled = false);
    };
}
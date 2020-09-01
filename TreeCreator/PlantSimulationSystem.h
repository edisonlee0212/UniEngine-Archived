#pragma once
#include "UniEngine.h"
#include "TreeManager.h"
using namespace UniEngine;
using namespace TreeUtilities;
namespace TreeUtilities {
    enum PlantSimulationSystemConfigFlags {
        PlantSimulationSystem_None = 0,
    };

    
    class PlantSimulationSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;

        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;
        
        float GetApicalControl(TreeInfo& treeInfo, BranchNodeInfo& branchNodeInfo, TreeParameters& treeParameters, TreeAge& treeAge, int level);
        void DrawGUI();
        void UpdateBranchNodeLength(Entity& branchNode);
        void UpdateBranchNodeLevel(Entity& branchNode);
        void UpdateBranchNodeMeanData(Entity& branchNode, unsigned treeAge);
        void UpdateLocalTransform(Entity& branchNode, Translation& parentTranslation, Rotation& parentRotation, Scale& parentScale);
        bool GrowShoots(Entity& branchNode, TreeInfo& treeInfo, TreeAge& treeAge, TreeParameters& treeParameters, TreeIndex& treeIndex);
        void DeactivateBud(BranchNodeInfo& branchNodeInfo, Bud& bud);
        void ComputeSagging(Entity& branchNode);

        void EvaluatePruning(Entity& branchNode, TreeParameters& treeParameters);
    public:
        void CompleteAllTrees();
        void CompleteTree(Entity treeEntity);
        bool GrowTree(Entity treeEntity);
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        Entity CreateTree(TreeParameters parameters, TreeColor color, glm::vec3 position, bool enabled = false);
        Entity CreateExampleTree(TreeColor color, glm::vec3 position, int index, bool enabled = false);
    };
}

#pragma once
#include "TreeUtilitiesAPI.h"
#include "TreeSystem.h"
#include "BranchSystem.h"
#include "BudSystem.h"
#include "LeafSystem.h"
#include "LightEstimator.h"
using namespace UniEngine;
namespace TreeUtilities {
#pragma region Common
    struct TREEUTILITIES_API TreeIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const TreeIndex& other) const {
            return other.Value == Value;
        }
    };

    struct TREEUTILITIES_API Direction {
        glm::vec3 Value;
        bool operator ==(const Direction& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API Mass : ComponentBase {
        float Value;
        bool operator ==(const Mass& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API LocalPosition : ComponentBase {
        glm::vec3 Value;
        bool operator ==(const LocalPosition& other) const {
            return other.Value == Value;
        }
    };
    
    struct TREEUTILITIES_API Connection : ComponentBase {
        glm::mat4 Value;
        bool operator ==(const Connection& other) const {
            return other.Value == Value;
        }
    };
#pragma endregion
#pragma region Leaf
    struct TREEUTILITIES_API LeafIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const LeafIndex& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API LeafInfo : ComponentBase {
        float BendDegrees = 90.0f;
        float CircleDegreeAddition = 120.0f;
    };
#pragma endregion
#pragma region Bud
    struct TREEUTILITIES_API Radius : ComponentBase
    {
        float Value;
        bool operator ==(const Radius& other) const {
            return other.Value == Value;
        }
    };

    struct TREEUTILITIES_API BudIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const BudIndex& other) const {
            return other.Value == Value;
        }
    };

    struct TREEUTILITIES_API Iteration : ComponentBase {
        unsigned Value;
        bool operator ==(const Iteration& other) const {
            return other.Value == Value;
        }
    };
    //Gravelius Order
    struct TREEUTILITIES_API Level : ComponentBase {
        unsigned Value;
        bool operator ==(const Level& other) const {
            return other.Value == Value;
        }
    };
    //Different bud type will affect their way of growth. 
    enum TREEUTILITIES_API BudTypes {
        LATERAL_BUD,
        APICAL_BUD
    };
    struct TREEUTILITIES_API BudInfo : ComponentBase {
        bool Searching;
        BudTypes Value;
        bool operator ==(const BudInfo& other) const {
            return (other.Value == Value) && (other.Searching == Searching);
        }
    };
#pragma endregion
#pragma region Branch
    struct TREEUTILITIES_API BranchIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const BranchIndex& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API BranchInfo : ComponentBase {
        float Length;
        float Thickness;
        float Deformation;
        float Straightness;
        float Slope;
        float SiblingAngle;
        float ParentAngle;
    };
#pragma endregion
#pragma region Tree
    struct TREEUTILITIES_API GeometricParamGroup : ComponentBase {
        glm::vec3 ApicalAngleVariance;
        int LateralBudNumber;

        float MeanBranchingAngle;
        float VarianceBranchingAngle;

        float MeanRollAngle;
        float VarianceRollAngle;
    };

    struct TREEUTILITIES_API BudFateParamGroup : ComponentBase {
        float ApicalBudExtintionRate;
        float LateralBudEntintionRate;
        
        float ApicalBudLightingFactor;
        float LateralBudLightingFactor;
        
        float ApicalDominanceBase;
        float ApicalDominanceDistance;
        float ApicalDominanceAgeFactor;
        
        float GrowthRate;
        
        float InternodeLength;
        float InternodeAgeFactor;

        float ApicalControlLevel;
        float ApicalAgeFactor;
    };

    struct TREEUTILITIES_API EnvironmentalParamGroup : ComponentBase {
        float Phototropism;
        float Gravitropism;

        float PruningFactor;
        float LowBranchPruningFactor;

        float GravityBendingStrength;
        float GravityBendingAngleFactor;
    };
    
    struct TREEUTILITIES_API RewardEstimation : ComponentBase {
        float LightEstimationResult = 0.0f;
    };

    struct TREEUTILITIES_API TreeGrowIteration : ComponentBase {
        int Value;
        bool Enable;
    };

    struct TREEUTILITIES_API TreeColor : ComponentBase {
        glm::vec4 Color;
        glm::vec4 BudColor;
        glm::vec4 ConnectionColor;
        glm::vec4 LeafColor;
        bool operator ==(const TreeColor& other) const {
            return other.Color == Color
                && other.BudColor == BudColor
                && other.ConnectionColor == ConnectionColor
                && other.LeafColor == LeafColor;
        }
    };
    struct TREEUTILITIES_API TreeInfo : ComponentBase {

    };
#pragma endregion
    class TREEUTILITIES_API TreeManager :
        public ManagerBase
    {
        static LightEstimator* _LightEstimator;

        static TreeSystem* _TreeSystem;
        static BranchSystem* _BranchSystem;
        static BudSystem* _BudSystem;
        static LeafSystem* _LeafSystem;
        

        static EntityArchetype _BudArchetype;
        static EntityArchetype _BranchArchetype;
        static EntityArchetype _LeafArchetype;
        static EntityArchetype _TreeArchetype;

        static EntityQuery _TreeQuery;
        static EntityQuery _BranchQuery;
        static EntityQuery _BudQuery;
        static EntityQuery _LeafQuery;

        static TreeIndex _TreeIndex;
        static BudIndex _BudIndex;
        static LeafIndex _LeafIndex;
        static BranchIndex _BranchIndex;

        static bool _Ready;
        
        static void LeafGenerationHelper(LeafInfo info, Entity leaf, Entity bud, int index);
    public:
        static void Init();
        static bool IsReady();

        static EntityQuery GetBudQuery();
        static EntityQuery GetTreeQuery();
        static EntityQuery GetLeafQuery();
        static EntityQuery GetBranchQuery();

        static BudSystem* GetBudSystem();
        static TreeSystem* GetTreeSystem();
        static LeafSystem* GetLeafSystem();
        static BranchSystem* GetBranchSystem();

        static void GetAllTrees(std::vector<Entity>* container);
        
        static void GenerateLeavesForTree(Entity treeEntity, LeafInfo leafInfo);
        static void GenerateLeavesForAllTrees(LeafInfo leafInfo);

        static Mesh* GetMeshForTree(Entity treeEntity);
        static void GenerateMeshForTree(Entity treeEntity);
        static void GenerateMeshForAllTrees();
        static void DeleteTree(Entity treeEntity);

        static Entity CreateTree();
        
        static Entity CreateBud(TreeIndex treeIndex, Entity parentEntity);
        static Entity CreateLeaf(TreeIndex treeIndex, Entity parentEntity);
        static Entity CreateBranch(TreeIndex treeIndex, Entity parentEntity);

        static LightEstimator* GetLightEstimator();

        static void CalculateRewards(Entity treeEntity, float snapShotWidth = 100.0f);
    };
}

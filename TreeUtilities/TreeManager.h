#pragma once
#include "TreeUtilitiesAPI.h"
#include "TreeSystem.h"
#include "BranchSystem.h"
#include "BranchNodeSystem.h"
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
        bool Illumated;
    };
#pragma endregion
#pragma region Bud
    struct TREEUTILITIES_API Activated : ComponentBase {
        bool Value;
        bool operator ==(const Activated& other) const {
            return other.Value == Value;
        }
    };

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
        LATERAL,
        APICAL
    };
    struct TREEUTILITIES_API BudInfo : ComponentBase {
        bool Searching = false;
        BudTypes Type = BudTypes::APICAL;
        float Inhibitor = 0;
        int StartAge = -1;

        float LeafWidth = 0.4f;
        float LeafThickness = 1.0f;
        float LeafLength = 0.6f;
        int LeafAmount = 3;
        float BendDegrees = 30.0f;
        float CircleDegreeStart = -40.0f;
        float CircleDegreeAddition = 40.0f;
    };

    struct TREEUTILITIES_API BudIllumination : ComponentBase {
        float Value;
    };

    struct TREEUTILITIES_API BranchNodeOwner : ComponentBase {
        Entity Value;
    };
#pragma endregion
#pragma region BranchNode
    struct TREEUTILITIES_API BranchNodeBudsList : ComponentBase {
        std::vector<Entity>* Buds;
    };
    struct TREEUTILITIES_API BranchNodeIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const BranchNodeIndex& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API BranchNodeInfo : ComponentBase {
        int MaxChildLevel;
        float Inhibitor = 0;
        float ParentInhibitorFactor = 1;
        int ActivatedBudsAmount = 0;
        int Level = 0;
        float DistanceToParent = 0;
        bool ApicalBudExist = false;
        float Length;
        float Thickness;
        float Deformation;
        float Straightness;
        float Slope;
        float SiblingAngle;
        float ParentAngle;
        glm::quat DesiredBranchDirection;
    };
#pragma endregion
#pragma region Tree
    struct TREEUTILITIES_API TreeParameters : ComponentBase {
#pragma region Geometric
        int LateralBudNumber;

        float VarianceApicalAngle; // Training target

        float MeanBranchingAngle; // Training target
        float VarianceBranchingAngle; // Training target

        float MeanRollAngle; // Training target
        float VarianceRollAngle; // Training target
#pragma endregion
#pragma region Bud fate
        float ApicalBudExtintionRate; // Useless.
        float LateralBudEntintionRate; //Useless.

        float ApicalDominanceBase; // Training target
        float ApicalDominanceDistanceFactor; // Training target
        float ApicalDominanceAgeFactor; // Training target

        float GrowthRate;

        float InternodeLengthBase; //Fixed
        float InternodeLengthAgeFactor; // Training target

        float ApicalControl; // Training target
        float ApicalControlAgeDescFactor; // Training target
        float ApicalControlLevelFactor; // Training target
        float ApicalControlDistanceFactor; // Training target

        int MaxBudAge;
#pragma endregion
#pragma region Environmental
        float Phototropism; // Based on tree leaf properties.
        float GravitropismBase; //Based on tree material properties.
        float GravitropismLevelFactor;  //Based on tree material properties.

        float PruningFactor; 
        float LowBranchPruningFactor;

        float GravityBendingStrength;
        float GravityBendingAngleFactor;

        float ApicalBudLightingFactor;
        float LateralBudLightingFactor;
#pragma endregion
        size_t Age;
    };
    
    struct TREEUTILITIES_API RewardEstimation : ComponentBase {
        float LightEstimationResult = 0.0f;
    };

    struct TREEUTILITIES_API TreeAge : ComponentBase {
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
        float Height;
        float ActiveLength;
        int MaxBranchingDepth;
        size_t LateralBudsCount;
        std::vector<float>* ApicalDominanceTimeVal;
        std::vector<float>* GravitropismLevelVal;
        float ResourceToGrow;
    };
#pragma endregion
    class TREEUTILITIES_API TreeManager :
        public ManagerBase
    {
        static LightEstimator* _LightEstimator;

        static TreeSystem* _TreeSystem;
        static BranchNodeSystem* _BranchNodeSystem;
        static BudSystem* _BudSystem;
        static LeafSystem* _LeafSystem;
        

        static EntityArchetype _BudArchetype;
        static EntityArchetype _LeafArchetype;
        static EntityArchetype _BranchNodeArchetype;
        static EntityArchetype _TreeArchetype;

        static EntityQuery _TreeQuery;
        static EntityQuery _BranchNodeQuery;
        static EntityQuery _BudQuery;
        static EntityQuery _LeafQuery;

        static TreeIndex _TreeIndex;
        static BranchNodeIndex _BranchNodeIndex;
        static BudIndex _BudIndex;
        static LeafIndex _LeafIndex;

        static bool _Ready;
        
        static void LeafGenerationHelper(BudInfo& info, Entity& leaf, Entity& bud, int index);
        
        static void BranchRemover(Entity branchEntity);
    public:
        static void Init();
        static bool IsReady();

        static EntityQuery GetBudQuery();
        static EntityQuery GetBranchNodeQuery();
        static EntityQuery GetTreeQuery();
        static EntityQuery GetLeafQuery();

        static BudSystem* GetBudSystem();
        static BranchNodeSystem* GetBranchNodeSystem();
        static TreeSystem* GetTreeSystem();
        static LeafSystem* GetLeafSystem();

        static void GetAllTrees(std::vector<Entity>* container);
        
        static void GenerateLeavesForTree(Entity treeEntity);
        static void ProneLeavesForTree(Entity treeEntity);
        static void GenerateLeavesForAllTrees();

        static Mesh* GetMeshForTree(Entity treeEntity);
        static void GenerateMeshForTree(Entity treeEntity);
        static void GenerateMeshForAllTrees();
        static void DeleteTree(Entity treeEntity);

        static Entity CreateTree();
        static Entity CreateBranchNode(TreeIndex treeIndex, Entity parentEntity);
        static Entity CreateBud(TreeIndex treeIndex, Entity parentEntity);
        static Entity CreateBudForBranchNode(TreeIndex treeIndex, Entity branchEntity);
        static Entity CreateLeaf(TreeIndex treeIndex, Entity parentEntity);

        static LightEstimator* GetLightEstimator();

        static void CalculateRewards(Entity treeEntity, float snapShotWidth = 100.0f);
    };
}

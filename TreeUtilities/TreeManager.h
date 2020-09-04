#pragma once
#include "TreeUtilitiesAPI.h"
#include "TreeSystem.h"
#include "BranchSystem.h"
#include "BranchNodeSystem.h"
#include "LeafSystem.h"
#include "LightEstimator.h"

#include "RingMesh.h"
#include "BezierCurve.h"
using namespace UniEngine;
namespace TreeUtilities {
#pragma region Common
    struct TREEUTILITIES_API TreeIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const TreeIndex& other) const {
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
        float Illumination;
        glm::vec3 WeightedLightDirection;
    };
    struct TREEUTILITIES_API LeafAlive : ComponentBase {
        bool Value;
        bool operator ==(const LeafAlive& other) const {
            return other.Value == Value;
        }
    };
#pragma endregion
#pragma region BranchNode
    struct BranchNodeRingList : ComponentBase {
        std::vector<RingMesh>* Rings;
    };

    struct TREEUTILITIES_API Connection : ComponentBase {
        glm::mat4 Value;
        bool operator ==(const Connection& other) const {
            return other.Value == Value;
        }
    };

    struct TREEUTILITIES_API Illumination : ComponentBase {
        float Value;
        glm::vec3 LightDir;
    };
    struct TREEUTILITIES_API BaseBudEntity : ComponentBase {
        Entity Value;
    };

    struct TREEUTILITIES_API Bud {
        bool IsActive;
        bool IsApical;
        unsigned StartAge;
        glm::vec3 EulerAngles;
    };

    struct TREEUTILITIES_API Gravity {
        float Value;
    };

    struct TREEUTILITIES_API BudList : ComponentBase {
        std::vector<Bud>* Buds;
    };


    struct TREEUTILITIES_API BranchNodeIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const BranchNodeIndex& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API BranchNodeInfo : ComponentBase {
#pragma region General
        int Level = 0;
        float DistanceToParent = 0;
        float DistanceToBranchEnd = 0;
        float TotalDistanceToBranchEnd = 0;
        float DistanceToBranchStart = 0;
        float AccmulatedLength = 0;
        float AccmulatedLight = 0;
        float AccmulatedActivatedBudsAmount = 0;
        float AccmulatedGravity = 0;
        unsigned NumValidChild;
#pragma endregion
#pragma region Growth
        int MaxChildLevel;
        int MaxActivatedChildLevel;
        float Inhibitor = 0;
        float ParentInhibitorFactor = 1;
        int ActivatedBudsAmount = 0;
        unsigned BranchEndNodeAmount;
        bool Pruned;
        bool IsApical;
        bool ApicalBudExist = false;
#pragma endregion
#pragma region Geometric
        float Length;
        float Thickness;
        float Deformation;
        float Straightness;
        float Slope;
        float SiblingAngle;
        float ParentAngle;
#pragma endregion
#pragma region Transformation
        glm::quat DesiredGlobalRotation;
        glm::quat DesiredLocalRotation;
        glm::mat4 GlobalTransform;
        glm::mat4 LocalTransform;
#pragma endregion
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

        float ApicalBudLightingFactor;
        float LateralBudLightingFactor;
#pragma endregion

#pragma region Sagging
        float GravityFactor;
        float GravityBackPropageteFixedCoefficient;
#pragma endregion

        size_t Age;
        float EndNodeThickness = 0.01f;
        float ThicknessControlFactor = 1.0f;
    };
    
    struct TREEUTILITIES_API TreeLeafPruningFactor : ComponentBase {
        float Value = 0.0f;
    };

    struct TREEUTILITIES_API RewardEstimation : ComponentBase {
        float LightEstimationResult = 0.0f;
    };

    struct TREEUTILITIES_API TreeAge : ComponentBase {
        unsigned Value;
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
        std::vector<float>* ApicalControlTimeVal;
        std::vector<Vertex>* Vertices;
        std::vector<unsigned>* Indices;
        std::vector<std::vector<float>>* ApicalControlTimeLevelVal;
        float ResourceToGrow;
    };
#pragma endregion
    class TREEUTILITIES_API TreeManager :
        public ManagerBase
    {
        static LightEstimator* _LightEstimator;

        static TreeSystem* _TreeSystem;
        static BranchNodeSystem* _BranchNodeSystem;
        static LeafSystem* _LeafSystem;
        

        static EntityArchetype _LeafArchetype;
        static EntityArchetype _BranchNodeArchetype;
        static EntityArchetype _TreeArchetype;

        static EntityQuery _TreeQuery;
        static EntityQuery _BranchNodeQuery;
        static EntityQuery _LeafQuery;

        static TreeIndex _TreeIndex;
        static BranchNodeIndex _BranchNodeIndex;
        static LeafIndex _LeafIndex;

        static bool _Ready;
        
        //static void LeafGenerationHelper(BudInfo& info, Entity& leaf, Entity& bud, int index);
        static void SimpleMeshGenerator(Entity& branchNode, std::vector<Vertex>& vertices, float resolution);
        static void BranchNodeCleaner(Entity branchEntity);
    public:
        static void Init();
        static bool IsReady();

        static EntityQuery GetBranchNodeQuery();
        static EntityQuery GetTreeQuery();
        static EntityQuery GetLeafQuery();

        static BranchNodeSystem* GetBranchNodeSystem();
        static TreeSystem* GetTreeSystem();
        static LeafSystem* GetLeafSystem();

        static void GetAllTrees(std::vector<Entity>* container);
        
        //static void GenerateLeavesForTree(Entity treeEntity);
        static void CalculateBranchNodeIllumination();
        //static void GenerateLeavesForAllTrees();

        static Mesh* GetMeshForTree(Entity treeEntity);
        static void GenerateSimpleMeshForTree(Entity treeEntity, float resolution);
        static void DeleteTree(Entity treeEntity);

        static Entity CreateTree(Material* treeSurfaceMaterial);
        static Entity CreateBranchNode(TreeIndex treeIndex, Entity parentEntity);
        static Entity CreateLeaf(TreeIndex treeIndex, Entity parentEntity);

        static LightEstimator* GetLightEstimator();

        static void CalculateRewards(Entity treeEntity, float snapShotWidth = 100.0f);
    };
}

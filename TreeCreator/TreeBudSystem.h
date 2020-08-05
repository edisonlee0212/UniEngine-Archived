#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace TreeCreator {
#pragma region Common
    struct ParentTranslation {
        glm::vec3 Value;
    };
    struct Mass : ComponentBase {
        float Value;
    };
    struct Position : ComponentBase {
        glm::vec3 Value;
    };
    struct Direction : ComponentBase
    {
        glm::vec3 Value;
    };
    struct Connection : ComponentBase {
        glm::mat4 Value;
    };
#pragma endregion
#pragma region Leaf
    struct LeafIndex : ComponentBase {
        unsigned Value;
    };
#pragma endregion
#pragma region Bud
    struct Radius : ComponentBase
    {
        float Value;
    };

    struct BudIndex : ComponentBase {
        unsigned Value;
    };

    struct Iteration : ComponentBase {
        unsigned Value;
    };
    //Gravelius Order
    struct Level : ComponentBase {
        unsigned Value;
    };

    struct Phototropism : ComponentBase {
        float Value;
    };

    //Branches tend to grow against gravity
    struct Gravitropism : ComponentBase {
        float Value;
    };

    //Different bud type will affect their way of growth. 
    enum BudTypes {
        LATERAL_BUD,
        APICAL_BUD
    };
    struct BudType : ComponentBase {
        bool Searching;
        BudTypes Value;
    };
#pragma endregion
#pragma region Tree
    struct TreeIndex : ComponentBase {
        unsigned Value;
    };
#pragma endregion
    struct TreeBud {
        Entity entity;
        Entity parent;
        std::vector<Entity> children;
        std::vector<Entity> leaves;
    };
    struct Tree {
        Entity _TreeEntity;
        Entity _BudRoot;
    };

    class TreeBudSystem :
        public SystemBase
    {
        bool _DrawLeaves;
        bool _DrawBuds;
        bool _DrawConnections;
        EntityArchetype _BudArchetype;
        EntityArchetype _LeafArchetype;
        EntityArchetype _TreeArchetype;
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        EntityQuery _ParentTranslationQuery;
        EntityQuery _ConnectionQuery;
        Material* _BudMaterial;
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        void RefreshParentTranslations();
        void RefreshConnections(float lineWidth);
        EntityArchetype GetBudArchetype();
        EntityArchetype GetLeafArchetype();
        EntityArchetype GetTreeArchetype();
        EntityQuery GetBudQuery();
        EntityQuery GetTreeQuery();
        EntityQuery GetLeafQuery();
    };
}

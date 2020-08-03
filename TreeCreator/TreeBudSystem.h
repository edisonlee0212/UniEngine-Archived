#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace TreeCreator {
#pragma region Common
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
        EntityArchetype _BudArchetype;
        EntityArchetype _LeafArchetype;
        EntityArchetype _TreeArchetype;
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        EntityArchetype GetBudArchetype();
        EntityArchetype GetLeafArchetype();
        EntityArchetype GetTreeArchetype();
        EntityQuery GetBudQuery();
        EntityQuery GetTreeQuery();
        EntityQuery GetLeafQuery();
    };
}

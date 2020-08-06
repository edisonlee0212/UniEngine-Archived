#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
#pragma region Common
    struct TREEUTILITIES_API TreeIndex : ComponentBase {
        unsigned Value;
        bool operator ==(const TreeIndex& other) const {
            return other.Value == Value;
        }
    };

    struct TREEUTILITIES_API ParentTranslation {
        glm::vec3 Value;
        bool operator ==(const ParentTranslation& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API Mass : ComponentBase {
        float Value;
        bool operator ==(const Mass& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API Position : ComponentBase {
        glm::vec3 Value;
        bool operator ==(const Position& other) const {
            return other.Value == Value;
        }
    };
    struct TREEUTILITIES_API Direction : ComponentBase
    {
        glm::vec3 Value;
        bool operator ==(const Direction& other) const {
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
    struct TREEUTILITIES_API LeafType : ComponentBase {

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

    struct TREEUTILITIES_API Phototropism : ComponentBase {
        float Value;
        bool operator ==(const Phototropism& other) const {
            return other.Value == Value;
        }
    };

    //Branches tend to grow against gravity
    struct TREEUTILITIES_API Gravitropism : ComponentBase {
        float Value;
        bool operator ==(const Gravitropism& other) const {
            return other.Value == Value;
        }
    };

    //Different bud type will affect their way of growth. 
    enum TREEUTILITIES_API BudTypes {
        LATERAL_BUD,
        APICAL_BUD
    };
    struct TREEUTILITIES_API BudType : ComponentBase {
        bool Searching;
        BudTypes Value;
        bool operator ==(const BudType& other) const {
            return (other.Value == Value) && (other.Searching == Searching);
        }
    };
#pragma endregion
#pragma region Tree
    struct TREEUTILITIES_API TreeColor : ComponentBase {
        glm::vec4 BudColor;
        glm::vec4 ConnectionColor;
    };
    struct TREEUTILITIES_API TreeType : ComponentBase {

    };
#pragma endregion

    class TREEUTILITIES_API TreeBudSystem :
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
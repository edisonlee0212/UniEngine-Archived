#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum BudSystemConfigFlags {
        BudSystem_None = 0,
        BudSystem_DrawBuds = 1 << 0,
    };
    class Connection;
    class BudSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;
        float _ConnectionWidth = 0.05f;
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        EntityQuery _ConnectionQuery;
        Material* _BudMaterial;

        std::vector<LocalToWorld> _BudLTWList;

        std::vector<Entity> _BudEntities;
        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        TREEUTILITIES_API std::vector<Entity>* GetBudEntities();
    };
}
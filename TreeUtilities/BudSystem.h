#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum BudSystemConfigFlags {
        BudSystem_None = 0,
        BudSystem_DrawBuds = 1 << 0,
        BudSystem_DrawConnections = 1 << 1

    };
    class Connection;
    class TREEUTILITIES_API BudSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;

        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        EntityQuery _ParentTranslationQuery;
        EntityQuery _ConnectionQuery;
        Material* _BudMaterial;

        std::vector<LocalToWorld> _BudLTWList;
        std::vector<Connection> _ConnectionList;

        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        void RefreshParentTranslations();
        void RefreshConnections(float lineWidth);
    };
}
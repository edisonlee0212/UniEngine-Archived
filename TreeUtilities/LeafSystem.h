#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum LeafSystemConfigFlags {
        LeafSystem_None = 0,
        LeafSystem_DrawLeafs = 1 << 0,
    };
    class LeafSystem :
        public SystemBase
    {
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
    };
}


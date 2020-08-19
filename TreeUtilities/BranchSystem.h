#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum BranchSystemConfigFlags {
        BranchSystem_None = 0,
    };
    class BranchSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;
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


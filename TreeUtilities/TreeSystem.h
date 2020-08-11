#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum TreeSystemConfigFlags {
        TreeSystem_None = 0,
        TreeSystem_DrawTrees = 1 << 0,
        TreeSystem_DrawTreeMeshes = 1 << 1
    };
    class TreeSystem :
        public SystemBase
    {
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        std::vector<Entity> _TreeEntities;
        void BudListHelper(Entity budEntity);
        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
    };
}

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
        unsigned int _ConfigFlags = 0;
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        std::vector<Entity> _TreeEntities;

        Entity _SelectedTreeEntity;
        void BudListHelper(Entity budEntity);
        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        TREEUTILITIES_API std::vector<Entity>* GetTreeEntities();
    };
}

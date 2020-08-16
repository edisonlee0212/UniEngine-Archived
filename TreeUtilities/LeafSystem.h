#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum LeafSystemConfigFlags {
        LeafSystem_None = 0,
        LeafSystem_DrawLeafs = 1 << 0,
        LeafSystem_SeperateTrees = 1 << 1
    };
    class LeafSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;
        EntityQuery _BudQuery;
        EntityQuery _LeafQuery;
        EntityQuery _TreeQuery;

        std::vector<Entity> _LeafEntities;
        std::vector<LocalToWorld> _LeafLTWList;

        Mesh* _LeafMesh;
        Material* _LeafMaterial;
        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void FixedUpdate();
        Mesh* GetLeafMesh();
        TREEUTILITIES_API std::vector<Entity>* GetTreeEntities();
    };
}


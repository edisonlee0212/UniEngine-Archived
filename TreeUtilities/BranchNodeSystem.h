#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
    enum BranchNodeSystemConfigFlags {
        BranchNodeSystem_None = 0,
        BranchNodeSystem_DrawBranchNodes = 1 << 0,
        BranchNodeSystem_DrawConnections = 1 << 1

    };
    class Connection;
    class BranchNodeSystem :
        public SystemBase
    {
        unsigned int _ConfigFlags = 0;
        EntityQuery _BranchNodeQuery;

        float _ConnectionWidth = 0.05f;

        std::vector<LocalToWorld> _BranchNodeLTWList;
        std::vector<Connection> _ConnectionList;
        void DrawGUI();
    public:
        void OnCreate();
        void OnDestroy();
        void Update();
        void RefreshConnections();
    };
}

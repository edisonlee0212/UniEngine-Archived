#pragma once
#include "SystemBase.h"
#include "PlanetTerrain.h"
using namespace UniEngine;
namespace Planet{
    class PlanetTerrainSystem :
        public SystemBase
    {
        std::vector<PlanetTerrain*> _PlanetTerrainList;
        Entity* _TargetCameraEntity;
        std::queue<TerrainChunk*> _GenerationQueue;
        std::queue<unsigned> _RecycleQueue;
        float _LodDistance;
    public:
        void OnCreate();
        void Update();
        void FixedUpdate();
        void Remove(std::vector<TerrainChunk*>* list, unsigned index);
    };
}
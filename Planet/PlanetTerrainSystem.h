#pragma once
#include "SystemBase.h"
#include "PlanetTerrain.h"
using namespace UniEngine;
namespace Planet{
    class PlanetTerrainSystem :
        public SystemBase
    {
        std::vector<PlanetTerrain*> _PlanetTerrainList;
        Entity _TargetCameraEntity;
        std::queue<TerrainChunk*> _GenerationQueue;
        unsigned _MaxRecycledMeshAmount;
    public:
        void OnCreate();
        void Update();
        void FixedUpdate();
        void Remove(std::vector<TerrainChunk*>* list, unsigned index);
        void GenerateTerrain(PlanetTerrain* planetTerrain, TerrainChunk* targetChunk);
        void SetCameraEntity(Entity targetEntity);
        void SetMaxMeshAmount(unsigned amount);
        void CreatePlanet(PlanetInfo info);
    };
}
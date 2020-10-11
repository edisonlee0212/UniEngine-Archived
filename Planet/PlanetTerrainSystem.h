#pragma once
#include "SystemBase.h"
#include "PlanetTerrain.h"
using namespace UniEngine;
namespace Planet{
    class PlanetTerrainSystem :
        public SystemBase
    {
        std::vector<PlanetTerrain*> _PlanetTerrainList;
        std::queue<TerrainChunk*> _GenerationQueue;
        std::shared_ptr<Material> _DefaultSurfaceMaterial;
        unsigned _MaxRecycledMeshAmount;
    public:
        void OnCreate() override;
        void Update() override;
        void FixedUpdate() override;
        void Remove(std::vector<TerrainChunk*>* list, unsigned index);
        void GenerateTerrain(PlanetTerrain* planetTerrain, TerrainChunk* targetChunk);
        void SetMaxMeshAmount(unsigned amount);
        void CreatePlanet(PlanetInfo info);
    };
}
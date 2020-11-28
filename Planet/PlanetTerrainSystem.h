#pragma once
#include "SystemBase.h"
#include "PlanetTerrain.h"
using namespace UniEngine;
namespace Planet{
	class PlanetTerrainSystem :
		public SystemBase
	{
		std::vector<std::shared_ptr<PlanetTerrain>> _PlanetTerrainList;
		std::queue<std::shared_ptr<TerrainChunk>> _GenerationQueue;
		std::shared_ptr<Material> _DefaultSurfaceMaterial;
		unsigned _MaxRecycledMeshAmount;
	public:
		void OnCreate() override;
		void Update() override;
		void FixedUpdate() override;
		void Remove(std::vector<std::shared_ptr<TerrainChunk>>& list, unsigned index);
		void GenerateTerrain(std::shared_ptr<PlanetTerrain>& planetTerrain, std::shared_ptr<TerrainChunk>& targetChunk) const;
		void SetMaxMeshAmount(unsigned amount);
		void CreatePlanet(PlanetInfo info);
	};
}
#pragma once
#include "UniEngine.h"
#include "TerrainChunk.h"
#include "TerrainConstructionStageBase.h"
using namespace UniEngine;
namespace Planet {
	struct PlanetInfo {
		unsigned MaxLodLevel;
		double LodDistance;
		double Radius;
		unsigned Index;
		unsigned Resolution;
	};

	struct MeshInfo {
		unsigned Index;
		bool Enabled;
		MeshInfo(unsigned index, bool enabled = true) : Index(index), Enabled(enabled) {};
	};

	class PlanetTerrain : public PrivateComponentBase
	{
		friend class TerrainChunk;
		friend class PlanetTerrainSystem;
		std::vector<std::unique_ptr<TerrainChunk>> _Chunks;
		PlanetInfo _Info;
		//Used for fast mesh generation;
		std::vector<Vertex> _SharedVertices;
		std::vector<unsigned> _SharedTriangles;
	public:
		std::shared_ptr<Material> SurfaceMaterial;
		std::vector<std::shared_ptr<TerrainConstructionStageBase>> TerrainConstructionStages;
		PlanetTerrain(PlanetInfo info, std::shared_ptr<Material> surfaceMaterial);
		void OnGui() override;
	};
}

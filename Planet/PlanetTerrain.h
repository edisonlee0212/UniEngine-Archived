#pragma once
#include "UniEngine.h"
#include "TerrainChunk.h"
#include "TerrainConstructionStageBase.h"
using namespace UniEngine;
namespace Planet {
	struct PlanetInfo {
		glm::dvec3 Position;
		glm::quat Rotation;
		unsigned MaxLodLevel;
		float LodDistance;
		double Radius;
		unsigned Index;
		unsigned Resolution;
	};

	struct MeshInfo {
		unsigned Index;
		bool Enabled;
		MeshInfo(unsigned index, bool enabled = true) : Index(index), Enabled(enabled) {};
	};

	class PlanetTerrain : PrivateComponentBase
	{
		friend class PlanetTerrainSystem;
		std::vector<std::shared_ptr<TerrainChunk>> _ChunkList;
		std::vector<std::shared_ptr<TerrainChunk>> _WaitingList;
		std::vector<std::shared_ptr<TerrainChunk>> _RecycledChunkList;
		PlanetInfo _Info;
		std::shared_ptr<Material> _SurfaceMaterial;	
		//Used for fast mesh generation;
		std::vector<Vertex> _SharedVertices;
		std::vector<unsigned> _SharedTriangles;
		std::vector<std::shared_ptr<TerrainConstructionStageBase>> _TerrainConstructionStages;
	public:
		PlanetTerrain(PlanetInfo info, std::shared_ptr<Material> surfaceMaterial, std::queue<std::shared_ptr<TerrainChunk>>& generationQueue);
		~PlanetTerrain();
	};
}

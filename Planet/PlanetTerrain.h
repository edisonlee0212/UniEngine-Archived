#pragma once
#include "UniEngine.h"
#include "TerrainChunk.h"
using namespace UniEngine;

namespace Planet
{
	struct PlanetInfo
	{
		glm::dvec3 Position;
		glm::quat Rotation;
		unsigned MaxLodLevel;
		float LodDistance;
		double Radius;
		unsigned Index;
		unsigned Resolution;
	};

	struct MeshInfo
	{
		unsigned Index;
		bool Enabled;

		MeshInfo(unsigned index, bool enabled = true) : Index(index), Enabled(enabled)
		{
		};
	};

	class PlanetTerrain : SharedComponentBase
	{
		friend class PlanetTerrainSystem;
		std::vector<TerrainChunk*> _ChunkList;
		std::vector<TerrainChunk*> _WaitingList;
		std::vector<TerrainChunk*> _RecycledChunkList;
		PlanetInfo _Info;
		Material* _SurfaceMaterial;
		//Used for fast mesh generation;
		std::vector<Vertex> _SharedVertices;
		std::vector<unsigned> _SharedTriangles;

	public:

		size_t GetHashCode() override;
		PlanetTerrain(PlanetInfo info, Material* surfaceMaterial, std::queue<TerrainChunk*>* generationQueue);
		~PlanetTerrain();
	};
}

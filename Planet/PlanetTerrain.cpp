#include "PlanetTerrain.h"

size_t Planet::PlanetTerrain::GetHashCode()
{
	return (size_t)this;
}

Planet::PlanetTerrain::PlanetTerrain(PlanetInfo info, Material* surfaceMaterial,
                                     std::queue<TerrainChunk*>* generationQueue)
{
	_Info = info;
	_SurfaceMaterial = surfaceMaterial;
	_SharedVertices = std::vector<Vertex>();
	size_t resolution = info.Resolution;
	_SharedVertices.resize(resolution * resolution);
	_SharedTriangles = std::vector<unsigned>();
	_SharedTriangles.resize(resolution * resolution * 6);
	size_t triIndex = 0;
	for (size_t y = 0; y < resolution; y++)
	{
		for (size_t x = 0; x < resolution; x++)
		{
			size_t i = x + y * resolution;

			if (x != resolution - 1 && y != resolution - 1)
			{
				_SharedTriangles[triIndex] = i;
				_SharedTriangles[triIndex + 1] = i + resolution + 1;
				_SharedTriangles[triIndex + 2] = i + resolution;

				_SharedTriangles[triIndex + 3] = i;
				_SharedTriangles[triIndex + 4] = i + 1;
				_SharedTriangles[triIndex + 5] = i + resolution + 1;
				triIndex += 6;
			}
		}
	}

	generationQueue->push(new TerrainChunk(nullptr, 0, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(1, 0, 0)));

	generationQueue->push(new TerrainChunk(nullptr, 1, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, 1, 0)));
	generationQueue->push(new TerrainChunk(nullptr, 2, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, 0, 1)));
	generationQueue->push(new TerrainChunk(nullptr, 3, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(-1, 0, 0)));
	generationQueue->push(new TerrainChunk(nullptr, 4, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, -1, 0)));
	generationQueue->push(new TerrainChunk(nullptr, 5, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, 0, -1)));
}


Planet::PlanetTerrain::~PlanetTerrain()
{
	for (auto i : _ChunkList)
	{
		delete i->_Mesh;
	}
	_ChunkList.clear();
	for (auto i : _RecycledChunkList)
	{
		delete i->_Mesh;
	}
	_RecycledChunkList.clear();
}

#include "PlanetTerrain.h"

Planet::PlanetTerrain::PlanetTerrain(PlanetInfo info, std::shared_ptr<Material> surfaceMaterial)
{
	SetEnabled(true);
	_Info = info;
	SurfaceMaterial = surfaceMaterial;
	_SharedVertices = std::vector<Vertex>();
	size_t resolution = info.Resolution;
	_SharedVertices.resize(resolution * resolution);
	_SharedTriangles = std::vector<unsigned>();
	_SharedTriangles.resize((resolution - 1) * (resolution - 1) * 6);

	size_t triIndex = 0;
	for (size_t y = 0; y < resolution; y++)
	{
		for (size_t x = 0; x < resolution; x++)
		{
			size_t i = x + y * resolution;
			_SharedVertices[i].TexCoords0 = glm::vec2(static_cast<float>(x) / (resolution - 1), static_cast<float>(y) / (resolution - 1));
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
	_Chunks.push_back(std::make_unique<TerrainChunk>(this, nullptr, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(1, 0, 0)));
	_Chunks.push_back(std::make_unique<TerrainChunk>(this, nullptr, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, 1, 0)));
	_Chunks.push_back(std::make_unique<TerrainChunk>(this, nullptr, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, 0, 1)));
	_Chunks.push_back(std::make_unique<TerrainChunk>(this, nullptr, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(-1, 0, 0)));
	_Chunks.push_back(std::make_unique<TerrainChunk>(this, nullptr, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, -1, 0)));
	_Chunks.push_back(std::make_unique<TerrainChunk>(this, nullptr, 0, glm::ivec2(0), ChunkDirection::Root, glm::dvec3(0, 0, -1)));

	std::mutex m;
	for(auto& chunk : _Chunks)
	{
		chunk->GenerateTerrain(m, chunk);
		chunk->Active = true;
	}
}

void Planet::PlanetTerrain::OnGui()
{
	if(SurfaceMaterial) SurfaceMaterial->OnGui();
}


#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace Planet {
	enum class ChunkDirection {
		Root,
		UpperLeft,
		UpperRight,
		LowerLeft,
		LowerRight
	};
	class TerrainChunk {
	public:
		std::unique_ptr<Mesh> _Mesh;
		//The level of detail, the larger the detail, the smaller the chunk will be.
		unsigned DetailLevel;
		//The chunk coordinate in which a chunk belongs to the face
		glm::ivec2 ChunkCoordinate;
		ChunkDirection Direction;
		std::shared_ptr<TerrainChunk> Parent;
		unsigned Index;
		bool TooFar;
		bool ToRecycle;
		//The index of four children, upperleft = 0, upperright = 1, lower left = 2, lower right = 3.
		std::shared_ptr<TerrainChunk> C0;
		std::shared_ptr<TerrainChunk> C1;
		std::shared_ptr<TerrainChunk> C2;
		std::shared_ptr<TerrainChunk> C3;
		glm::dvec3 LocalUp;
		glm::dvec3 AxisA;
		glm::dvec3 AxisB;
		glm::dvec3 ChunkCenterPosition(glm::dvec3 planetPosition, double radius, glm::quat rotation);
		TerrainChunk(std::shared_ptr<TerrainChunk> parent, unsigned index, unsigned detailLevel, glm::ivec2 chunkCoordinate, ChunkDirection direction, glm::dvec3 localUp);
	};
}

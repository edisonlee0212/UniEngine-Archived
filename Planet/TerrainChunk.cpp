#include "TerrainChunk.h"

glm::dvec3 Planet::TerrainChunk::ChunkCenterPosition(glm::dvec3 planetPosition, double radius, glm::quat rotation)
{

	int actualDetailLevel = (int)glm::pow(2, DetailLevel);
	glm::dvec2 percent = glm::dvec2(0.5, 0.5) / (double)actualDetailLevel;
	glm::dvec3 point = LocalUp + (percent.x + (double)ChunkCoordinate.x / (double)actualDetailLevel - 0.5) * 2 * AxisA + (percent.y + (double)ChunkCoordinate.y / (double)actualDetailLevel - 0.5) * 2 * AxisB;
	double x = rotation.x * 2.0f;
	double y = rotation.y * 2.0f;
	double z = rotation.z * 2.0f;
	double xx = rotation.x * x;
	double yy = rotation.y * y;
	double zz = rotation.z * z;
	double xy = rotation.x * y;
	double xz = rotation.x * z;
	double yz = rotation.y * z;
	double wx = rotation.w * x;
	double wy = rotation.w * y;
	double wz = rotation.w * z;

	glm::dvec3 res;
	res.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	res.y = (xy + wz) * point.x + (1.0f - (xx + zz)) * point.y + (yz - wx) * point.z;
	res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;
	res = glm::normalize(res);
	glm::dvec3 ret = res * radius + planetPosition;
	return ret;

}

Planet::TerrainChunk::TerrainChunk(std::shared_ptr<TerrainChunk> parent, unsigned index, unsigned detailLevel, glm::ivec2 chunkCoordinate, ChunkDirection direction, glm::dvec3 localUp)
{
	Index = index;
	TooFar = false;
	ToRecycle = false;
	_Mesh = nullptr;
	C0 = C1 = C2 = C3 = nullptr;
	ChunkCoordinate = chunkCoordinate;
	DetailLevel = detailLevel;
	Parent = parent;
	LocalUp = localUp;
	AxisA = glm::dvec3(localUp.y, localUp.z, localUp.x);
	AxisB = glm::cross(localUp, AxisA);
	LocalUp = glm::normalize(LocalUp);
}

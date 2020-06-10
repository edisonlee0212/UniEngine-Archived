#include "SurfaceOfRevolutionEnvelope.h"

SCTree::SurfaceOfRevolutionEnvelope::SurfaceOfRevolutionEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
	: Envelope(spaceOffset, spaceSize)
{
}

float SCTree::SurfaceOfRevolutionEnvelope::GetRadius(float height)
{
	if (height >= _SpaceOffset.y || height <= _SpaceOffset.y + _SpaceSize.y) {
		return glm::sin(glm::pi<float>() * glm::pow((height - _SpaceOffset.y) / _SpaceSize.y, 0.6f)) * (_SpaceSize.x + _SpaceSize.z) / 4.0f;
	}
	return 0.0f;
}

bool SCTree::SurfaceOfRevolutionEnvelope::IsInEnvelope(glm::vec3 point)
{
	float height = point.y;
	float distance = glm::sqrt(point.x * point.x + point.z * point.z);
	return GetRadius(height) > distance;
}

#include "CylinderEnvelope.h"

SpaceColonizationTree::CylinderEnvelope::CylinderEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
	: Envelope(spaceOffset, spaceSize)
{
}

bool SpaceColonizationTree::CylinderEnvelope::IsInEnvelope(glm::vec3 point)
{
	float height = point.y;
	float distance = glm::sqrt(point.x * point.x + point.z * point.z);
	float radius = _SpaceSize.x / 2.0f;
	return radius > distance;
}

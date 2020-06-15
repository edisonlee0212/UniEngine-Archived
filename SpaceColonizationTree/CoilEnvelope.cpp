#include "CoilEnvelope.h"

SpaceColonizationTree::CoilEnvelope::CoilEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
	: Envelope(spaceOffset, spaceSize)
{
}

bool SpaceColonizationTree::CoilEnvelope::IsInEnvelope(glm::vec3 point)
{
	float h = point.y;
	glm::vec2 xz = glm::vec2(point.x, point.z);
	float circleA = _SpaceSize.x / 5.0f;
	glm::vec2 center = glm::vec2(circleA * glm::sin(6.0f * 3.14159f * h / _SpaceSize.y), circleA * glm::cos(6.0f * 3.14159f * h / _SpaceSize.y));
	return glm::distance(center, xz) < circleA;
}

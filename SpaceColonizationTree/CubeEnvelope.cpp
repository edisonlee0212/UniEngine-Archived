#include "CubeEnvelope.h"

SpaceColonizationTree::CubeEnvelope::CubeEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
	:Envelope(spaceOffset, spaceSize)
{
}

bool SpaceColonizationTree::CubeEnvelope::IsInEnvelope(glm::vec3 point)
{
	return true;
}


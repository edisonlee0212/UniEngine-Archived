#include "CubeEnvelope.h"

SCTree::CubeEnvelope::CubeEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
	:Envelope(spaceOffset, spaceSize)
{
}

bool SCTree::CubeEnvelope::IsInEnvelope(glm::vec3 point)
{
	return true;
}


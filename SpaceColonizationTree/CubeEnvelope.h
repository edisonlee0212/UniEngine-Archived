#pragma once
#include "Envelope.h"
namespace SpaceColonizationTree {
	class CubeEnvelope :
		public Envelope
	{
		
	public:
		CubeEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
		bool IsInEnvelope(glm::vec3 point);
	};
}
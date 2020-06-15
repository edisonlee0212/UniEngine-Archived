#pragma once
#include "Envelope.h"
#include "Misc.h"
namespace SpaceColonizationTree {
	class CylinderEnvelope :
		public Envelope
	{
	public:
		CylinderEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
		bool IsInEnvelope(glm::vec3 point);
	};

}
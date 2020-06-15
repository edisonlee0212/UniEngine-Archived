#pragma once
#include "Envelope.h"
namespace SpaceColonizationTree {
	class SurfaceOfRevolutionEnvelope :
		public Envelope
	{
	public:
		SurfaceOfRevolutionEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
		float GetRadius(float height);
		bool IsInEnvelope(glm::vec3 point);
	};

}
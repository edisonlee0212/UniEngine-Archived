#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace Planet {
	class TerrainConstructionStageBase
	{
	public:
		virtual ~TerrainConstructionStageBase() = default;
		virtual void Process(glm::dvec3 point, double previousResult, double& elevation) = 0;
	};
}

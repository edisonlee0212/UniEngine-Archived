#pragma once
#include "UniEngine.h"
#include "TerrainConstructionStageBase.h"
using namespace UniEngine;
namespace Planet {
    class PerlinNoiseStage :
        public TerrainConstructionStageBase
    {
    public:
    	void Process(glm::dvec3 point, double previousResult, double& elevation) override;
    };

}
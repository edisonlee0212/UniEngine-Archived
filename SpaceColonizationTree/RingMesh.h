#pragma once
#include "UniEngine.h"
#include "UniEngine.h"
using namespace UniEngine;
namespace SpaceColonizationTree {
	struct RingMesh
	{
		glm::vec3 StartPosition, EndPosition;
		glm::vec3 StartAxis, EndAxis;
		float StartRadius, EndRadius;
		RingMesh(glm::vec3 startPosition, glm::vec3 endPosition, glm::vec3 startAxis, glm::vec3 endAxis, float startRadius, float endRadius);
		void AppendPoints(std::vector<Vertex>* vertices, int resolution = 9);
		inline glm::vec3 GetPoint(float angle, bool isStart);
	};

}
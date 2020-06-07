#pragma once
#include "Misc.h"
namespace SCTree {
	class Envelope
	{
	protected:
		glm::vec3 _SpaceOffset;
		glm::vec3 _SpaceSize;
		std::vector<glm::vec3> _PointPositions;
		std::vector<glm::mat4> _PointMatrices;
		bool _PointsGenerated;
		Envelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
		
	public:
		~Envelope();
		virtual bool IsInEnvelope(glm::vec3 point) = 0;
		void GeneratePoints(size_t amount);
		void AddPoint(glm::vec3 point, glm::vec3 scale = glm::vec3(0.01f));
		void RemovePointSwapBack(int index);
		void Clear();
		bool PointsGenerated();
		std::vector<glm::vec3>* PointPositions();
	};
}


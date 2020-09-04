#pragma once
#include "TreeUtilitiesAPI.h"
#include "Curve.h"
namespace TreeUtilities {
	class TREEUTILITIES_API BezierCurve :
		public Curve
	{
	public:
		BezierCurve(glm::vec3 cp0, glm::vec3 cp1, glm::vec3 cp2, glm::vec3 cp3);
		glm::vec3 GetPoint(float t);
	private:
		glm::vec3 _CP0, _CP1, _CP2, _CP3;
		std::vector<glm::vec3> _Points;
	};
}

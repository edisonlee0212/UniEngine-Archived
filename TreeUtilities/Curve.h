#pragma once
#include "TreeUtilitiesAPI.h"
namespace TreeUtilities {
	class TREEUTILITIES_API Curve
	{
	public:
		virtual glm::vec3 GetPoint(float t) = 0;
		void GetUniformCurve(size_t pointAmount, std::vector<glm::vec3>& points);
	private:
	};
}

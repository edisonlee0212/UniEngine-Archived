#include "pch.h"
#include "BezierCurve.h"
using namespace TreeUtilities;
TreeUtilities::BezierCurve::BezierCurve(glm::vec3 cp0, glm::vec3 cp1, glm::vec3 cp2, glm::vec3 cp3)
	: Curve(),
	_CP0(cp0),
	_CP1(cp1),
	_CP2(cp2),
	_CP3(cp3)
{
}

glm::vec3 TreeUtilities::BezierCurve::GetPoint(float t)
{
	float b0, b1, b2, b3;
	b0 = (1.0f - t) * (1.0f - t) * (1.0f - t);
	b1 = 3.0f * t * (1.0f - t) * (1.0f - t);
	b2 = 3.0f * t * t * (1.0f - t);
	b3 = t * t * t;
	return glm::vec3(
		(_CP0.x * b0 + _CP1.x * b1 + _CP2.x * b2 + _CP3.x * b3),
		(_CP0.y * b0 + _CP1.y * b1 + _CP2.y * b2 + _CP3.y * b3),
		(_CP0.z * b0 + _CP1.z * b1 + _CP2.z * b2 + _CP3.z * b3));
}

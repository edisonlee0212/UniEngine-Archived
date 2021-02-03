#pragma once
#include "Core.h"
#include "UniEngineAPI.h"

namespace UniEngine
{
	struct UNIENGINE_API BezierCubic2D : ComponentBase
	{
		bool Fixed = true;
		glm::vec2 ControlPoints[4];
		BezierCubic2D();
		glm::vec2 GetPoint(const float& t) const;
		bool Graph(const std::string& label);
	};
}

#pragma once
#include "Core.h"
#include "UniEngineAPI.h"

namespace UniEngine
{
	struct UNIENGINE_API BezierCubic2D : ComponentDataBase
	{
		bool m_fixed = true;
		glm::vec2 m_controlPoints[4];
		BezierCubic2D();
		glm::vec2 GetPoint(const float& t) const;
		bool Graph(const std::string& label);
	};
}

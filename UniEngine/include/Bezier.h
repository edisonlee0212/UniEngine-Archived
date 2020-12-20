#pragma once
#include "Core.h"
#include "UniEngineAPI.h"

namespace UniEngine
{
	struct Bezier2D : ComponentBase
	{
		float ControlPoints[4] = {0, 0, 1, 1};
		float Preset = 0;

		Bezier2D(){}
		Bezier2D(float p0, float p1, float p2, float p3);
        template<int steps>
        void BezierTable(ImVec2 P[4], ImVec2 results[steps + 1]) const;
		int Graph(const char* label);
	};

	template <int steps>
	void Bezier2D::BezierTable(ImVec2 P[4], ImVec2 results[steps + 1]) const
	{
		static float C[(steps + 1) * 4], *K = 0;
		if (!K)
		{
			K = C;
			for (unsigned step = 0; step <= steps; ++step)
			{
				float t = (float)step / (float)steps;
				C[step * 4 + 0] = (1 - t) * (1 - t) * (1 - t); // * P0
				C[step * 4 + 1] = 3 * (1 - t) * (1 - t) * t; // * P1
				C[step * 4 + 2] = 3 * (1 - t) * t * t; // * P2
				C[step * 4 + 3] = t * t * t; // * P3
			}
		}
		for (unsigned step = 0; step <= steps; ++step)
		{
			ImVec2 point = {
				K[step * 4 + 0] * P[0].x + K[step * 4 + 1] * P[1].x + K[step * 4 + 2] * P[2].x + K[step * 4 + 3] * P[3].
				x,
				K[step * 4 + 0] * P[0].y + K[step * 4 + 1] * P[1].y + K[step * 4 + 2] * P[2].y + K[step * 4 + 3] * P[3].
				y
			};
			results[step] = point;
		}
	}
}

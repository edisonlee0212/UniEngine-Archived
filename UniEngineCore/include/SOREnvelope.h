#pragma once
#include "Envelope.h"
namespace SCTree {
	class SOREnvelope :
		public Envelope
	{
		float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;
	public:
		SOREnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin);
		float GetRadius(float height);
		bool IsInEnvelope(glm::vec3 point);
		void GeneratePoints(int amount);
	};
}

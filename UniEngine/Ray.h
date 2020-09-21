#pragma once
#include "UniEngineAPI.h"
namespace UniEngine
{
	struct UNIENGINE_API Ray : ComponentBase {
		glm::vec3 Start;
		glm::vec3 Direction;
		float Length;
		Ray(glm::vec3 start, glm::vec3 end);
		Ray(glm::vec3 start, glm::vec3 direction, float length);
		bool Intersect(glm::vec3 position, float radius) const;
		glm::vec3 GetEnd() const;
	};

	inline Ray::Ray(glm::vec3 start, glm::vec3 end)
	{
		Start = start;
		Direction = glm::normalize(end - start);
		Length = glm::distance(start, end);
	}

	inline Ray::Ray(glm::vec3 start, glm::vec3 direction, float length)
	{
		Start = start;
		Direction = direction;
		Length = length;
	}

	inline bool Ray::Intersect(glm::vec3 position, float radius) const
	{
		const glm::vec3 rayEnd = Start + Direction * Length;
		auto cp = glm::closestPointOnLine(position, Start, rayEnd);
		if (cp == Start || cp == rayEnd) return false;
		return glm::distance(cp, position) <= radius;
	}

	inline glm::vec3 Ray::GetEnd() const
	{
		return Start + Direction * Length;
	}
}

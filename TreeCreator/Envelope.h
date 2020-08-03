#pragma once
#include "UniEngine.h"
using namespace UniEngine;
class Envelope {
	glm::vec3 _SpaceOffset;
	glm::vec3 _SpaceSize;
public:
	Envelope(glm::vec3 spaceOffset, glm::vec3 spaceSize) {
		_SpaceOffset = spaceOffset;
		_SpaceSize = spaceSize;
	}
	float GetRadius(float height)
	{
		if (height >= _SpaceOffset.y || height <= _SpaceOffset.y + _SpaceSize.y) {
			return glm::sin(glm::pi<float>() * glm::pow((height - _SpaceOffset.y) / _SpaceSize.y, 0.6f)) * (_SpaceSize.x + _SpaceSize.z) / 4.0f;
		}
		return 0.0f;
	}
	bool IsInEnvelope(glm::vec3 point) {
		float height = point.y;
		float distance = glm::sqrt(point.x * point.x + point.z * point.z);
		return GetRadius(height) > distance;
	}
	glm::vec3 GetPoint() {
		glm::vec3 point = glm::vec3(0.0f);
		bool succeed = true;
		while (succeed) {
			point = _SpaceOffset + glm::vec3(_SpaceSize.x * (float)rand() / (RAND_MAX),
				_SpaceSize.y * (float)rand() / (RAND_MAX),
				_SpaceSize.z * (float)rand() / (RAND_MAX));
			succeed = !IsInEnvelope(point);
		}
		return point;
	}
};
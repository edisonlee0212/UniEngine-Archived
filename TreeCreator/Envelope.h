#pragma once
#include "UniEngine.h"
using namespace UniEngine;
enum class EnvelopeType {
	Default,
	Box,
	Cylinder,
	Coil
};
class Envelope {
	friend class SpaceColonizationTreeSystem;
	EnvelopeType _Type;
	glm::vec3 _SpaceCenter;
	glm::vec3 _SpaceSize;
	float GetRadius(float height)
	{
		if (height >= _SpaceCenter.y || height <= _SpaceCenter.y + _SpaceSize.y) {
			return glm::sin(glm::pi<float>() * glm::pow((height - _SpaceCenter.y) / _SpaceSize.y, 0.6f)) * (_SpaceSize.x + _SpaceSize.z) / 4.0f;
		}
		return 0.0f;
	}
	bool IsInEnvelope(glm::vec3 point) {
		switch (_Type)
		{
		case EnvelopeType::Default:
			return GetRadius(point.y) > glm::sqrt(point.x * point.x + point.z * point.z);
		case EnvelopeType::Box:
			return true;
		case EnvelopeType::Cylinder:
			return _SpaceSize.x / 2.0f > glm::sqrt(point.x * point.x + point.z * point.z);
		case EnvelopeType::Coil:
			float circleA = _SpaceSize.x / 5.0f;
			glm::vec2 center = glm::vec2(circleA * glm::sin(6.0f * 3.14159f * point.y / _SpaceSize.y), circleA * glm::cos(6.0f * 3.14159f * point.y / _SpaceSize.y));
			return glm::distance(center, glm::vec2(point.x, point.z)) < circleA;
		}
		return false;
	}
public:
	Envelope() {
		_Type = EnvelopeType::Default;
		_SpaceCenter = glm::vec3(0);
		_SpaceSize = glm::vec3(0);
	}
	Envelope(glm::vec3 spaceOffset, glm::vec3 spaceSize) {
		_Type = EnvelopeType::Default;
		_SpaceCenter = spaceOffset;
		_SpaceSize = spaceSize;
	}
	glm::vec3 GetPoint() {
		glm::vec3 point = glm::vec3(0.0f);
		bool succeed = true;
		while (succeed) {
			point = _SpaceCenter + glm::vec3(_SpaceSize.x * (((float)rand() / RAND_MAX) - 0.5f),
				_SpaceSize.y * (((float)rand() / RAND_MAX) - 0.5f),
				_SpaceSize.z * (((float)rand() / RAND_MAX) - 0.5f));
			succeed = !IsInEnvelope(point);
		}
		return point;
	}
	void Reset(glm::vec3 spaceOffset, glm::vec3 spaceSize) {
		_SpaceCenter = spaceOffset;
		_SpaceSize = spaceSize;
	}
	void ResetType(EnvelopeType value) {
		_Type = value;
	}
};
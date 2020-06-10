#pragma once
#include "Math.h"
#include "Misc.h"
namespace UniEngine {
	struct FixedData {

	};
	struct Position : FixedData {
		glm::vec3 value;
	};
	struct Scale : FixedData {
		glm::vec3 value;
	};
	struct Rotation : FixedData {
		glm::vec4 value;
	};
	struct LocalPosition : FixedData
	{
		glm::vec3 value;
	};
	struct LocalScale : FixedData {
		glm::vec3 value;
	};
	struct LocalRotation : FixedData {
		glm::vec4 value;
	};
	struct LocalToWorld : FixedData {
		glm::mat4 value;
	};
	struct LocalToParent : FixedData {
		glm::mat4 value;
	};
	struct CameraMask : FixedData
	{
		unsigned value;
		CameraMask() { value = 0; }
	};

}
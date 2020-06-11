#pragma once
#include "Misc.h"
namespace UniEngine {
	struct UECORE_API FixedData {

	};
	struct UECORE_API Position : FixedData {
		glm::vec3 value;
	};
	struct UECORE_API Scale : FixedData {
		glm::vec3 value;
	};
	struct UECORE_API Rotation : FixedData {
		glm::vec4 value;
	};
	struct UECORE_API LocalPosition : FixedData
	{
		glm::vec3 value;
	};
	struct UECORE_API LocalScale : FixedData {
		glm::vec3 value;
	};
	struct UECORE_API LocalRotation : FixedData {
		glm::vec4 value;
	};
	struct UECORE_API LocalToWorld : FixedData {
		glm::mat4 value;
	};
	struct UECORE_API LocalToParent : FixedData {
		glm::mat4 value;
	};
	struct UECORE_API CameraMask : FixedData
	{
		unsigned value;
		CameraMask() { value = 0; }
	};

}
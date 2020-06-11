#pragma once
#include "Core.h"
#include "SharedComponentBase.h"
namespace UniEngine {
	struct UECORE_API SpotLight
	{
		glm::vec4 position;
		glm::vec4 direction;
		float cutOff;
		float outerCutOff;

		float constant;
		float linear;
		float quadratic;

		glm::vec4 diffuse;
		glm::vec4 specular;
	};
	class UECORE_API SpotLightComponent :
		public SharedComponentBase
	{
	public:
		SpotLight value;
		size_t GetHashCode();
	};
}

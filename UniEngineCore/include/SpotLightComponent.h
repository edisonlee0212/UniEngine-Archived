#pragma once
#include "SharedComponentBase.h"
namespace UniEngine {
	struct SpotLight
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
	class SpotLightComponent :
		public SharedComponentBase
	{
	public:
		SpotLight value;
		size_t GetHashCode();
	};
}

#pragma once
#include "Core.h"
namespace UniEngine {
	class SpotLight :
		public SharedComponentBase
	{
		float cutOff;
		float outerCutOff;

		float constant;
		float linear;
		float quadratic;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};
}

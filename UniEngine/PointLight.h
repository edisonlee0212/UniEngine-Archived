#pragma once
#include "Core.h"
namespace UniEngine {
	class PointLight :
		public SharedComponentBase
	{
		float constant;
		float linear;
		float quadratic;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};
}
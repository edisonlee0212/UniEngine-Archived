#pragma once
#include "SharedComponentBase.h"
namespace UniEngine {
	struct PointLight
	{
		glm::vec4 position;

		float constant;
		float linear;
		float quadratic;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};

	class PointLightComponent :
		public SharedComponentBase
	{
	public:
		PointLight value;
		size_t GetHashCode();
	};
}

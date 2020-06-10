#pragma once
#include "SharedComponentBase.h"
namespace UniEngine {
	struct PointLight
	{
		glm::vec4 position;
		glm::vec4 constantLinearQuadFarPlane;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};

	class PointLightComponent :
		public SharedComponentBase
	{
	public:
		float constant;
		float linear;
		float quadratic;
		float farPlane;
		glm::vec3 diffuse;
		glm::vec3 specular;
		size_t GetHashCode();
	};
}

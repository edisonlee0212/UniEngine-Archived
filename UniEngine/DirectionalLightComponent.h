#pragma once
#include "Core.h"
#include "SharedComponentBase.h"
namespace UniEngine {
	struct UECORE_API DirectionalLight
	{
		glm::vec4 position;
		glm::vec4 direction;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::mat4 lightSpaceMatrix;
	};
	class UECORE_API DirectionalLightComponent :
		public SharedComponentBase
	{
	public:
		glm::vec3 diffuse;
		glm::vec3 specular;
		size_t GetHashCode();
	};

}
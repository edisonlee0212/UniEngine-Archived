#pragma once
#include "SharedComponentBase.h"
namespace UniEngine {
	struct DirectionalLight
	{
		glm::vec4 direction;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};
	class DirectionalLightComponent :
		public SharedComponentBase
	{
	public:
		DirectionalLight value;
		size_t GetHashCode();
	};

}
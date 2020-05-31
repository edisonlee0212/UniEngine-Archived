#pragma once
#include "Core.h"
namespace UniEngine {
	class DirectionalLight :
		public SharedComponentBase
	{
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};

}
#pragma once
#include "Core.h"
namespace UniEngine {
	class UECORE_API  TransformSystem :
		public SystemBase
	{
		void CalculateTransform(Entity* parent);
		glm::mat4 TRS(glm::vec3 translation, glm::vec4 rotation, glm::vec3 scale);
	public:
		TransformSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

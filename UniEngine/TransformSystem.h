#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API TransformSystem :
		public SystemBase
	{
		void CalculateTransform(Entity parent);
		glm::mat4 TRS(glm::vec3 translation, glm::quat rotation, glm::vec3 scale);
	public:

		TransformSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};

}
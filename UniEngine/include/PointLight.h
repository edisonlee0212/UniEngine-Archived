#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API PointLightInfo
	{
		glm::vec4 position;
		glm::vec4 constantLinearQuadFarPlane;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::mat4 lightSpaceMatrix[6];
		glm::vec4 ReservedParameters;
		glm::ivec4 viewPort;
	};

	class UNIENGINE_API PointLight :
		public PrivateComponentBase
	{
	public:
		bool CastShadow = true;
		float constant = 1.0f;
		float linear = 0.07f;
		float quadratic = 0.0015f;
		float farPlane = 200.0f;
		float bias = 0.05f;
		glm::vec3 diffuse = glm::vec3(1.0f);
		float diffuseBrightness = 0.8f;
		float lightSize = 0.1f;
		void OnGui() override;
		void Init() override;
	};

	
	
}

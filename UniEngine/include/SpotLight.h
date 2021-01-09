#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API SpotLightInfo
	{
		glm::vec4 position;
		glm::vec4 direction;
		glm::mat4 lightSpaceMatrix;
		glm::vec4 cutOffOuterCutOffLightSizeBias;
		glm::vec4 constantLinearQuadFarPlane;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::ivec4 viewPort;
	};
	class UNIENGINE_API SpotLight :
		public PrivateComponentBase
	{
	public:
		bool CastShadow = true;
		float innerDegrees = 20;
		float outerDegrees = 30;
		float constant = 1.0f;
		float linear = 0.07f;
		float quadratic = 0.0015f;
		float bias = 0.001f;
		float farPlane = 200.0f;
		glm::vec3 diffuse = glm::vec3(1.0f);
		float diffuseBrightness = 0.8f;
		glm::vec3 specular = glm::vec3(1.0f);
		float specularBrightness = 0.2f;
		float lightSize = 0.1f;
		void OnGui() override;
	};

}

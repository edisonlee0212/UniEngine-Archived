#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API DirectionalLightInfo
	{
		glm::vec4 direction;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::mat4 lightSpaceMatrix[4];
		glm::vec4 lightFrustumWidth;
		glm::vec4 lightFrustumDistance;
		glm::vec4 ReservedParameters;
		glm::ivec4 viewPort;
	};
	class UNIENGINE_API DirectionalLight :
		public PrivateComponentBase
	{
	public:
		bool CastShadow = true;
		glm::vec3 diffuse = glm::vec3(1.0f);
		float diffuseBrightness = 0.8f;
		float bias = 0.1f;
		float normalOffset = 0.001f;
		float lightSize = 0.01f;
		void Init() override;
		void OnGui() override;
	};

	
}
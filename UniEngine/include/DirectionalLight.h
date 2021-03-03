#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API DirectionalLightInfo
	{
		glm::vec4 m_direction;
		glm::vec4 m_diffuse;
		glm::vec4 m_specular;
		glm::mat4 m_lightSpaceMatrix[4];
		glm::vec4 m_lightFrustumWidth;
		glm::vec4 m_lightFrustumDistance;
		glm::vec4 m_reservedParameters;
		glm::ivec4 m_viewPort;
	};
	class UNIENGINE_API DirectionalLight :
		public PrivateComponentBase
	{
	public:
		bool m_castShadow = true;
		glm::vec3 m_diffuse = glm::vec3(1.0f);
		float m_diffuseBrightness = 0.8f;
		float m_bias = 0.1f;
		float m_normalOffset = 0.001f;
		float m_lightSize = 0.01f;
		void Init() override;
		void OnGui() override;
	};

	
}
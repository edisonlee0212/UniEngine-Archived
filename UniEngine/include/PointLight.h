#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API PointLightInfo
	{
		glm::vec4 m_position;
		glm::vec4 m_constantLinearQuadFarPlane;
		glm::vec4 m_diffuse;
		glm::vec4 m_specular;
		glm::mat4 m_lightSpaceMatrix[6];
		glm::vec4 m_reservedParameters;
		glm::ivec4 m_viewPort;
	};

	class UNIENGINE_API PointLight :
		public PrivateComponentBase
	{
	public:
		bool m_castShadow = true;
		float m_constant = 1.0f;
		float m_linear = 0.07f;
		float m_quadratic = 0.0015f;
		float m_farPlane = 200.0f;
		float m_bias = 0.05f;
		glm::vec3 m_diffuse = glm::vec3(1.0f);
		float m_diffuseBrightness = 0.8f;
		float m_lightSize = 0.1f;
		void OnGui() override;
		void Init() override;
	};

	
	
}

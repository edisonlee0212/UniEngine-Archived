#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API SpotLightInfo
	{
		glm::vec4 m_position;
		glm::vec4 m_direction;
		glm::mat4 m_lightSpaceMatrix;
		glm::vec4 m_cutOffOuterCutOffLightSizeBias;
		glm::vec4 m_constantLinearQuadFarPlane;
		glm::vec4 m_diffuse;
		glm::vec4 m_specular;
		glm::ivec4 m_viewPort;
	};
	class UNIENGINE_API SpotLight :
		public PrivateComponentBase
	{
	public:
		bool m_castShadow = true;
		float m_innerDegrees = 20;
		float m_outerDegrees = 30;
		float m_constant = 1.0f;
		float m_linear = 0.07f;
		float m_quadratic = 0.0015f;
		float m_bias = 0.001f;
		float m_farPlane = 200.0f;
		glm::vec3 m_diffuse = glm::vec3(1.0f);
		float m_diffuseBrightness = 0.8f;
		float m_lightSize = 0.1f;
		void OnGui() override;
		void Init() override;
	};

}

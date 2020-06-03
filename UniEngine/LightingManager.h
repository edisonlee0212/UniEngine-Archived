#pragma once
#include "ManagerBase.h"
#include "Core.h"
#include "RenderManager.h"

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"
#include "DirectionalShadowMap.h"
#include "PointShadowMap.h"

namespace UniEngine {
	class LightingManager :
		public ManagerBase
	{
		static GLUBO* _DirectionalLightBlock;
		static GLUBO* _PointLightBlock;
		static GLUBO* _SpotLightBlock;

		static std::vector<DirectionalLight> _DirectionalLights;
		static std::vector<PointLight> _PointLights;
		static std::vector<SpotLight> _SpotLights;

		static bool _UpdateDirectionalLightBlock;
		static bool _UpdatePointLightBlock;
		static bool _UpdateSpotLightBlock;

		static GLProgram* _DirectionalLightProgram;
		static GLProgram* _PointLightProgram;
		friend class RenderManager;
		static DirectionalShadowMap* _DirectionalLightShadowMap;
		static PointShadowMap* _PointLightShadowMap;
		static glm::mat4 _DirLightSpaceMatrix;
		static glm::vec3 _DirLightPos;
		static glm::vec3 _DirLightDir;

		
		static float _PointLightFarPlane;
		static glm::vec3 _PointLightPos;

	public:
		static void Init();
		static void Start();
	};
}

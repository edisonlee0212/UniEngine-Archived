#pragma once
#include "UniEngineAPI.h"

#include "RenderManager.h"

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"
#include "DirectionalLightShadowMap.h"
#include "PointLightShadowMap.h"
#include "Default.h"
namespace UniEngine {

	struct UNIENGINE_API ShadowCascadeInfo {
		float SplitDistance[4];
	};

	class UNIENGINE_API LightingManager :
		public ManagerBase
	{
		static CameraComponent* _TargetMainCamera;
		static Entity _TargetMainCameraEntity;
		static GLUBO* _DirectionalLightBlock;
		static GLUBO* _PointLightBlock;
		static GLUBO* _SpotLightBlock;
		
		static float _ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount];
		static unsigned _DirectionalShadowMapResolution;
		static GLUBO* _ShadowCascadeInfoBlock;
		static ShadowCascadeInfo _ShadowCascadeInfo;

		static DirectionalLight _DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
		static PointLight _PointLights[Default::ShaderIncludes::MaxPointLightAmount];
		static SpotLight _SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

		static bool _UpdateDirectionalLightBlock;
		static bool _UpdatePointLightBlock;
		static bool _UpdateSpotLightBlock;

		static GLProgram* _DirectionalLightProgram;
		static GLProgram* _PointLightProgram;
		static GLProgram* _DirectionalLightInstancedProgram;
		static GLProgram* _PointLightInstancedProgram;
		
		friend class RenderManager;
		static DirectionalLightShadowMap* _DirectionalLightShadowMap;
		static PointLightShadowMap* _PointLightShadowMap;

	public:
		static void Init();
		static void Start();

		static void SetDirectionalLightResolution(float value);

		static glm::vec3 ClosestPointOnLine(glm::vec3 point, glm::vec3 a, glm::vec3 b);

		static void SetMainCamera(Entity entity);
	};
}

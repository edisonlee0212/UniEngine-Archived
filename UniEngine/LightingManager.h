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

	enum class UNIENGINE_API ShadowMode {
		PCF,
		VSM,
		ESM,
		PCSS,
		HARD
	};

	struct UNIENGINE_API ShadowSettings {
		float SplitDistance[4];
		int SoftShadowMode = (int)ShadowMode::PCSS;
		float PCSSScaleFactor = 0.0f;
		float DisplaySplit = 0.0f;
		float SeamFixRatio = 0.05f;
		float VSMMaxVariance = 0.001f;
		float LightBleedFactor = 0.5f;
		float EVSMExponent = 40.0f;
		float AmbientLight = 0.1f;
	};

	class UNIENGINE_API LightingManager :
		public ManagerBase
	{
		static GLUBO* _DirectionalLightBlock;
		static GLUBO* _PointLightBlock;
		static GLUBO* _SpotLightBlock;
		
		static float _ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount];
		static size_t _DirectionalShadowMapResolution;
		static GLUBO* _ShadowCascadeInfoBlock;
		static ShadowSettings _ShadowSettings;

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
		static RenderTarget* _DirectionalLightShadowMapFilter;
		static PointLightShadowMap* _PointLightShadowMap;
		static GLProgram* _DirectionalLightVFilterProgram;
		static GLProgram* _DirectionalLightHFilterProgram;


		static GLTexture* _DLVSMVFilter;
		static bool _StableFit;
		static float _MaxShadowDistance;
	public:
		static void Init();
		static void Start();
		static void SetSplitRatio(float r1, float r2, float r3, float r4);
		static void SetDirectionalLightResolution(size_t value);
		static void SetShadowMode(ShadowMode value);
		static void SetEnableSplitDisplay(bool value);
		static void SetStableFit(bool value);
		static void SetSeamFixRatio(float value);
		static void SetMaxShadowDistance(float value);
		static void SetPCSSScaleFactor(float value);
		static void SetVSMMaxVariance(float value);
		static void SetLightBleedControlFactor(float value);
		static void SetEVSMExponent(float value);
		static void SetAmbientLight(float value);
		static glm::vec3 ClosestPointOnLine(glm::vec3 point, glm::vec3 a, glm::vec3 b);
	};
}

#pragma once
#include "ManagerBase.h"
#include "Core.h"

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"
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

	public:
		static void Init();
		static void Start();
	};
}

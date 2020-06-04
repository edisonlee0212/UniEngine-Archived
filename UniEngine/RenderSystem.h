#pragma once
#include "Core.h"
#include "RenderManager.h"
#include "MeshMaterialComponent.h"

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"
namespace UniEngine {

	class RenderSystem : public SystemBase
	{
		void RenderToCamera(Camera* camera);
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

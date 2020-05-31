#pragma once
#include "Core.h"
#include "RenderManager.h"
#include "MeshMaterialComponent.h"
namespace UniEngine {
	class RenderSystem : public SystemBase
	{
		void RenderToCamera(Camera* camera);
		void DrawEntity(Entity* entity, Camera* camera);
		void DrawEntity(Entity* entity, Camera* camera, MeshMaterialComponent* meshMaterialComponent);
	public:
		RenderSystem();
		void OnCreate();
		void OnDestroy();
		void Update();
	};
}

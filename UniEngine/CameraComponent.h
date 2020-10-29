#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Camera.h"
#include "Cubemap.h"

namespace UniEngine {
	class UNIENGINE_API CameraComponent :
		public PrivateComponentBase
	{
	public:
		bool DrawSkyBox = true;
		glm::vec3 ClearColor;
		std::shared_ptr<Cubemap> SkyBox;
		std::shared_ptr<Camera> Value;
		void OnGui() override;
	};

}

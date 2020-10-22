#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Camera.h"
#include "Cubemap.h"

namespace UniEngine {
	class UNIENGINE_API CameraComponent :
		public SharedComponentBase
	{	
	public:
		bool DrawSkyBox = true;
		std::shared_ptr<Cubemap> SkyBox;
		std::shared_ptr<Camera> Value;
		std::size_t GetHashCode() override;
		void OnGui() override;
	};

}

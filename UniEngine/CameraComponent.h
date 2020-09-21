#pragma once
#include "UniEngineAPI.h"
#include "Camera.h"
namespace UniEngine {
	class UNIENGINE_API CameraComponent :
		public SharedComponentBase
	{	
	public:
		std::shared_ptr<Camera> Value;
		std::size_t GetHashCode();
	};

}
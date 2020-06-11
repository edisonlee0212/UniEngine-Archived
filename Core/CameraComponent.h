#pragma once
#include "Core.h"
#include "SharedComponentBase.h"
#include "Camera.h"
namespace UniEngine {
	class UECORE_API CameraComponent :
		public SharedComponentBase
	{	
	public:
		Camera* Value;
		std::size_t GetHashCode();
	};

}
#pragma once
#include "SharedComponentBase.h"
#include "RenderManager.h"
namespace UniEngine {
	class CameraComponent :
		public SharedComponentBase
	{	
	public:
		Camera* Value;
		std::size_t GetHashCode();
	};

}
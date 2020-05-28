#pragma once
#include "SharedComponentBase.h"
#include "RenderManager.h"
namespace UniEngine {
	class MaterialComponent :
		public SharedComponentBase
	{	
	public:
		Material* Value;
		std::size_t GetHashCode();
	};

}
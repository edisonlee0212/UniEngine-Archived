#pragma once
#include "SharedComponentBase.h"
#include "RenderManager.h"
namespace UniEngine {
	class MeshComponent :
		public SharedComponentBase
	{
	public:
		Mesh* Value;
		std::size_t GetHashCode();
	};
}

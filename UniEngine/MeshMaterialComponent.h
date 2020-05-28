#pragma once
#include "SharedComponentBase.h"
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class MeshMaterialComponent :
		public SharedComponentBase
	{
	public:
		Mesh* _Mesh;
		Material* _Material;
		size_t GetHashCode();
	};
}


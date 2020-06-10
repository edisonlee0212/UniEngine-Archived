#pragma once
#include "SharedComponentBase.h"
#include "Mesh.h"
#include "Material.h"
#include "Core.h"
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


#pragma once
#include "UniEngineAPI.h"
#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class UNIENGINE_API MeshMaterialComponent :
		public SharedComponentBase
	{
	public:
		Mesh* _Mesh;
		Material* _Material;
		size_t GetHashCode();
	};
}


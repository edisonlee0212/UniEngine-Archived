#pragma once
#include "UniEngineAPI.h"
#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class UNIENGINE_API InstancedMeshMaterialComponent :
		public SharedComponentBase
	{
	public:
		std::vector<glm::mat4>* _Matrices;
		Mesh* _Mesh;
		Material* _Material;
		size_t GetHashCode();
	};
}

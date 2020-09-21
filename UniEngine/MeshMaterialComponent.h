#pragma once
#include "UniEngineAPI.h"
#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class UNIENGINE_API MeshMaterialComponent :
		public SharedComponentBase
	{
	public:
		bool CastShadow = true;
		bool ReceiveShadow = true;
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Material> Material;
		size_t GetHashCode();
	};
}


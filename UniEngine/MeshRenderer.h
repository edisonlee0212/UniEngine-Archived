#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class UNIENGINE_API MeshRenderer :
		public SharedComponentBase
	{
	public:
		bool ForwardRendering = false;
		bool CastShadow = true;
		bool ReceiveShadow = true;
		bool BackCulling = true;
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Material> Material;
		size_t GetHashCode() override;
		void OnGui() override;
	};
}


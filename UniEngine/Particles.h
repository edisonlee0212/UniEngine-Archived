#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class UNIENGINE_API Particles :
		public PrivateComponentBase
	{
	public:
		glm::vec4 DisplayBoundColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
		bool DisplayBound = true;
		Particles();
		Bound BoundingBox;
		bool ForwardRendering = false;
		bool CastShadow = true;
		bool ReceiveShadow = true;
		std::vector<glm::mat4> Matrices;
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Material> Material;
		void RecalculateBoundingBox();
		void OnGui() override;
	};
}

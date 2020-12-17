#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "MeshRenderer.h"
namespace UniEngine {
	struct ModelNode {
		glm::mat4 _LocalToParent;
		std::vector<std::pair<std::shared_ptr<Material>, std::shared_ptr<Mesh>>> _MeshMaterials;
		std::vector<std::unique_ptr<ModelNode>> Children;
	};
	class UNIENGINE_API Model : public ResourceBehaviour
	{
		std::unique_ptr<ModelNode> _RootNode;
	public:
		Model();
		std::unique_ptr<ModelNode>& RootNode();
	};
}
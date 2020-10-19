#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "MeshRenderer.h"
namespace UniEngine {
	struct ModelNode {
		glm::mat4 _LocalToParent;
		std::vector<std::shared_ptr<MeshRenderer>> _MeshMaterialComponents;
		std::vector<std::unique_ptr<ModelNode>> Children;
	};
	class UNIENGINE_API Model
	{
		std::unique_ptr<ModelNode> _RootNode;
	public:
		std::string Name;
		Model();
		std::unique_ptr<ModelNode>& RootNode();
	};
}
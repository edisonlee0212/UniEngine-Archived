#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "MeshRenderer.h"
namespace UniEngine {
	struct ModelNode {
		glm::mat4 _LocalToParent;
		std::vector<std::shared_ptr<MeshRenderer>> _MeshMaterialComponents;
		ModelNode* Parent;
		std::vector<ModelNode*> Children;
		~ModelNode();
	};
	class UNIENGINE_API Model
	{
		ModelNode* _RootNode;
	public:
		std::string Name;
		Model();
		~Model();
		ModelNode* RootNode();
	};
}
#pragma once
#include "UniEngineAPI.h"
#include "MeshMaterialComponent.h"
namespace UniEngine {
	struct ModelNode {
		glm::mat4 _LocalToParent;
		std::vector<MeshMaterialComponent*> _MeshMaterialComponents;
		ModelNode* Parent;
		std::vector<ModelNode*> Children;
		~ModelNode();
	};
	class UNIENGINE_API Model
	{
		ModelNode* _RootNode;
	public:
		Model();
		~Model();
		ModelNode* RootNode();
	};
}
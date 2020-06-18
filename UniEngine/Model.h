#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	struct ModelNode {
		ModelNode* Parent;
		Entity Node;
		std::vector<ModelNode*> Children;
		~ModelNode();
	};
	class UNIENGINE_API Model
	{
		ModelNode _RootNode;
	public:
		ModelNode* RootNode();
	};
}
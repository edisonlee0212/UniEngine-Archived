#pragma once
#include "Misc.h"
#include "Core.h"
namespace UniEngine {
	class SceneNode
	{
	public:
		float4x4 _Matrix;
		SceneNode* _Parent;
		std::vector<SceneNode*> _Children;
		std::vector<unsigned> _MeshIndices;
		std::vector<unsigned> _MaterialIndices;
		SceneNode(SceneNode* parent);
		~SceneNode();
	};

}
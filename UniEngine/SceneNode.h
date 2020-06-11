#pragma once
#include "Core.h"
namespace UniEngine {
	class SceneNode
	{
	public:
		glm::mat4 _Matrix;
		SceneNode* _Parent;
		std::vector<SceneNode*> _Children;
		std::vector<unsigned> _MeshIndices;
		std::vector<unsigned> _MaterialIndices;
		SceneNode(SceneNode* parent);
		~SceneNode();
	};

}
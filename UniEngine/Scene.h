#pragma once
#include "Misc.h"
#include "Core.h"
namespace UniEngine {
	class SceneNode {
	public:
		float4x4 mTransformation;
		SceneNode* mParent;
		std::vector<SceneNode*> mChildren;
		std::vector<int> mMeshesIndices;
		std::vector<int> mMaterialIndices;
		SceneNode(SceneNode* parent);
		~SceneNode();
	};
	class Scene
	{
	public:
		std::vector<Mesh*> mMeshes;
		std::vector<Material*> mMaterials;
		std::vector<Texture2D*> mTexture2Ds;
		SceneNode* mRootNode;
		Scene();
		~Scene();
	};
}

#pragma once
#include "RenderManager.h"
#include "SceneNode.h"
#include "Core.h"
namespace UniEngine {
	class Scene
	{
	public:
		std::vector<Mesh*> _Meshes;
		std::vector<Material*> _Materials;
		std::vector<Texture2D*> _Texture2Ds;
		SceneNode* _Root;
		Scene();
		~Scene();
	};
}


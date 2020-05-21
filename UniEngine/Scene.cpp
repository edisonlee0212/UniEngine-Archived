#include "Scene.h"
using namespace UniEngine;
SceneNode::SceneNode(SceneNode* parent) : mParent(parent) {}
SceneNode::~SceneNode() {
	for (auto i : mChildren) delete i;
	mChildren.clear();
}

Scene::Scene() {
	mRootNode = new SceneNode(nullptr);
}
Scene::~Scene() {
	delete mRootNode;
	for (auto i : mMeshes) delete i;
	for (auto i : mMaterials) delete i;
	for (auto i : mTexture2Ds) delete i;
	mMeshes.clear();
	mMaterials.clear();
	mTexture2Ds.clear();
}
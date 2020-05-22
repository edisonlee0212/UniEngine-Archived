#include "Scene.h"
#include "SceneNode.h"
using namespace UniEngine;

Scene::Scene() {
	_Root = new SceneNode(nullptr);
}
Scene::~Scene() {
	delete _Root;
	_Meshes.clear();
	_Materials.clear();
	_Texture2Ds.clear();
}
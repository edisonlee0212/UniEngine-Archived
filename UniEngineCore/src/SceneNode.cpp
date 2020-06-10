#include "SceneNode.h"
using namespace UniEngine;

SceneNode::SceneNode(SceneNode* parent) : _Parent(parent) {}
SceneNode::~SceneNode() {
	for (auto i : _Children) delete i;
	_Children.clear();
}

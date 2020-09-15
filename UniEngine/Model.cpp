#include "pch.h"
#include "Model.h"
using namespace UniEngine;

Model::Model()
{
	_RootNode = new ModelNode();
}

Model::~Model()
{
	delete _RootNode;
}

ModelNode* Model::RootNode()
{
	return _RootNode;
}

ModelNode::~ModelNode()
{
	for (auto i : _MeshMaterialComponents) delete i;
	for (auto i : Children) delete i;
}

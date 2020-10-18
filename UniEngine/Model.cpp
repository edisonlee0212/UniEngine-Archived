#include "pch.h"
#include "Model.h"
using namespace UniEngine;
UniEngine::Model::Model()
{
    _RootNode = new ModelNode();
    Name = "New model";
}
UniEngine::Model::~Model()
{
    delete _RootNode;
}
ModelNode* UniEngine::Model::RootNode()
{
    return _RootNode;
}

UniEngine::ModelNode::~ModelNode()
{
    for (auto i : Children) delete i;
}

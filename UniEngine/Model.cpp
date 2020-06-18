#include "pch.h"
#include "Model.h"
using namespace UniEngine;
UniEngine::Model::Model()
{
    _RootNode = new ModelNode();
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
    EntityManager::DeleteEntity(Node);
    for (auto i : Children) delete i;
}

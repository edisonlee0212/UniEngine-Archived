#include "pch.h"
#include "Model.h"
using namespace UniEngine;
ModelNode* UniEngine::Model::RootNode()
{
    return &_RootNode;
}

UniEngine::ModelNode::~ModelNode()
{
    EntityManager::DeleteEntity(Node);
    for (auto i : Children) delete i;
}

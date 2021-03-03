#include "pch.h"
#include "Model.h"
using namespace UniEngine;
UniEngine::Model::Model()
{
    _RootNode = std::make_unique<ModelNode>();
    m_name = "New model";
}

std::unique_ptr<ModelNode>& UniEngine::Model::RootNode()
{
    return _RootNode;
}
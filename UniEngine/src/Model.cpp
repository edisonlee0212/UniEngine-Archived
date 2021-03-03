#include "pch.h"
#include "Model.h"
using namespace UniEngine;
UniEngine::Model::Model()
{
    m_rootNode = std::make_unique<ModelNode>();
    m_name = "New model";
}

std::unique_ptr<ModelNode>& UniEngine::Model::RootNode()
{
    return m_rootNode;
}
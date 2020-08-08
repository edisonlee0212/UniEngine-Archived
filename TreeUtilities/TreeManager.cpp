#include "pch.h"
#include "TreeManager.h"

TreeUtilities::TreeBudSystem* TreeUtilities::TreeManager::_TreeBudSystem;
EntityQuery TreeUtilities::TreeManager::_TreeQuery;
bool TreeUtilities::TreeManager::_Ready;
#pragma region Helpers
void TreeUtilities::TreeManager::Init()
{
    _TreeBudSystem = Application::GetWorld()->CreateSystem<TreeBudSystem>(SystemGroup::SimulationSystemGroup);
    _TreeQuery = _TreeBudSystem->GetTreeQuery();
    _Ready = true;
}

void TreeUtilities::TreeManager::GetAllTrees(std::vector<Entity>* container)
{
    if (!_Ready) {
        Debug::Error("TreeManager: Not initialized!");
        return;
    }
    return _TreeQuery.ToEntityArray(container);
}

void TreeUtilities::TreeManager::GenerateMeshForAllTrees()
{
    if (!_Ready) {
        Debug::Error("TreeManager: Not initialized!");
        return;
    }
    std::vector<Entity> trees;
    GetAllTrees(&trees);
    for (auto i : trees) {
        GenerateMeshForTree(i);
    }
}

Mesh* TreeUtilities::TreeManager::GetMeshFromTree(Entity treeEntity)
{
    if (!_Ready) {
        Debug::Error("TreeManager: Not initialized!");
        return nullptr;
    }
    return EntityManager::GetSharedComponent<MeshMaterialComponent>(treeEntity)->_Mesh;
}
#pragma endregion


void TreeUtilities::TreeManager::GenerateMeshForTree(Entity treeEntity)
{
    if (!_Ready) {
        Debug::Error("TreeManager: Not initialized!");
        return;
    }
    auto rootBud = EntityManager::GetChildren(treeEntity).at(0);
    //TODO: Finish mesh generation here.
}

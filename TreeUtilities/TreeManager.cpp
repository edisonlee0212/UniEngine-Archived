#include "pch.h"
#include "TreeManager.h"
#include "LightEstimator.h"
using namespace TreeUtilities;

LightEstimator* TreeUtilities::TreeManager::_LightEstimator;

TreeSystem* TreeUtilities::TreeManager::_TreeSystem;
BranchNodeSystem* TreeUtilities::TreeManager::_BranchNodeSystem;
BudSystem* TreeUtilities::TreeManager::_BudSystem;
LeafSystem* TreeUtilities::TreeManager::_LeafSystem;

EntityArchetype TreeUtilities::TreeManager::_BudArchetype;
EntityArchetype TreeUtilities::TreeManager::_BranchNodeArchetype;
EntityArchetype TreeUtilities::TreeManager::_LeafArchetype;
EntityArchetype TreeUtilities::TreeManager::_TreeArchetype;

EntityQuery TreeUtilities::TreeManager::_TreeQuery;
EntityQuery TreeUtilities::TreeManager::_BranchNodeQuery;
EntityQuery TreeUtilities::TreeManager::_BudQuery;
EntityQuery TreeUtilities::TreeManager::_LeafQuery;

TreeIndex TreeUtilities::TreeManager::_TreeIndex;
BranchNodeIndex TreeUtilities::TreeManager::_BranchNodeIndex;
BudIndex TreeUtilities::TreeManager::_BudIndex;
LeafIndex TreeUtilities::TreeManager::_LeafIndex;

bool TreeUtilities::TreeManager::_Ready;
#pragma region Helpers
inline void TreeUtilities::TreeManager::LeafGenerationHelper(LeafInfo info, Entity leaf, Entity bud, int index)
{
    EntityManager::SetComponentData(leaf, info);
    Translation t;
    Scale s;
    Rotation r;
    t.Value = EntityManager::GetComponentData<Translation>(bud).Value;
    s.Value = glm::vec3(0.4f);

    auto pltw = EntityManager::GetComponentData<LocalToWorld>(EntityManager::GetParent(bud));
    auto ltw = EntityManager::GetComponentData<LocalToWorld>(bud);
    glm::vec3 diff = glm::normalize(glm::vec3(ltw.Value[3]) - glm::vec3(pltw.Value[3]));
    glm::quat right = glm::quatLookAt(glm::cross(diff, glm::vec3(0, 1, 0)), diff);
    right = glm::rotate(right, glm::radians(info.CircleDegreeAddition * index), diff);
    r.Value = glm::quatLookAt(diff, glm::vec3(0, 1, 0));
    r.Value = glm::rotate(r.Value, glm::radians(info.BendDegrees), right * glm::vec3(0, 0, 1));
    EntityManager::SetComponentData(leaf, t);
    EntityManager::SetComponentData(leaf, s);
    EntityManager::SetComponentData(leaf, r);
}
void TreeUtilities::TreeManager::BranchRemover(Entity branchEntity)
{
    BranchNodeBudsList ob = EntityManager::GetComponentData<BranchNodeBudsList>(branchEntity);
    delete ob.Buds;
    EntityManager::ForEachChild(branchEntity, [](Entity child) {
        BranchRemover(child);
        });
}
void TreeUtilities::TreeManager::Init()
{
    _LeafArchetype = EntityManager::CreateEntityArchetype(
        "Leaf",
        Translation(), Rotation(), Scale(), LocalToWorld(),
        LocalPosition(), Connection(), TreeIndex(),
        LeafIndex(), LeafInfo());
    _BudArchetype = EntityManager::CreateEntityArchetype(
        "Bud",
        BranchNodeOwner(),
        Translation(), Rotation(), Scale(), LocalToWorld(),
        Activated(), LocalPosition(), Connection(),
        Radius(), BudIndex(), Iteration(), Level(), BudInfo(), TreeIndex(),
        BudIllumination());
    _BranchNodeArchetype = EntityManager::CreateEntityArchetype(
        "BranchNode",
        Translation(), Rotation(), Scale(), LocalToWorld(), Connection(),
        BranchNodeIndex(), BranchNodeInfo(), TreeIndex(), BranchNodeBudsList()
    );
    _TreeArchetype = EntityManager::CreateEntityArchetype(
        "Tree",
        Translation(), Rotation(), Scale(), LocalToWorld(),
        TreeIndex(), TreeInfo(), TreeColor(), TreeAge(),
        TreeParameters(),
        RewardEstimation());

    _LeafQuery = EntityManager::CreateEntityQuery();
    EntityManager::SetEntityQueryAllFilters(_LeafQuery, LeafInfo());
    _BudQuery = EntityManager::CreateEntityQuery();
    EntityManager::SetEntityQueryAllFilters(_BudQuery, BudInfo());
    _BranchNodeQuery = EntityManager::CreateEntityQuery();
    EntityManager::SetEntityQueryAllFilters(_BranchNodeQuery, BranchNodeInfo());
    _TreeQuery = EntityManager::CreateEntityQuery();
    EntityManager::SetEntityQueryAllFilters(_TreeQuery, TreeInfo());
    
    _TreeSystem = Application::GetWorld()->CreateSystem<TreeSystem>(SystemGroup::SimulationSystemGroup);
    _BranchNodeSystem = Application::GetWorld()->CreateSystem<BranchNodeSystem>(SystemGroup::SimulationSystemGroup);
    _BudSystem = Application::GetWorld()->CreateSystem<BudSystem>(SystemGroup::SimulationSystemGroup);
    _LeafSystem = Application::GetWorld()->CreateSystem<LeafSystem>(SystemGroup::SimulationSystemGroup);
    


    _TreeIndex.Value = 0;
    _BudIndex.Value = 0;
    _LeafIndex.Value = 0;
    _BranchNodeIndex.Value = 0;

    _LightEstimator = new LightEstimator();

    _Ready = true;
}

bool TreeUtilities::TreeManager::IsReady()
{
    return _Ready;
}

EntityQuery TreeUtilities::TreeManager::GetLeafQuery()
{
    return _LeafQuery;
}

EntityQuery TreeUtilities::TreeManager::GetBudQuery()
{
    return _BudQuery;
}

EntityQuery TreeUtilities::TreeManager::GetBranchNodeQuery()
{
    return _BranchNodeQuery;
}

EntityQuery TreeUtilities::TreeManager::GetTreeQuery()
{
    return _TreeQuery;
}

LeafSystem* TreeUtilities::TreeManager::GetLeafSystem()
{
    return _LeafSystem;
}

BudSystem* TreeUtilities::TreeManager::GetBudSystem()
{
    return _BudSystem;
}

BranchNodeSystem* TreeUtilities::TreeManager::GetBranchNodeSystem()
{
    return _BranchNodeSystem;
}

TreeSystem* TreeUtilities::TreeManager::GetTreeSystem()
{
    return _TreeSystem;
}



void TreeUtilities::TreeManager::GetAllTrees(std::vector<Entity>* container)
{
    if (!_Ready) {
        Debug::Error("TreeManager: Not initialized!");
        return;
    }
    return _TreeQuery.ToEntityArray(container);
}

void TreeUtilities::TreeManager::GenerateLeavesForTree(Entity treeEntity, LeafInfo leafInfo)
{
    TreeIndex treeIndex = EntityManager::GetComponentData<TreeIndex>(treeEntity);
#pragma region Create leaves for all buds
    std::vector<Entity> buds;
    _BudQuery.ToEntityArray(treeIndex, &buds);
    for (Entity bud : buds) {
        //Clear all leafs
        auto children = EntityManager::GetChildren(bud);
        for (auto i : children) {
            if (EntityManager::HasComponentData<LeafIndex>(i)) EntityManager::DeleteEntity(i);
        }
        //Generate leaves
        int leavesAmount = 2;
        for (int i = 0; i < leavesAmount; i++) {
            Entity leaf = CreateLeaf(treeIndex, bud);
            //TODO: Set Component Data for leaf.
            EntityManager::SetComponentData(leaf, treeIndex);
            LeafGenerationHelper(leafInfo, leaf, bud, i);
        }
    }
#pragma endregion
#pragma region Prone leaves for all buds
    std::vector<Entity> leaves;
    _LeafQuery.ToEntityArray(treeIndex, &leaves);
    for (Entity leaf : leaves) {
        bool prone = false;
        //TODO: Add prone condition here.
        if (prone) EntityManager::DeleteEntity(leaf);
    }
#pragma endregion
}

void TreeUtilities::TreeManager::GenerateLeavesForAllTrees(LeafInfo leafInfo)
{
#pragma region Create leaves for all buds
    std::vector<Entity> buds;
    _BudQuery.ToEntityArray(&buds);
    for (Entity bud : buds) {
        //Clear all leafs
        auto children = EntityManager::GetChildren(bud);
        for (auto i : children) {
            if (EntityManager::HasComponentData<LeafIndex>(i)) EntityManager::DeleteEntity(i);
        }
        //Generate leaves
        int leavesAmount = 2;
        for (int i = 0; i < leavesAmount; i++) {
            Entity leaf = CreateLeaf(EntityManager::GetComponentData<TreeIndex>(bud), bud);
            //TODO: Set Component Data for leaf.
            LeafGenerationHelper(leafInfo, leaf, bud, i);
        }
    }
#pragma endregion
#pragma region Prone leaves for all buds
    std::vector<Entity> leaves;
    _LeafQuery.ToEntityArray(&leaves);
    for (Entity leaf : leaves) {
        bool prone = false;
        //TODO: Add prone condition here.
        if (prone) EntityManager::DeleteEntity(leaf);
    }
#pragma endregion
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

Entity TreeUtilities::TreeManager::CreateTree()
{
    auto entity = EntityManager::CreateEntity(_TreeArchetype);
    TreeInfo treeInfo;
    treeInfo.GravitropismLevelVal = new std::vector<float>();
    treeInfo.ApicalDominanceTimeVal = new std::vector<float>();
    EntityManager::SetComponentData(entity, treeInfo);
    EntityManager::SetComponentData(entity, _TreeIndex);
    _TreeIndex.Value++;
    return entity;
}

void TreeUtilities::TreeManager::DeleteTree(Entity treeEntity)
{
    TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(treeEntity);
    if (treeInfo.GravitropismLevelVal != nullptr) delete treeInfo.GravitropismLevelVal;
    if (treeInfo.ApicalDominanceTimeVal != nullptr) delete treeInfo.ApicalDominanceTimeVal;
    if (EntityManager::HasComponentData<BranchNodeInfo>(EntityManager::GetChildren(treeEntity).at(0))) {
        BranchRemover(EntityManager::GetChildren(treeEntity).at(0));
    }
    EntityManager::DeleteEntity(treeEntity);
}

Entity TreeUtilities::TreeManager::CreateBranchNode(TreeIndex treeIndex, Entity parentEntity)
{
    auto entity = EntityManager::CreateEntity(_BranchNodeArchetype);
    BranchNodeBudsList ob = BranchNodeBudsList();
    ob.Buds = new std::vector<Entity>();
    EntityManager::SetComponentData(entity, treeIndex);
    EntityManager::SetParent(entity, parentEntity);
    EntityManager::SetComponentData(entity, _BranchNodeIndex);
    EntityManager::SetComponentData(entity, ob);
    _BranchNodeIndex.Value++;
    BranchNodeInfo branchInfo;
    EntityManager::SetComponentData(entity, branchInfo);
    return entity;
}

Entity TreeUtilities::TreeManager::CreateBud(TreeIndex treeIndex, Entity parentEntity)
{
    auto entity = EntityManager::CreateEntity(_BudArchetype);
    EntityManager::SetComponentData(entity, treeIndex);
    EntityManager::SetParent(entity, parentEntity);
    EntityManager::SetComponentData(entity, _BudIndex);
    Activated act;
    act.Value = true;
    EntityManager::SetComponentData(entity, act);
    _BudIndex.Value++;
    return entity;
}

Entity TreeUtilities::TreeManager::CreateBudForBranchNode(TreeIndex treeIndex, Entity branchNodeEntity)
{
    auto entity = EntityManager::CreateEntity(_BudArchetype);
    BranchNodeOwner owner;
    owner.Value = branchNodeEntity;
    EntityManager::SetComponentData(entity, owner);
    EntityManager::GetComponentData<BranchNodeBudsList>(branchNodeEntity).Buds->push_back(entity);
    EntityManager::SetComponentData(entity, treeIndex);
    EntityManager::SetComponentData(entity, _BudIndex);
    Activated act;
    act.Value = true;
    EntityManager::SetComponentData(entity, act);
    _BudIndex.Value++;
    return entity;
}

Entity TreeUtilities::TreeManager::CreateLeaf(TreeIndex treeIndex, Entity parentEntity)
{
    auto entity = EntityManager::CreateEntity(_LeafArchetype);
    EntityManager::SetComponentData(entity, treeIndex);
    EntityManager::SetParent(entity, parentEntity);
    EntityManager::SetComponentData(entity, _LeafIndex);
    _LeafIndex.Value++;
    return entity;
}

LightEstimator* TreeUtilities::TreeManager::GetLightEstimator()
{
    return _LightEstimator;
}

void TreeUtilities::TreeManager::CalculateRewards(Entity treeEntity, float snapShotWidth)
{
    RewardEstimation estimation = EntityManager::GetComponentData<RewardEstimation>(treeEntity);
    _LightEstimator->TakeSnapShot(treeEntity, true);
    estimation.LightEstimationResult = _LightEstimator->GetScore();

    EntityManager::SetComponentData(treeEntity, estimation);
}

Mesh* TreeUtilities::TreeManager::GetMeshForTree(Entity treeEntity)
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

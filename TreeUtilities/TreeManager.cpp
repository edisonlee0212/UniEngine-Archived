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
inline void TreeUtilities::TreeManager::LeafGenerationHelper(BudInfo& info, Entity& leaf, Entity& bud, int index)
{
	Translation t = EntityManager::GetComponentData<Translation>(bud);
	Scale s;
	Rotation r;
	s.Value = glm::vec3(info.LeafWidth, info.LeafThickness, info.LeafLength);
	BranchNodeOwner owner = EntityManager::GetComponentData<BranchNodeOwner>(bud);
	glm::vec3 budDirection;
	if (owner.Value.Version == 0) {
		budDirection = EntityManager::GetComponentData<Rotation>(bud).Value * glm::vec3(0, 0, -1);
	}
	else {
		budDirection = EntityManager::GetComponentData<Rotation>(owner.Value).Value * glm::vec3(0, 0, -1);
	}
	glm::vec3 front = glm::normalize(glm::cross(glm::cross(budDirection, glm::vec3(0, 1, 0)), glm::vec3(0, 1, 0)));
	front = glm::rotate(front, glm::radians(info.CircleDegreeStart + index * info.CircleDegreeAddition), glm::vec3(0, 1, 0));
	front = glm::rotate(front, glm::radians(info.BendDegrees), glm::cross(front, glm::vec3(0, 1, 0)));
	r.Value = glm::quatLookAt(front, glm::vec3(0, 1, 0));
	if (glm::any(glm::isnan(r.Value))) {
		float random = glm::radians(glm::linearRand(0.0f, 360.0f));
		front = glm::vec3(glm::sin(random), 0, glm::cos(random));
		front = glm::rotate(front, glm::radians(info.CircleDegreeStart + index * info.CircleDegreeAddition), glm::vec3(0, 1, 0));
		front = glm::rotate(front, glm::radians(info.BendDegrees), glm::cross(front, glm::vec3(0, 1, 0)));
		r.Value = glm::quatLookAt(front, glm::vec3(0, 1, 0));
	}
	EntityManager::SetComponentData(leaf, t);
	EntityManager::SetComponentData(leaf, s);
	EntityManager::SetComponentData(leaf, r);
}
void TreeUtilities::TreeManager::BranchNodeRemover(Entity branchEntity)
{
	BranchNodeBudsList ob = EntityManager::GetComponentData<BranchNodeBudsList>(branchEntity);
	delete ob.Buds;
	EntityManager::ForEachChild(branchEntity, [](Entity child) {
		BranchNodeRemover(child);
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
		Radius(), BudIndex(), Iteration(), Level(), BudInfo(), TreeIndex()
	);
	_BranchNodeArchetype = EntityManager::CreateEntityArchetype(
		"BranchNode",
		LocalToWorld(), Connection(),
		BranchNodeIllumination(), GravityForceSensor(),
		BranchNodeIndex(), BranchNodeInfo(), TreeIndex(), BranchNodeBudsList()
	);
	_TreeArchetype = EntityManager::CreateEntityArchetype(
		"Tree",
		Translation(), Rotation(), Scale(), LocalToWorld(),
		TreeIndex(), TreeInfo(), TreeColor(), TreeAge(),
		TreeParameters(),
		RewardEstimation(),
		TreeLeafPruningFactor()
		);

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

void TreeUtilities::TreeManager::GenerateLeavesForTree(Entity treeEntity)
{
	TreeIndex treeIndex = EntityManager::GetComponentData<TreeIndex>(treeEntity);
#pragma region Create leaves for all branchNodes
	std::vector<Entity> buds;
	_BudQuery.ToEntityArray(treeIndex, &buds);
	for (Entity bud : buds) {
		//Clear all leafs
		auto children = EntityManager::GetChildren(bud);
		for (auto i : children) {
			if (EntityManager::HasComponentData<LeafInfo>(i)) EntityManager::DeleteEntity(i);
		}
		auto budInfo = EntityManager::GetComponentData<BudInfo>(bud);
		//Generate leaves
		for (int i = 0; i < budInfo.LeafAmount; i++) {
			Entity leaf = CreateLeaf(treeIndex, bud);
			//TODO: Set Component Data for leaf.
			EntityManager::SetComponentData(leaf, treeIndex);
			LeafGenerationHelper(budInfo, leaf, bud, i);
		}
	}
#pragma endregion

}

void TreeUtilities::TreeManager::CalculateBranchNodeIllumination()
{
	std::vector<Entity> branchNodes;
	_BranchNodeQuery.ToEntityArray(&branchNodes);
	TreeManager::GetLightEstimator()->TakeSnapShot(true);
	EntityManager::ForEach<BranchNodeIllumination, TreeIndex>(_BranchNodeQuery, [](int i, Entity leafEntity, BranchNodeIllumination* illumination, TreeIndex* index) 
		{
			illumination->LightDir = glm::vec3(0);
			illumination->Value = 0;
		}
	);
	auto snapShots = _LightEstimator->GetSnapShots();
	float maxIllumination = 0;
	for (const auto& shot : *snapShots) {
		size_t resolution = shot->Resolution();
		std::vector<std::shared_future<void>> futures;
		std::mutex writeMutex;
		std::mutex maxIlluminationMutex;
		for (size_t i = 0; i < resolution; i++) {
			futures.push_back(_ThreadPool->Push([i, shot, resolution, &writeMutex, &maxIlluminationMutex, &maxIllumination](int id)
				{
					float localMaxIllumination = 0;
					for (size_t j = 0; j < resolution; j++) {
						unsigned index = shot->GetEntityIndex(i, j);
						if (index != 0) {
							std::lock_guard<std::mutex> lock(writeMutex);
							BranchNodeIllumination illumination = EntityManager::GetComponentData<BranchNodeIllumination>(index);
							illumination.LightDir += shot->GetDirection() * shot->Weight();
							illumination.Value += shot->Weight();
							if (localMaxIllumination < illumination.Value) localMaxIllumination = illumination.Value;
							EntityManager::SetComponentData(index, illumination);
						}
					}
					std::lock_guard<std::mutex> lock(maxIlluminationMutex);
					if (maxIllumination < localMaxIllumination) maxIllumination = localMaxIllumination;
				}
			).share());
		}
		for (auto i : futures) i.wait();
	}
	_LightEstimator->SetMaxIllumination(maxIllumination);
}

void TreeUtilities::TreeManager::GenerateLeavesForAllTrees()
{
#pragma region Create leaves for all branchNodes
	std::vector<Entity> buds;
	_BudQuery.ToEntityArray(&buds);
	for (int budIndex = 0; budIndex < buds.size(); budIndex++) {
		auto& bud = buds.at(budIndex);
		//Clear all leafs
		auto children = EntityManager::GetChildren(bud);
		for (auto i : children) {
			if (EntityManager::HasComponentData<LeafInfo>(i)) EntityManager::DeleteEntity(i);
		}
		auto budInfo = EntityManager::GetComponentData<BudInfo>(bud);
		//Generate leaves
		for (int i = 0; i < budInfo.LeafAmount; i++) {
			Entity leaf = CreateLeaf(EntityManager::GetComponentData<TreeIndex>(bud), bud);
			EntityManager::SetComponentData(leaf, EntityManager::GetComponentData<TreeIndex>(bud));
			//TODO: Set Component Data for leaf.
			LeafGenerationHelper(budInfo, leaf, bud, i);
		}
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
	treeInfo.ApicalControlTimeVal = new std::vector<float>();
	treeInfo.ApicalControlTimeLevelVal = new std::vector<std::vector<float>>();
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
	if (treeInfo.ApicalControlTimeVal != nullptr) delete treeInfo.ApicalControlTimeVal;
	if (treeInfo.ApicalControlTimeLevelVal != nullptr) delete treeInfo.ApicalControlTimeLevelVal;

	if (EntityManager::HasComponentData<BranchNodeInfo>(EntityManager::GetChildren(treeEntity).at(0))) {
		BranchNodeRemover(EntityManager::GetChildren(treeEntity).at(0));
	}
	EntityManager::DeleteEntity(treeEntity);
}

Entity TreeUtilities::TreeManager::CreateBranchNode(TreeIndex treeIndex, Entity parentEntity)
{
	auto entity = EntityManager::CreateEntity(_BranchNodeArchetype);
	BranchNodeBudsList ob = BranchNodeBudsList();
	ob.Buds = new std::vector<Bud>();
	EntityManager::SetComponentData(entity, treeIndex);
	EntityManager::SetParent(entity, parentEntity);
	EntityManager::SetComponentData(entity, _BranchNodeIndex);
	EntityManager::SetComponentData(entity, ob);
	_BranchNodeIndex.Value++;
	BranchNodeInfo branchInfo;
	branchInfo.MaxActivatedChildLevel = 0;
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

Entity TreeUtilities::TreeManager::CreateLeaf(TreeIndex treeIndex, Entity parentEntity)
{
	auto entity = EntityManager::CreateEntity(_LeafArchetype);
	LeafAlive alive;
	alive.Value = true;
	EntityManager::SetComponentData(entity, alive);
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
	estimation.LightEstimationResult = _LightEstimator->CalculateScore();

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

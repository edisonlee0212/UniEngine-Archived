#include "PlantSimulationSystem.h"


void TreeUtilities::PlantSimulationSystem::DeactivateBranch(size_t listIndex, size_t index)
{
	_TreeActivatedBranchesLists[listIndex].Branches[index].Activated = false;
	Activated act;
	act.Value = false;
	EntityManager::SetComponentData(_TreeActivatedBranchesLists[listIndex].Branches[index].BranchEntity, act);
}

bool TreeUtilities::PlantSimulationSystem::GenerateShootsFromBud(Entity budEntity, Entity branchEntity, bool isLateral)
{
	return false;
}

void TreeUtilities::PlantSimulationSystem::DrawGUI()
{

}

void TreeUtilities::PlantSimulationSystem::GrowTree(size_t index)
{
	int startIndex = _TreeActivatedBranchesLists[index].Branches.size();
	Entity tree = _TreeActivatedBranchesLists[index].TreeEntity;
	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(tree);
	GeometricParamGroup gPG = EntityManager::GetComponentData<GeometricParamGroup>(tree);
	BudFateParamGroup bPG = EntityManager::GetComponentData<BudFateParamGroup>(tree);
	EnvironmentalParamGroup ePG = EntityManager::GetComponentData<EnvironmentalParamGroup>(tree);
	bool growed = false;
	//Grow buds in reverse order.
	for (int i = startIndex - 1; i >= 0; i--) {
		Branch b = _TreeActivatedBranchesLists[index].Branches[i];
		Entity branch = b.BranchEntity;
		BranchInfo branchInfo = EntityManager::GetComponentData<BranchInfo>(branch);
		Activated branchActivated = EntityManager::GetComponentData<Activated>(branch);
		if (!branchActivated.Value) continue;
		std::vector<Entity>* buds = EntityManager::GetComponentData<BranchBudsList>(branch).Buds;
		bool branchGrowed = false;
		float lateralInhibitorToAdd = 0;
		for (int j = 0; j < buds->size(); j++) {
			Entity bud = buds->at(j);
			Activated budActivated = EntityManager::GetComponentData<Activated>(bud);
			if (!budActivated.Value) continue;
			BudInfo budInfo = EntityManager::GetComponentData<BudInfo>(bud);
			BudIllumination illumination = EntityManager::GetComponentData<BudIllumination>(bud);
			//First check whether we want to kill the bud completly (due to some unspecific reason - environment)
			float budKillProbability = 0;
			if (budInfo.Type == BudTypes::APICAL) {
				if (i == 0) budKillProbability = 0;
				else budKillProbability = bPG.ApicalBudExtintionRate;
			}
			else budKillProbability = bPG.LateralBudEntintionRate;
			if (glm::linearRand(0, 1) < budKillProbability) {
				branchInfo.ActivatedBudsAmount--;
				budActivated.Value = false;
				if (budInfo.Type == BudTypes::APICAL) {
					branchInfo.ApicalBudExist = false;
				}
				EntityManager::SetComponentData(bud, budInfo);
				EntityManager::SetComponentData(branch, branchInfo);
			}
			//compute probability that the given bud can grow
			float budGrowProbability = 1;
			// first take into account the apical dominance
			if (budInfo.Inhibitor > 0) budGrowProbability *= glm::exp(-budInfo.Inhibitor);
			// now take into consideration the light on the bud
			if (illumination.Value < 1) {
				budGrowProbability *= glm::pow(illumination.Value, budInfo.Type == BudTypes::APICAL ? bPG.ApicalBudLightingFactor : bPG.LateralBudLightingFactor);
			}
			// now check whether the bud is going to flush or not
			bool flush = (budGrowProbability > glm::linearRand(0, 1));
			bool budRemoved = false;
			// if the bud is flushing we need to generate the new shoot and add an inhibitor to this node
			if (flush) {
				// generate shoot
				bool isLateral = !(budInfo.Type == BudTypes::APICAL && EntityManager::GetChildrenAmount(branch) == 0);
				if (GenerateShootsFromBud(bud, branch, isLateral)) {
					float localInhibitor = 0;
					if (treeInfo.Age <= 1) localInhibitor += bPG.ApicalDominanceBase;
					else {

					}
					if (budInfo.Type == BudTypes::APICAL) {
						branchInfo.Inhibitor += localInhibitor;
						EntityManager::SetComponentData(branch, branchInfo);
					}
					else {
						lateralInhibitorToAdd += localInhibitor;
					}
					budRemoved = true;
					growed = true;
				}
			}
			if (!budRemoved) {
				int budAge = treeInfo.Age - budInfo.StartAge;
				if (budAge > bPG.MaxBudAge) {
					budRemoved = true;

					branchInfo.ActivatedBudsAmount--;
					budActivated.Value = false;
					if (budInfo.Type == BudTypes::APICAL) {
						branchInfo.ApicalBudExist = false;
					}
					EntityManager::SetComponentData(bud, budInfo);
					EntityManager::SetComponentData(branch, branchInfo);
				}
			}
		}
		branchInfo.Inhibitor += lateralInhibitorToAdd;
		EntityManager::SetComponentData(branch, branchInfo);
	}
}

Entity TreeUtilities::PlantSimulationSystem::CreateTree(TreeColor color, glm::vec3 position, bool enabled)
{
	BudInfo budInfo;
	budInfo.StartAge = 0;
	budInfo.Inhibitor = 0;
	budInfo.Type = BudTypes::APICAL;
	budInfo.Searching = true;
	auto treeEntity = TreeManager::CreateTree();
	Entity branchEntity = TreeManager::CreateBranch(EntityManager::GetComponentData<TreeIndex>(treeEntity), treeEntity);
	BranchInfo branchInfo;
	branchInfo.ApicalBudExist = true;
	EntityManager::SetComponentData(branchEntity, branchInfo);
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = glm::vec3(1.0f);
	EntityManager::SetComponentData(treeEntity, t);
	EntityManager::SetComponentData(treeEntity, s);
	EntityManager::SetComponentData(treeEntity, color);
	TreeGrowIteration iteration;
	iteration.Value = 0;
	iteration.Enable = enabled;
	EntityManager::SetComponentData(treeEntity, iteration);
	auto budEntity = TreeManager::CreateBudForBranch(EntityManager::GetComponentData<TreeIndex>(treeEntity), branchEntity);

	EntityManager::SetComponentData(budEntity, t);
	EntityManager::SetComponentData(budEntity, s);
	EntityManager::SetComponentData(budEntity, budInfo);

	Branches tab;
	tab.TreeEntity = treeEntity;
	Branch branch;
	branch.Activated = true;
	branch.BranchEntity = branchEntity;
	tab.Branches.push_back(branch);
	return treeEntity;
}

#pragma region Helpers

void TreeUtilities::PlantSimulationSystem::GrowAllTrees()
{
	std::vector<std::shared_future<void>> futures;
	for (size_t i = 0; i < _TreeActivatedBranchesLists.size(); i++) {
		futures.push_back(_ThreadPool->Push([this, i](int jobIndex)
			{
				GrowTree(i);
			}).share());
	}
	for (auto i : futures) i.wait();
}

void TreeUtilities::PlantSimulationSystem::DestroyedTreeCheck()
{
	for (size_t i = 0; i < _TreeActivatedBranchesLists.size(); i++) {
		if (_TreeActivatedBranchesLists[i].TreeEntity.IsDeleted()) _TreeActivatedBranchesLists.erase(_TreeActivatedBranchesLists.begin() + i);
		i--;
	}
}

void TreeUtilities::PlantSimulationSystem::GrowTree(Entity treeEntity)
{
	for (size_t i = 0; i < _TreeActivatedBranchesLists.size(); i++) {
		if (treeEntity == _TreeActivatedBranchesLists[i].TreeEntity) {
			GrowTree(i);
		}
	}
}

void TreeUtilities::PlantSimulationSystem::OnCreate()
{
}

void TreeUtilities::PlantSimulationSystem::OnDestroy()
{
}

void TreeUtilities::PlantSimulationSystem::Update()
{
}

void TreeUtilities::PlantSimulationSystem::FixedUpdate()
{
}
#pragma endregion

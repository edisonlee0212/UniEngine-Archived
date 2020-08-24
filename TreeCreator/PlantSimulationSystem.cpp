#include "PlantSimulationSystem.h"


inline void TreeUtilities::PlantSimulationSystem::DeactivateBud(Entity bud, Entity branchNode, BudInfo* budInfo, BranchNodeInfo* branchNodeInfo)
{
	branchNodeInfo->ActivatedBudsAmount--;
	Activated act;
	act.Value = false;
	if (budInfo->Type == BudTypes::APICAL) {
		branchNodeInfo->ApicalBudExist = false;
	}
	EntityManager::SetComponentData(bud, *budInfo);
	EntityManager::SetComponentData(branchNode, *branchNodeInfo);
	EntityManager::SetComponentData(bud, act);
	if (branchNodeInfo->ActivatedBudsAmount == 0) {
		//Also deactivate branch here.
		EntityManager::SetComponentData(branchNode, act);
	}
}

void TreeUtilities::PlantSimulationSystem::DeactivateBranch(size_t listIndex, size_t index)
{
	_TreeActivatedBranchNodesLists[listIndex].BranchNodes[index].Activated = false;
	Activated act;
	act.Value = false;
	EntityManager::SetComponentData(_TreeActivatedBranchNodesLists[listIndex].BranchNodes[index].BranchNodeEntity, act);
}

void TreeUtilities::PlantSimulationSystem::DrawGUI()
{

}

bool TreeUtilities::PlantSimulationSystem::GrowTree(size_t index)
{
#pragma region Collect tree data
	int startIndex = _TreeActivatedBranchNodesLists[index].BranchNodes.size();
	Entity tree = _TreeActivatedBranchNodesLists[index].TreeEntity;
	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(tree);
	TreeAge treeAge = EntityManager::GetComponentData<TreeAge>(tree);
	TreeParameters tps = EntityManager::GetComponentData<TreeParameters>(tree);
	TreeIndex treeIndex = EntityManager::GetComponentData<TreeIndex>(tree);
	if (treeAge.Value >= tps.Age) {
		return false;
	}
#pragma endregion
#pragma region Grow branch nodes in reverse order of the tree.
	for (int selectedBranchNodeIndex = startIndex - 1; selectedBranchNodeIndex >= 0; selectedBranchNodeIndex--) {
#pragma region Collect branch node Data
		BranchNode b = _TreeActivatedBranchNodesLists[index].BranchNodes[selectedBranchNodeIndex];
		Entity branchNode = b.BranchNodeEntity;
		BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
		Activated branchActivated = EntityManager::GetComponentData<Activated>(branchNode);
		if (!branchActivated.Value) {
			_TreeActivatedBranchNodesLists[index].BranchNodes.erase(_TreeActivatedBranchNodesLists[index].BranchNodes.begin() + selectedBranchNodeIndex);
			selectedBranchNodeIndex++;
			continue;
		}
		std::vector<Entity>* buds = EntityManager::GetComponentData<BranchNodeBudsList>(branchNode).Buds;
#pragma endregion
#pragma region Collect inhibitor from children and apply instantly.
		float gatheredInhibitor = 0;
		EntityManager::ForEachChild(branchNode, [&gatheredInhibitor](Entity child) {
			BranchNodeInfo bi = EntityManager::GetComponentData<BranchNodeInfo>(child);
			gatheredInhibitor += bi.Inhibitor * bi.ParentInhibitorFactor;
			});
		branchNodeInfo.Inhibitor += gatheredInhibitor;
		EntityManager::SetComponentData<BranchNodeInfo>(branchNode, branchNodeInfo);
#pragma endregion
		float lateralInhibitorToAdd = 0;
		for (int selectedBudIndex = 0; selectedBudIndex < buds->size(); selectedBudIndex++) {
#pragma region Collect bud data
			Entity bud = buds->at(selectedBudIndex);
			Activated budActivated = EntityManager::GetComponentData<Activated>(bud);
			if (!budActivated.Value) continue;
			BudInfo budInfo = EntityManager::GetComponentData<BudInfo>(bud);
			Rotation budRotation = EntityManager::GetComponentData<Rotation>(bud);
			BudIllumination illumination = EntityManager::GetComponentData<BudIllumination>(bud);
#pragma endregion
#pragma region Kill check
			//First check whether we want to kill the bud completly (due to some unspecific reason - environment)
			float budKillProbability = 0;
			if (budInfo.Type == BudTypes::APICAL) {
				if (selectedBranchNodeIndex == 0) budKillProbability = 0;
				else budKillProbability = tps.ApicalBudExtintionRate;
			}
			else budKillProbability = tps.LateralBudEntintionRate;
			if (glm::linearRand(0, 1) < budKillProbability) {
				branchNodeInfo.ActivatedBudsAmount--;
				budActivated.Value = false;
				if (budInfo.Type == BudTypes::APICAL) {
					branchNodeInfo.ApicalBudExist = false;
				}
				EntityManager::SetComponentData(bud, budInfo);
				EntityManager::SetComponentData(branchNode, branchNodeInfo);
				continue;
			}
#pragma endregion
#pragma region Grow check
			//compute probability that the given bud can grow
			float budGrowProbability = 1;
			// first take into account the apical dominance
			if (budInfo.Inhibitor > 0) budGrowProbability *= glm::exp(-budInfo.Inhibitor);
			// now take into consideration the light on the bud
			if (illumination.Value < 1) {
				//budGrowProbability *= glm::pow(illumination.Value, budInfo.Type == BudTypes::APICAL ? tps.ApicalBudLightingFactor : tps.LateralBudLightingFactor);
			}
			// now check whether the bud is going to flush or not
			bool flush = (budGrowProbability > glm::linearRand(0, 1));
#pragma endregion
			bool budRemoved = false;
#pragma region If the bud is flushing we need to generate the new shoot and add an inhibitor to this node.
			if (flush) {
				// generate shoot
				bool isLateral = !(budInfo.Type == BudTypes::APICAL && EntityManager::GetChildrenAmount(branchNode) == 0);
				bool growSucceed = false;
#pragma region Compute total grow distance and internodes amount.
				int level = branchNodeInfo.Level;
				if (isLateral) level++;
				float apicalControl = 0;
				float internodesToGrowF = tps.GrowthRate;
				//Calculate base apical control for this age.
				apicalControl = tps.ApicalControl * glm::pow(tps.ApicalControlAgeFactor, treeAge.Value);
				if (apicalControl > 1.0f) {
					internodesToGrowF *= (1.0f + (apicalControl - 1.0f) * glm::pow(tps.ApicalControlLevelFactor, level));
				}
				else {
					internodesToGrowF *= (1.0f - (1.0f - apicalControl) * (1.0f - glm::pow(tps.ApicalControlLevelFactor, treeAge.Value - level)));
				}
				

				int internodesToGrow = glm::floor(internodesToGrowF + 0.5f);
				if (internodesToGrow != 0) {
					growSucceed = true;
				}
#pragma endregion
#pragma region Grow new shoot.
				if (growSucceed) {
					float internodeLength = 1.0f;
					internodeLength *= tps.InternodeLengthBase * glm::pow(tps.InternodeLengthAgeFactor, treeAge.Value);
					int level = branchNodeInfo.Level;
					if (budInfo.Type == BudTypes::LATERAL) level++;
					Entity prevBranchNode = branchNode;
					Translation prevBranchNodeTranslation = EntityManager::GetComponentData<Translation>(branchNode);
					Rotation prevBranchNodeRotation = budRotation;
					Scale prevBranchNodeScale = EntityManager::GetComponentData<Scale>(branchNode);

					for (int selectedNewNodeIndex = 0; selectedNewNodeIndex < internodesToGrow; selectedNewNodeIndex++) {
						Translation newBranchNodeTranslation = Translation();
						Rotation newBranchNodeRotation = Rotation();
						Scale newBranchNodeScale = Scale();
#pragma region Calculate new node transform
						newBranchNodeRotation = prevBranchNodeRotation;
						newBranchNodeScale.Value = prevBranchNodeScale.Value;
						glm::vec3 direction = newBranchNodeRotation.Value * glm::vec3(0, 0, -1);
						newBranchNodeTranslation.Value = prevBranchNodeTranslation.Value + internodeLength * direction;
#pragma endregion
						Entity newBranchNode = TreeManager::CreateBranchNode(treeIndex, prevBranchNode);
						BranchNode bn;
						bn.Activated = true;
						bn.BranchNodeEntity = newBranchNode;
						_TreeActivatedBranchNodesLists[index].BranchNodes.push_back(bn);
						BranchNodeInfo newBranchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(newBranchNode);
						newBranchNodeInfo.DistanceToParent = internodeLength;
						newBranchNodeInfo.Level = level;
						newBranchNodeInfo.ParentInhibitorFactor = glm::pow(tps.ApicalDominanceDistanceFactor, newBranchNodeInfo.DistanceToParent);
						newBranchNodeInfo.DesiredBranchDirection = newBranchNodeRotation.Value;
						treeInfo.ActiveLength += newBranchNodeInfo.DistanceToParent;
#pragma region Generate buds for branch node.
						glm::quat prevBudRotation = prevBranchNodeRotation.Value;
						for (int selectedNewBudIndex = 0; selectedNewBudIndex < tps.LateralBudNumber; selectedNewBudIndex++) {
							Entity newBud = TreeManager::CreateBudForBranchNode(treeIndex, newBranchNode);
							BudInfo newBudInfo = EntityManager::GetComponentData<BudInfo>(newBud);
							Translation newBudTranslation = Translation();
							newBudTranslation.Value = prevBranchNodeTranslation.Value + (newBranchNodeTranslation.Value - prevBranchNodeTranslation.Value) / (float)tps.LateralBudNumber * (float)(selectedNewBudIndex + 1);
							Rotation newBudRotation;
							Scale newBudScale = Scale();
							newBudScale.Value = prevBranchNodeScale.Value + (newBranchNodeScale.Value - prevBranchNodeScale.Value) / (float)tps.LateralBudNumber * (float)(selectedNewBudIndex + 1);
							newBudRotation.Value = prevBudRotation;
							glm::vec3 front = newBudRotation.Value * glm::vec3(0, 0, -1);
							glm::vec3 up = newBudRotation.Value * glm::vec3(0, 1, 0);
							up = glm::rotate(up,
								glm::radians(tps.MeanRollAngle + tps.VarianceRollAngle * glm::linearRand(-1, 1)), front);
							//If this is the last bud, we need to apply apical angle variance.
							if (selectedNewBudIndex == tps.LateralBudNumber - 1) {
								glm::vec3 right = glm::cross(front, up);
								right = glm::rotate(right, glm::radians(glm::linearRand(0.0f, 360.0f)), front);
								front = glm::rotate(front, glm::radians(glm::gaussRand(tps.VarianceApicalAngle, 1.0f)), right);
								right = glm::cross(front, up);
								up = glm::cross(right, front);
							}
							newBudRotation.Value = glm::quatLookAt(front, up);
							prevBudRotation = newBudRotation.Value;
							if (selectedNewBudIndex == tps.LateralBudNumber - 1) {
								prevBranchNodeRotation = newBudRotation;
							}
							//If the bud is the last bud of the entire shoot, it's set as apical.
							if (selectedBranchNodeIndex == internodesToGrow - 1 && selectedNewBudIndex == tps.LateralBudNumber - 1) {
								newBudInfo.Type = BudTypes::APICAL;
							}
							else {
								newBudInfo.Type = BudTypes::LATERAL;
#pragma region Bend Lateral bud direction
								glm::vec3 front = newBudRotation.Value * glm::vec3(0, 0, -1);
								glm::vec3 left = newBudRotation.Value * glm::vec3(-1, 0, 0);
								front = glm::rotate(front, glm::radians(tps.MeanBranchingAngle + tps.VarianceBranchingAngle * glm::linearRand(-1, 1)), left);
								glm::vec3 up = glm::cross(front, left);
								newBudRotation.Value = glm::quatLookAt(front, up);
							}
#pragma region Apply tropisms to bud direction

#pragma endregion
#pragma region Deactivate first bud or apply info.
							if (selectedNewBudIndex == 0) {
								DeactivateBud(newBud, newBranchNode, &budInfo, &branchNodeInfo);
							}
							else {
								EntityManager::SetComponentData(newBud, newBudInfo);
								EntityManager::SetComponentData(newBranchNode, newBranchNodeInfo);
							}
#pragma endregion
							EntityManager::SetComponentData(newBud, newBudRotation);
							EntityManager::SetComponentData(newBud, newBudTranslation);
							EntityManager::SetComponentData(newBud, newBudScale);
						}

#pragma endregion
						EntityManager::SetComponentData<Translation>(newBranchNode, newBranchNodeTranslation);
						EntityManager::SetComponentData<Rotation>(newBranchNode, newBranchNodeRotation);
						EntityManager::SetComponentData<Scale>(newBranchNode, newBranchNodeScale);
						prevBranchNode = newBranchNode;
						prevBranchNodeTranslation = newBranchNodeTranslation;
						prevBranchNodeScale = newBranchNodeScale;
					}
#pragma region Deactivate current bud since we formed a new shoot from this bud.
					budRemoved = true;
					DeactivateBud(bud, branchNode, &budInfo, &branchNodeInfo);
#pragma endregion
#pragma region Add inhibitor to this branchnode.
					float localInhibitor = 0;
					if (tps.Age <= 1) localInhibitor += tps.ApicalDominanceBase;
					else {
						localInhibitor += tps.ApicalDominanceBase * tps.ApicalControl * glm::pow(tps.ApicalControlAgeFactor, treeAge.Value);
					}
					if (budInfo.Type == BudTypes::APICAL) {
						branchNodeInfo.Inhibitor += localInhibitor;
						EntityManager::SetComponentData(branchNode, branchNodeInfo);
					}
					else {
						lateralInhibitorToAdd += localInhibitor;
					}
#pragma endregion
				}
#pragma endregion
			}
#pragma endregion
#pragma region If the bud didnt flush then check whether we should remove it because of the old age.
			if (!budRemoved) {
				int budAge = treeAge.Value - budInfo.StartAge;
				if (budAge > tps.MaxBudAge) {
					budRemoved = true;
					DeactivateBud(bud, branchNode, &budInfo, &branchNodeInfo);
				}
			}
#pragma endregion
		}
#pragma region Apply inhibitor

#pragma endregion

		branchNodeInfo.Inhibitor += lateralInhibitorToAdd;
		EntityManager::SetComponentData(branchNode, branchNodeInfo);
	}
#pragma endregion
	treeAge.Value++;
	EntityManager::SetComponentData(tree, treeAge);
	return !_TreeActivatedBranchNodesLists[index].BranchNodes.empty();
}

Entity TreeUtilities::PlantSimulationSystem::CreateExampleTree(TreeColor color, glm::vec3 position, int index, bool enabled)
{
	TreeParameters tps = TreeParameters();
	switch (index)
	{
	case 1:
		tps.VarianceApicalAngle = 10;
		tps.LateralBudNumber = 4;
		tps.MeanBranchingAngle = 38;
		tps.VarianceBranchingAngle = 2;
		tps.MeanRollAngle = 91;
		tps.VarianceRollAngle = 1;

		tps.ApicalBudExtintionRate = 0;
		tps.LateralBudEntintionRate = 0.21f;
		tps.ApicalBudLightingFactor = 0.39f;
		tps.LateralBudLightingFactor = 1.13f;
		tps.ApicalDominanceBase = 3.13f;
		tps.ApicalDominanceDistanceFactor = 0.13f;
		tps.ApicalDominanceAgeFactor = 0.82;
		tps.GrowthRate = 2.7f;
		tps.InternodeLengthBase = 10.2f;
		tps.InternodeLengthAgeFactor = 0.97f;

		tps.ApicalControl = 2.4f;
		tps.ApicalControlAgeFactor = 0.85f;
		tps.ApicalControlLevelFactor = 0.8f;
		tps.Phototropism = 0.29f;
		tps.GravitropismBase = 0.61f;
		tps.PruningFactor = 0.05;
		tps.LowBranchPruningFactor = 1.3f;
		tps.GravityBendingStrength = 0.73f;
		tps.GravityBendingAngleFactor = 0.05f;
		tps.Age = 8;
		break;
	case 2:
		tps.VarianceApicalAngle = 10;
		tps.LateralBudNumber = 2;
		tps.MeanBranchingAngle = 51;
		tps.VarianceBranchingAngle = 4;
		tps.MeanRollAngle = 100;
		tps.VarianceRollAngle = 30;

		tps.ApicalBudExtintionRate = 0;
		tps.LateralBudEntintionRate = 0.015f;
		tps.ApicalBudLightingFactor = 0.36f;
		tps.LateralBudLightingFactor = 0.65f;
		tps.ApicalDominanceBase = 6.29f;
		tps.ApicalDominanceDistanceFactor = 0.9f;
		tps.ApicalDominanceAgeFactor = 0.87;
		tps.GrowthRate = 3.26f;
		tps.InternodeLengthBase = 4.0f;
		tps.InternodeLengthAgeFactor = 0.96f;

		tps.ApicalControl = 6.2f;
		tps.ApicalControlAgeFactor = 0.7f;
		tps.ApicalControlLevelFactor = 0.5f;
		tps.Phototropism = 0.42f;
		tps.GravitropismBase = 0.43f;
		tps.PruningFactor = 0.12;
		tps.LowBranchPruningFactor = 1.25f;
		tps.GravityBendingStrength = 0.94f;
		tps.GravityBendingAngleFactor = 0.52f;
		tps.Age = 6;
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		tps.LateralBudNumber = 4;
		tps.VarianceApicalAngle = 38;
		tps.MeanBranchingAngle = 38;
		tps.MeanRollAngle = 90;
		tps.VarianceRollAngle = 1;

		tps.ApicalBudExtintionRate = 0;
		tps.LateralBudEntintionRate = 0.21f;
		tps.ApicalBudLightingFactor = 0.39f;
		tps.LateralBudLightingFactor = 1.13f;
		tps.ApicalDominanceBase = 3.13f;
		tps.ApicalDominanceDistanceFactor = 0.13f;
		tps.ApicalDominanceAgeFactor = 0.82;
		tps.GrowthRate = 0.98f;
		tps.InternodeLengthBase = 10.2f;
		tps.InternodeLengthAgeFactor = 0.97f;

		tps.ApicalControl = 2.4f;
		tps.ApicalControlAgeFactor = 0.85f;
		tps.ApicalControlLevelFactor = 0.9f;
		tps.Phototropism = 0.29f;
		tps.GravitropismBase = 0.61f;
		tps.PruningFactor = 0.05;
		tps.LowBranchPruningFactor = 1.3f;
		tps.GravityBendingStrength = 0.73f;
		tps.GravityBendingAngleFactor = 0.05f;
		tps.Age = 8;
		break;
	}

	return CreateTree(tps, color, position);
}

#pragma region Helpers

void TreeUtilities::PlantSimulationSystem::GrowAllTrees()
{
	std::vector<std::shared_future<void>> futures;
	for (size_t i = 0; i < _TreeActivatedBranchNodesLists.size(); i++) {
		futures.push_back(_ThreadPool->Push([this, i](int jobIndex)
			{
				GrowTree(i);
			}).share());
	}
	for (auto i : futures) i.wait();
	for (size_t i = 0; i < _TreeActivatedBranchNodesLists.size(); i++) {
		if (_TreeActivatedBranchNodesLists[i].BranchNodes.empty()) {
			_TreeActivatedBranchNodesLists.erase(_TreeActivatedBranchNodesLists.begin() + i);
			i--;
		}
	}
}

void TreeUtilities::PlantSimulationSystem::CompleteAllTrees()
{
	std::vector<std::shared_future<void>> futures;
	for (size_t i = 0; i < _TreeActivatedBranchNodesLists.size(); i++) {
		futures.push_back(_ThreadPool->Push([this, i](int jobIndex)
			{
				while (GrowTree(i));
			}).share());
	}
	for (auto i : futures) i.wait();
	_TreeActivatedBranchNodesLists.clear();
}

void TreeUtilities::PlantSimulationSystem::CompleteTree(Entity treeEntity)
{
	for (size_t i = 0; i < _TreeActivatedBranchNodesLists.size(); i++) {
		if (treeEntity == _TreeActivatedBranchNodesLists[i].TreeEntity) {
			while(GrowTree(i));
		}
		_TreeActivatedBranchNodesLists.erase(_TreeActivatedBranchNodesLists.begin() + i);
	}
}

void TreeUtilities::PlantSimulationSystem::DestroyedTreeCheck()
{
	for (size_t i = 0; i < _TreeActivatedBranchNodesLists.size(); i++) {
		if (_TreeActivatedBranchNodesLists[i].TreeEntity.IsDeleted()) _TreeActivatedBranchNodesLists.erase(_TreeActivatedBranchNodesLists.begin() + i);
		i--;
	}
}

void TreeUtilities::PlantSimulationSystem::GrowTree(Entity treeEntity)
{
	for (size_t i = 0; i < _TreeActivatedBranchNodesLists.size(); i++) {
		if (treeEntity == _TreeActivatedBranchNodesLists[i].TreeEntity) {
			GrowTree(i);
		}
	}
}

void TreeUtilities::PlantSimulationSystem::OnCreate()
{
	Enable();
}

void TreeUtilities::PlantSimulationSystem::OnDestroy()
{
}

void TreeUtilities::PlantSimulationSystem::Update()
{
}

void TreeUtilities::PlantSimulationSystem::FixedUpdate()
{
	//GrowAllTrees();
}
Entity TreeUtilities::PlantSimulationSystem::CreateTree(TreeParameters treeParameters, TreeColor color, glm::vec3 position, bool enabled)
{
	auto treeEntity = TreeManager::CreateTree();
	Entity branchNodeEntity = TreeManager::CreateBranchNode(EntityManager::GetComponentData<TreeIndex>(treeEntity), treeEntity);
	auto budEntity = TreeManager::CreateBudForBranchNode(EntityManager::GetComponentData<TreeIndex>(treeEntity), branchNodeEntity);
#pragma region Position & Style
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = glm::vec3(1.0f);
	Rotation r;
	r.Value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
	EntityManager::SetComponentData(treeEntity, t);
	EntityManager::SetComponentData(treeEntity, s);
	EntityManager::SetComponentData(treeEntity, color);

	EntityManager::SetComponentData(branchNodeEntity, t);
	EntityManager::SetComponentData(branchNodeEntity, s);
	EntityManager::SetComponentData(branchNodeEntity, r);

	EntityManager::SetComponentData(budEntity, t);
	EntityManager::SetComponentData(budEntity, s);
	EntityManager::SetComponentData(budEntity, r);
#pragma endregion
	TreeAge age;
	age.Value = 0;
	age.Enable = enabled;

	BudInfo budInfo;
	budInfo.StartAge = 0;
	budInfo.Inhibitor = 0;
	budInfo.Type = BudTypes::APICAL;
	budInfo.Searching = true;

	BranchNodeInfo branchNodeInfo;
	branchNodeInfo.ApicalBudExist = true;
	branchNodeInfo.Level = 0;

	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(treeEntity);
#pragma region Prepare info
	treeInfo.MaxBranchingDepth = 3;
	treeInfo.Height = 0;
	treeInfo.ActiveLength = 0;
	int timeOff = 4;
	treeInfo.ApicalDominanceTimeVal->resize(treeParameters.Age + timeOff);
	treeInfo.GravitropismLevelVal->resize(treeParameters.Age + timeOff);
	for (size_t t = 0; t < treeParameters.Age + timeOff; t++) {
		treeInfo.ApicalDominanceTimeVal->at(t) = glm::pow(treeParameters.ApicalDominanceAgeFactor, t);
		treeInfo.GravitropismLevelVal->at(t) = treeParameters.GravitropismBase + t * treeParameters.GravitropismLevelFactor;
	}
#pragma endregion

	EntityManager::SetComponentData(branchNodeEntity, branchNodeInfo);
	EntityManager::SetComponentData(budEntity, budInfo);
	EntityManager::SetComponentData(treeEntity, treeParameters);
	EntityManager::SetComponentData(treeEntity, treeInfo);
	EntityManager::SetComponentData(treeEntity, age);
#pragma region Add to grow list
	BranchNodesCollection tab;
	tab.TreeEntity = treeEntity;
	BranchNode branchNode;
	branchNode.Activated = true;
	branchNode.BranchNodeEntity = branchNodeEntity;
	tab.BranchNodes.push_back(branchNode);
	_TreeActivatedBranchNodesLists.push_back(tab);
#pragma endregion

	CompleteTree(treeEntity);
	return treeEntity;
}
#pragma endregion

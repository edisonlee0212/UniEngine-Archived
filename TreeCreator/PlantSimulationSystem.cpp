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

void TreeUtilities::PlantSimulationSystem::GrowTree(size_t index)
{
#pragma region Collect tree data
	int startIndex = _TreeActivatedBranchNodesLists[index].BranchNodes.size();
	Entity tree = _TreeActivatedBranchNodesLists[index].TreeEntity;
	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(tree);
	TreeAge treeAge = EntityManager::GetComponentData<TreeAge>(tree);
	TreeParameters tps = EntityManager::GetComponentData<TreeParameters>(tree);
	TreeIndex treeIndex = EntityManager::GetComponentData<TreeIndex>(tree);
	if (treeAge.Value >= treeInfo.MaxTreeAge) {
		return;
	}
#pragma endregion
	bool growed = false;
#pragma region Grow branch nodes in reverse order of the tree.
	for (int selectedBranchNodeIndex = startIndex - 1; selectedBranchNodeIndex >= 0; selectedBranchNodeIndex--) {
#pragma region Collect branch node Data
		BranchNode b = _TreeActivatedBranchNodesLists[index].BranchNodes[selectedBranchNodeIndex];
		Entity branchNode = b.BranchNodeEntity;
		BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
		Activated branchActivated = EntityManager::GetComponentData<Activated>(branchNode);
		if (!branchActivated.Value) continue;
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
		bool branchGrowed = false;
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
				if (treeInfo.ApicalControlTimeVal->at(treeAge.Value) < 1) {
					apicalControl = treeInfo.ApicalControlTimeLevelVal->at(treeAge.Value)[treeInfo.MaxTreeAge - level + 1];
				}
				else {
					apicalControl = treeInfo.ApicalControlTimeLevelVal->at(treeAge.Value)[level];
				}
				float distanceToGrow = apicalControl * tps.ResourceToGrow;
				int internodesToGrow = (int)glm::floor(distanceToGrow + 0.5f);
				if (internodesToGrow != 0) {
					growSucceed = true;
				}
#pragma endregion
#pragma region Grow new shoot.
				if (growSucceed) {
					float internodeLength = distanceToGrow / (float)internodesToGrow;
					internodeLength *= tps.InternodeLengthBase * glm::pow(tps.InternodeLengthAgeFactor, treeAge.Value);
					int level = branchNodeInfo.Level;
					if (budInfo.Type == BudTypes::LATERAL) level++;
					Entity prevBranchNode = branchNode;
					Translation prevBranchNodeTranslation = EntityManager::GetComponentData<Translation>(branchNode);
					Rotation prevBranchNodeRotation = EntityManager::GetComponentData<Rotation>(branchNode);
					Scale prevBranchNodeScale = EntityManager::GetComponentData<Scale>(branchNode);
					Rotation baseBudRotation = budRotation;
					
					for (int selectedNewNodeIndex = 0; selectedNewNodeIndex < internodesToGrow; selectedNewNodeIndex++) {
						Translation newBranchNodeTranslation = Translation();
						Rotation newBranchNodeRotation = Rotation();
						Scale newBranchNodeScale = Scale();
#pragma region Calculate new node transform
						if (selectedNewNodeIndex == 0) {
							newBranchNodeRotation.Value = baseBudRotation.Value;
						}
						else {
							newBranchNodeRotation = prevBranchNodeRotation;
						}
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
						newBranchNodeInfo.ParentInhibitorFactor = glm::pow(tps.ApicalDominanceDistanceFactor, newBranchNodeInfo.DistanceToParent);
						newBranchNodeInfo.DesiredBranchDirection = newBranchNodeRotation.Value * glm::vec3(0, 0, -1);
						treeInfo.ActiveLength += newBranchNodeInfo.DistanceToParent;
#pragma region Generate buds for branch node.
						glm::quat prevBudRotation = baseBudRotation.Value;
						for (int selectedNewBudIndex = 0; selectedNewBudIndex < tps.LateralBudNumber; selectedNewBudIndex++) {
							Entity newBud = TreeManager::CreateBudForBranchNode(treeIndex, newBranchNode);
							BudInfo newBudInfo = EntityManager::GetComponentData<BudInfo>(newBud);
							Translation newBudTranslation = Translation();
							newBudTranslation.Value = prevBranchNodeTranslation.Value + (newBranchNodeTranslation.Value - prevBranchNodeTranslation.Value) / (float)tps.LateralBudNumber * (float)(selectedBudIndex + 1);
							Rotation newBudRotation;
							Scale newBudScale = Scale();
							newBudScale.Value = prevBranchNodeScale.Value + (newBranchNodeScale.Value - prevBranchNodeScale.Value) / (float)tps.LateralBudNumber * (float)(selectedBudIndex + 1);
#pragma region Vary bud direction
							//Rotate variance angle by random axis.
							prevBudRotation = glm::rotate(prevBudRotation, glm::radians(glm::linearRand(0.0f, tps.VarianceApicalAngle)), glm::normalize(glm::vec3(glm::linearRand(-1, 1), glm::linearRand(-1, 1), glm::linearRand(-1, 1))));
#pragma endregion
							newBudRotation.Value = prevBudRotation;
							glm::vec3 front = newBudRotation.Value * glm::vec3(0, 0, -1);
							glm::vec3 up = newBudRotation.Value * glm::vec3(0, 1, 0);
							up = glm::rotate(up,
								glm::radians(tps.MeanRollAngle + tps.VarianceRollAngle * glm::linearRand(-1, 1)), front);
							newBudRotation.Value = glm::quatLookAt(front, up);
							prevBudRotation = newBudRotation.Value;
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
							if (selectedBranchNodeIndex == internodesToGrow - 1 && selectedNewBudIndex == tps.LateralBudNumber - 1) {
								baseBudRotation = newBudRotation;
							}
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
						prevBranchNodeRotation = newBranchNodeRotation;
						prevBranchNodeScale = newBranchNodeScale;
						prevBranchNodeRotation = newBranchNodeRotation;
					}
#pragma region Deactivate current bud since we formed a new shoot from this bud.
					budRemoved = true;
					growed = true;
					DeactivateBud(bud, branchNode, &budInfo, &branchNodeInfo);
#pragma endregion
#pragma region Add inhibitor to this branchnode.
					float localInhibitor = 0;
					if (treeInfo.MaxTreeAge <= 1) localInhibitor += tps.ApicalDominanceBase;
					else {
						localInhibitor += tps.ApicalDominanceBase * treeInfo.ApicalControlTimeVal->at(treeAge.Value);
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
}

Entity TreeUtilities::PlantSimulationSystem::CreateTree(TreeColor color, glm::vec3 position, bool enabled)
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

	TreeParameters tps = TreeParameters();

	tps.LateralBudNumber = 4;
	tps.VarianceApicalAngle = 38;
	tps.MeanBranchingAngle = 38;
	tps.VarianceApicalAngle = 2;
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
	tps.InternodeLengthBase = 1.02f;
	tps.InternodeLengthAgeFactor = 0.97f;
	tps.ApicalControlBase = 2.4f;
	tps.ApicalControlAgeFactor = 0.85f;
	tps.Phototropism = 0.29f;
	tps.GravitropismBase = 0.61f;
	tps.PruningFactor = 0.05;
	tps.LowBranchPruningFactor = 1.3f;
	tps.GravityBendingStrength = 0.73f;
	tps.GravityBendingAngleFactor = 0.05f;

	tps.ResourceToGrow = 3.25;

	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(treeEntity);
#pragma region Prepare info
	treeInfo.MaxTreeAge = 6;
	if (tps.ResourceToGrow > 1.0) treeInfo.InitResourcesFactor = 1.1f;
	else treeInfo.InitResourcesFactor = 1.0 / tps.ResourceToGrow;
	treeInfo.MaxLeafClusterDepth = glm::floor(3.0 * tps.ResourceToGrow + 0.5);
	treeInfo.MaxBranchingDepth = 3;
	treeInfo.Height = 0;
	treeInfo.ActiveLength = 0;
	int timeOff = 4;
	treeInfo.ApicalControlTimeLevelVal->resize(treeInfo.MaxTreeAge + timeOff);
	treeInfo.ApicalDominanceTimeVal->resize(treeInfo.MaxTreeAge + timeOff);
	treeInfo.GravitropismLevelVal->resize(treeInfo.MaxTreeAge + timeOff);
	treeInfo.ApicalControlTimeVal->resize(treeInfo.MaxTreeAge + timeOff);
	for (size_t t = 0; t < treeInfo.MaxTreeAge + timeOff; t++) {
		treeInfo.ApicalControlTimeVal->at(t) = tps.ApicalControlBase * glm::pow(tps.ApicalControlAgeFactor, t);
		treeInfo.ApicalDominanceTimeVal->at(t) = glm::pow(tps.ApicalDominanceAgeFactor, t);
		treeInfo.GravitropismLevelVal->at(t) = tps.GravitropismBase + t * tps.GravitropismLevelFactor;
	}
	for (size_t t = 0; t < treeInfo.MaxTreeAge + timeOff; t++) {
		treeInfo.ApicalControlTimeLevelVal->at(t).resize(treeInfo.MaxTreeAge + timeOff);
		float ac0 = treeInfo.ApicalControlTimeVal->at(t);
		float accAccum = 1;
		for (int level = 0; level < treeInfo.MaxTreeAge + timeOff; ++level) {
			int levelSq = level * level;
			//compute the apical control
			if (ac0 >= 1) {
				float accF = 1;
				if (tps.Version > 1 && level > 0) {
					accF = (1.0 + (ac0 - 1.0) * glm::pow(tps.ApicalControlLevelFactor, level) * glm::pow(tps.ApicalControlLevelQuadFactor, levelSq));
					accAccum *= accF;
				}
				treeInfo.ApicalControlTimeLevelVal->at(t)[level] = 1.0 / accAccum;
				if (tps.Version == 1) {
					if (level == 0) {
						accAccum = ac0;
					}
					else
					{
						accAccum *= (1.0 + (ac0 - 1.0) * glm::pow(tps.ApicalControlLevelFactor, level));
					}
				}
			}
			else {
				//ac0 < 0
				// levels are inverted here but do not deal with it here
				if (tps.Version > 1 && level > 0) {
					accAccum *= (1.0 - (1.0 - ac0) * glm::pow(tps.ApicalControlLevelFactor, level) * glm::pow(tps.ApicalControlLevelQuadFactor, levelSq));
					if (accAccum < 0) accAccum = 0;
				}
				treeInfo.ApicalControlTimeLevelVal->at(t)[level] = accAccum;
				if (tps.Version == 1) {
					if (level == 0) {
						accAccum = ac0;
					}
					else
					{
						accAccum *= (1.0 - (1.0 - ac0) * glm::pow(tps.ApicalControlLevelFactor, level));
						if (accAccum < 0) accAccum = 0;
					}
				}
			}
		}
	}
#pragma endregion

	EntityManager::SetComponentData(branchNodeEntity, branchNodeInfo);
	EntityManager::SetComponentData(budEntity, budInfo);
	EntityManager::SetComponentData(treeEntity, tps);
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
	return treeEntity;
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
	GrowAllTrees();
}
#pragma endregion

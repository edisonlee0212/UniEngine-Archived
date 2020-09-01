#include "PlantSimulationSystem.h"

#include <gtx/matrix_decompose.hpp>

void TreeUtilities::PlantSimulationSystem::DrawGUI()
{

}


bool TreeUtilities::PlantSimulationSystem::GrowTree(Entity tree)
{
#pragma region Collect tree data
	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(tree);
	TreeAge treeAge = EntityManager::GetComponentData<TreeAge>(tree);
	TreeParameters treeParameters = EntityManager::GetComponentData<TreeParameters>(tree);
	TreeIndex treeIndex = EntityManager::GetComponentData<TreeIndex>(tree);
#pragma endregion
	if (treeAge.Value >= treeParameters.Age) {
		return false;
	}
#pragma region Prepare info
	treeInfo.MaxBranchingDepth = 3;
	treeInfo.Height = 0;
	treeInfo.ActiveLength = 0;
	int timeOff = 4;
	treeInfo.ApicalDominanceTimeVal->resize(treeParameters.Age + timeOff);
	treeInfo.GravitropismLevelVal->resize(treeParameters.Age + timeOff);
	treeInfo.GravitropismLevelVal->resize(treeParameters.Age + timeOff);
	treeInfo.ApicalControlTimeVal->resize(treeParameters.Age + timeOff);
	treeInfo.ApicalControlTimeLevelVal->resize(treeParameters.Age + timeOff);
	for (size_t t = 0; t < treeParameters.Age + timeOff; t++) {
		treeInfo.ApicalDominanceTimeVal->at(t) = glm::pow(treeParameters.ApicalDominanceAgeFactor, t);
		treeInfo.GravitropismLevelVal->at(t) = treeParameters.GravitropismBase + t * treeParameters.GravitropismLevelFactor;
		treeInfo.ApicalControlTimeVal->at(t) = treeParameters.ApicalControl * glm::pow(treeParameters.ApicalControlAgeDescFactor, t);

		treeInfo.ApicalControlTimeLevelVal->at(t).resize(treeParameters.Age + timeOff);
		float baseApicalControlVal = treeInfo.ApicalControlTimeVal->at(t);
		treeInfo.ApicalControlTimeLevelVal->at(t).at(0) = 1.0f;
		float currentVal = 1;
		for (size_t level = 1; level < treeParameters.Age + timeOff; level++) {
			if (baseApicalControlVal >= 1) {
				currentVal *= 1.0f + (baseApicalControlVal - 1.0f) * glm::pow(treeParameters.ApicalControlLevelFactor, level);
				treeInfo.ApicalControlTimeLevelVal->at(t).at(level) = 1.0f / currentVal;
			}
			else {
				currentVal *= 1.0f - (1.0f - baseApicalControlVal) * glm::pow(treeParameters.ApicalControlLevelFactor, level);
				treeInfo.ApicalControlTimeLevelVal->at(t).at(level) = currentVal;
			}
		}
	}
#pragma endregion
#pragma region Update branch structure information
	Entity rootBranchNode = EntityManager::GetChildren(tree).at(0);
	UpdateBranchNodeLength(rootBranchNode);
	BranchNodeInfo tempBNInfo = EntityManager::GetComponentData<BranchNodeInfo>(rootBranchNode);
	tempBNInfo.Level = 0;
	tempBNInfo.MaxActivatedChildLevel = 0;
	tempBNInfo.DistanceToBranchStart = 0;
	EntityManager::SetComponentData(rootBranchNode, tempBNInfo);
	UpdateBranchNodeActivatedLevel(rootBranchNode);
#pragma endregion
	bool idle = GrowShoots(rootBranchNode, treeInfo, treeAge, treeParameters, treeIndex);
	UpdateBranchNodeMeanData(rootBranchNode, treeAge.Value);
	treeAge.Value++;
	EntityManager::SetComponentData(tree, treeAge);
	EntityManager::SetComponentData(tree, treeInfo);
	if (!idle) {
		ComputeSagging(rootBranchNode, treeParameters);
		
		//UpdateBranchNodeLevel(rootBranchNode);
		//ComputeLight();
		UpdateBranchNodeResource(rootBranchNode, treeParameters, treeAge);
		UpdateBranchNodeResourceAllocation(rootBranchNode);

		EvaluatePruning(rootBranchNode, treeParameters, treeAge, treeInfo);
		EntityManager::SetComponentData(tree, treeInfo);
	}
	return idle;
}

#pragma region Helpers
inline float TreeUtilities::PlantSimulationSystem::GetApicalControl(TreeInfo& treeInfo, BranchNodeInfo& branchNodeInfo, TreeParameters& treeParameters, TreeAge& treeAge, int level)
{
	float apicalControl = treeParameters.ApicalControl * glm::pow(treeParameters.ApicalControlAgeDescFactor, treeAge.Value);
	if (treeInfo.ApicalControlTimeVal->at(treeAge.Value) < 1.0f) {
		int reversedLevel = branchNodeInfo.MaxActivatedChildLevel - level + 1;
		return treeInfo.ApicalControlTimeLevelVal->at(treeAge.Value)[reversedLevel];
	}
	else {
		return treeInfo.ApicalControlTimeLevelVal->at(treeAge.Value)[level];
	}

	return 1.0f;
}

void TreeUtilities::PlantSimulationSystem::CompleteAllTrees()
{

}

void TreeUtilities::PlantSimulationSystem::CompleteTree(Entity treeEntity)
{
	while (GrowTree(treeEntity));
	TreeManager::GenerateLeavesForTree(treeEntity);
}

void TreeUtilities::PlantSimulationSystem::UpdateBranchNodeLength(Entity& branchNode)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	branchNodeInfo.DistanceToBranchEnd = 0;
	branchNodeInfo.TotalDistanceToBranchEnd = 0;
	if (branchNodeInfo.Pruned) EntityManager::SetComponentData(branchNode, branchNodeInfo);
	float totalChildW = 0;
	float totalChildWSq = 0;
	EntityManager::ForEachChild(branchNode, [this, &branchNodeInfo](Entity child) {
		UpdateBranchNodeLength(child);
		BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
		float d = childNodeInfo.DistanceToBranchEnd + childNodeInfo.DistanceToParent;
		branchNodeInfo.TotalDistanceToBranchEnd += childNodeInfo.DistanceToParent + childNodeInfo.TotalDistanceToBranchEnd;
		if (d > branchNodeInfo.DistanceToBranchEnd) branchNodeInfo.DistanceToBranchEnd = d;
		});
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
}

void TreeUtilities::PlantSimulationSystem::UpdateBranchNodeActivatedLevel(Entity& branchNode)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	if (branchNodeInfo.Pruned) EntityManager::SetComponentData(branchNode, branchNodeInfo);
	// go through node children and update their level accordingly
	float maxChildLength = 0;
	Entity maxChild;
	EntityManager::ForEachChild(branchNode, [this, &branchNodeInfo, &maxChild, &maxChildLength](Entity child) {
		BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
		if (branchNodeInfo.Pruned) return;
		float d = childNodeInfo.TotalDistanceToBranchEnd + childNodeInfo.DistanceToParent;
		if (d > maxChildLength) {
			maxChildLength = d;
			maxChild = child;
		}
		});
	int maxChildLevel = branchNodeInfo.Level;

	EntityManager::ForEachChild(branchNode, [this, &branchNodeInfo, &maxChild](Entity child)
		{
			BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
			if (branchNodeInfo.Pruned || child.Index == maxChild.Index) return;
			childNodeInfo.DistanceToBranchStart = childNodeInfo.DistanceToParent;
			childNodeInfo.Level = branchNodeInfo.Level + 1;
			childNodeInfo.MaxActivatedChildLevel = childNodeInfo.Level;
			childNodeInfo.IsApical = false;
			EntityManager::SetComponentData(child, childNodeInfo);
			UpdateBranchNodeActivatedLevel(child);
			childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
			if (childNodeInfo.MaxActivatedChildLevel > branchNodeInfo.MaxActivatedChildLevel) branchNodeInfo.MaxActivatedChildLevel = childNodeInfo.MaxActivatedChildLevel;
		}
	);
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
	if (maxChild.Index != 0) {
		BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(maxChild);
		childNodeInfo.DistanceToBranchStart = branchNodeInfo.DistanceToBranchStart + childNodeInfo.DistanceToParent;
		childNodeInfo.Level = branchNodeInfo.Level;
		childNodeInfo.MaxActivatedChildLevel = branchNodeInfo.MaxActivatedChildLevel;
		childNodeInfo.IsApical = true;
		EntityManager::SetComponentData(maxChild, childNodeInfo);
		UpdateBranchNodeActivatedLevel(maxChild);
	}
}

void TreeUtilities::PlantSimulationSystem::UpdateBranchNodeLevel(Entity& branchNode)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	EntityManager::ForEachChild(branchNode, [this, &branchNodeInfo](Entity child)
		{
			BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
			if (branchNodeInfo.MaxChildLevel < childNodeInfo.MaxChildLevel) {
				branchNodeInfo.MaxChildLevel = childNodeInfo.MaxChildLevel;
			}
			else if (branchNodeInfo.MaxChildLevel < childNodeInfo.Level) {
				branchNodeInfo.MaxChildLevel = childNodeInfo.Level;
			}
		}
	);
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
}

void TreeUtilities::PlantSimulationSystem::UpdateBranchNodeMeanData(Entity& branchNode, unsigned treeAge)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	branchNodeInfo.DistanceToBranchEnd = 0;
	branchNodeInfo.MeanW = 0;
	branchNodeInfo.NumValidChild = 0;
	branchNodeInfo.ChildBranchesMean = glm::vec3(0.0f);
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
	if (branchNodeInfo.Pruned) return;
	float totalChildW = 0;
	float totalChildWSq = 0;
	EntityManager::ForEachChild(branchNode, [this, treeAge, &branchNodeInfo, &totalChildW, &totalChildWSq](Entity child)
		{
			UpdateBranchNodeMeanData(child, treeAge);
			BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
			float d = childNodeInfo.DistanceToBranchEnd + childNodeInfo.DistanceToParent;
			if (d > branchNodeInfo.DistanceToBranchEnd)branchNodeInfo.DistanceToBranchEnd = d;
			float cL = childNodeInfo.DistanceToParent;
			branchNodeInfo.NumValidChild += 1;
			float w = childNodeInfo.MeanW;
			branchNodeInfo.ChildBranchesMean += w * childNodeInfo.ChildBranchesMean;
			totalChildW += w;
			totalChildWSq += w * w;
		});
	float nodeWFactor = 1;
	float locW = 1.0f + glm::max((int)treeAge - branchNodeInfo.Level, 0);
	branchNodeInfo.ChildBranchesMean += EntityManager::GetComponentData<Translation>(branchNode).Value * branchNodeInfo.DistanceToParent * locW;
	branchNodeInfo.MeanW = locW * branchNodeInfo.DistanceToParent + totalChildW;
	if (branchNodeInfo.MeanW > 0) {
		branchNodeInfo.ChildBranchesMean = branchNodeInfo.ChildBranchesMean / branchNodeInfo.MeanW;
	}
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
}

void TreeUtilities::PlantSimulationSystem::UpdateLocalTransform(Entity& branchNode, Translation& parentTranslation, Rotation& parentRotation, Scale& parentScale)
{
	Translation t = EntityManager::GetComponentData<Translation>(branchNode);
	Rotation r = EntityManager::GetComponentData<Rotation>(branchNode);
	Scale s = EntityManager::GetComponentData<Scale>(branchNode);

	LocalTranslation lt;
	LocalRotation lr;
	LocalScale ls;
	EntityManager::ForEachChild(branchNode, [this, &t, &r, &s](Entity child)
		{
			UpdateLocalTransform(child, t, r, s);
		}
	);
}

bool TreeUtilities::PlantSimulationSystem::GrowShoots(Entity& branchNode, TreeInfo& treeInfo, TreeAge& treeAge, TreeParameters& treeParameters, TreeIndex& treeIndex)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	if (branchNodeInfo.Pruned) return false;
#pragma region Grow child and collect Inhibitor
	branchNodeInfo.Inhibitor = 0;
	bool ret = false;
	EntityManager::ForEachChild(branchNode, [&ret, this, &branchNodeInfo, &treeInfo, &treeAge, &treeParameters, &treeIndex](Entity childNode)
		{
			if (GrowShoots(childNode, treeInfo, treeAge, treeParameters, treeIndex)) ret = true;
			auto childBranchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(childNode);
			branchNodeInfo.Inhibitor += childBranchNodeInfo.Inhibitor * childBranchNodeInfo.ParentInhibitorFactor;
		}
	);
	if (branchNodeInfo.ActivatedBudsAmount == 0) return ret;
#pragma endregion
	BranchNodeIllumination branchNodeIllumination = EntityManager::GetComponentData<BranchNodeIllumination>(branchNode);
	BranchNodeBudsList budsList = EntityManager::GetComponentData<BranchNodeBudsList>(branchNode);
	BranchNodeIndex branchNodeIndex = EntityManager::GetComponentData<BranchNodeIndex>(branchNode);
	float lateralInhibitorToAdd = 0;
	for (auto& bud : *budsList.Buds) {
		if (!bud.IsActive) continue;
#pragma region Bud kill probability
		float budKillProbability = 0;
		if (bud.IsApical) {
			budKillProbability = EntityManager::HasComponentData<TreeInfo>(EntityManager::GetParent(branchNode)) ? 0 : treeParameters.ApicalBudExtintionRate;
		}
		else {
			budKillProbability = treeParameters.LateralBudEntintionRate;
		}
		if (glm::linearRand(0.0f, 1.0f) < budKillProbability) {
			DeactivateBud(branchNodeInfo, bud);
			continue;
		}
#pragma endregion
#pragma region Flush check
		//compute probability that the given bud can grow
		float budGrowProbability = 1;
		// first take into account the apical dominance
		if (branchNodeInfo.Inhibitor > 0) budGrowProbability *= glm::exp(-branchNodeInfo.Inhibitor);
		// now take into consideration the light on the bud
		if (branchNodeIllumination.Value < 1) {
			//budGrowProbability *= glm::pow(branchNodeIllumination.Value, bud.IsApical ? treeParameters.ApicalBudLightingFactor : treeParameters.LateralBudLightingFactor);
		}
		// now check whether the bud is going to flush or not
		bool flush = budGrowProbability > glm::linearRand(0.0f, 1.0f);
#pragma endregion
		bool growSucceed = false;
		if (flush) {
			bool isLateral = !(bud.IsApical && EntityManager::GetChildrenAmount(branchNode) == 0);
#pragma region Compute total grow distance and internodes amount.
			int level = branchNodeInfo.Level;
			if (isLateral) level++;
			float apicalControl = GetApicalControl(treeInfo, branchNodeInfo, treeParameters, treeAge, level);
			float distanceToGrow = treeParameters.GrowthRate * apicalControl;
			int internodesToGrow = glm::floor(distanceToGrow + 0.5f);
			if (internodesToGrow != 0) {
				growSucceed = true;
			}
#pragma endregion
#pragma region Grow new shoot
			if (growSucceed) {
				float internodeLength = distanceToGrow / (float)internodesToGrow;
				internodeLength *= treeParameters.InternodeLengthBase * glm::pow(treeParameters.InternodeLengthAgeFactor, treeAge.Value);
				int level = branchNodeInfo.Level;
				if (!bud.IsApical) {
					level++;
				}
				Entity prevBranchNode = branchNode;
				BranchNodeInfo prevBranchNodeInfo = branchNodeInfo;
				glm::vec3 prevEulerAngle = bud.EulerAngles;
				glm::mat4 templtw = EntityManager::GetComponentData<LocalToWorld>(branchNode).Value;
				glm::vec3 scale;
				glm::quat rotation;
				glm::vec3 translation;
				glm::vec3 skew;
				glm::vec4 perspective;
				glm::decompose(templtw, scale, rotation, translation, skew, perspective);
				Rotation prevBranchNodeRotation;
				prevBranchNodeRotation.Value = rotation;
#pragma region Create branch nodes
				for (int selectedNewNodeIndex = 0; selectedNewNodeIndex < internodesToGrow; selectedNewNodeIndex++) {
#pragma region Setup branch node
					Entity newBranchNode = TreeManager::CreateBranchNode(treeIndex, prevBranchNode);
					BranchNodeBudsList newBranchNodeBudList = EntityManager::GetComponentData<BranchNodeBudsList>(newBranchNode);
					BranchNodeInfo newBranchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(newBranchNode);
					newBranchNodeInfo.ApicalBudExist = true;
					newBranchNodeInfo.ActivatedBudsAmount = treeParameters.LateralBudNumber + 1;
					newBranchNodeInfo.DistanceToParent = internodeLength;
					newBranchNodeInfo.Level = level;
					newBranchNodeInfo.Pruned = false;
					newBranchNodeInfo.IsApical = prevBranchNodeInfo.IsApical;
					if (newBranchNodeInfo.IsApical) newBranchNodeInfo.Level = prevBranchNodeInfo.Level;
					else newBranchNodeInfo.Level = prevBranchNodeInfo.Level + 1;
					newBranchNodeInfo.MaxActivatedChildLevel = level;
					newBranchNodeInfo.ParentInhibitorFactor = glm::pow(treeParameters.ApicalDominanceDistanceFactor, newBranchNodeInfo.DistanceToParent);
					
#pragma endregion
#pragma region Transforms for branch node
					LocalTranslation lt;
					LocalRotation lr;
					lr.Value = glm::quat(prevEulerAngle);
#pragma region Roll branch node
					glm::vec3 rollAngles = glm::vec3(0.0f, 0.0f, glm::radians(treeParameters.MeanRollAngle + treeParameters.VarianceRollAngle * glm::linearRand(-1, 1)));
					lr.Value *= glm::quat(rollAngles);
#pragma endregion

#pragma region Apply phototropism and gravitropism
					float gravitropism = treeInfo.GravitropismLevelVal->at(newBranchNodeInfo.Level);
					Rotation globalRawRotation;
					globalRawRotation.Value = prevBranchNodeRotation.Value * lr.Value;
					glm::vec3 rawFront = globalRawRotation.Value * glm::vec3(0, 0, -1);
					glm::vec3 rawUp = globalRawRotation.Value * glm::vec3(0, 1, 0);
					rawFront += glm::vec3(0, -1, 0) * gravitropism;
					rawFront += glm::vec3(0, 1, 0) * treeParameters.Phototropism;
					rawFront = glm::normalize(rawFront);
					rawUp = glm::cross(glm::cross(rawFront, rawUp), rawFront);
					globalRawRotation.Value = glm::quatLookAt(rawFront, rawUp);
					lr.Value = glm::inverse(prevBranchNodeRotation.Value) * globalRawRotation.Value;
					prevBranchNodeRotation = globalRawRotation;
					//Store desired local rotation, if we want to sag by different value later.
					newBranchNodeInfo.DesiredLocalRotation = lr.Value;
#pragma endregion
					LocalScale ls;
					lt.Value = lr.Value * glm::vec3(0, 0, -1) * internodeLength;
					ls.Value = glm::vec3(1.0f);
#pragma endregion
					
					

					treeInfo.ActiveLength += newBranchNodeInfo.DistanceToParent;
#pragma region Create Apical Bud
					Bud newApicalBud;
					newApicalBud.EulerAngles = glm::vec3(glm::gaussRand(glm::vec2(0.0f), glm::vec2(glm::radians(treeParameters.VarianceApicalAngle / 2.0f))), 0.0f);
					newApicalBud.IsActive = true;
					newApicalBud.IsApical = true;
					newApicalBud.StartAge = treeAge.Value;
					newBranchNodeBudList.Buds->push_back(newApicalBud);
#pragma endregion
#pragma region Create Lateral Buds
					for (int selectedNewBudIndex = 0; selectedNewBudIndex < treeParameters.LateralBudNumber; selectedNewBudIndex++) {
						Bud newLateralBud;
						float rollAngle = 360.0f * (selectedNewBudIndex + 1) / treeParameters.LateralBudNumber + treeParameters.VarianceBranchingAngle * glm::linearRand(-1, 1);
						float branchAngle = treeParameters.MeanBranchingAngle + treeParameters.VarianceBranchingAngle * glm::gaussRand(0.0f, 0.5f);
						newLateralBud.EulerAngles = glm::vec3(glm::radians(branchAngle), 0.0f, glm::radians(rollAngle));
						newLateralBud.IsActive = true;
						newLateralBud.IsApical = false;
						newLateralBud.StartAge = treeAge.Value;
						newBranchNodeBudList.Buds->push_back(newLateralBud);
					}
#pragma endregion
					prevEulerAngle = newApicalBud.EulerAngles;
					prevBranchNode = newBranchNode;
					prevBranchNodeInfo = newBranchNodeInfo;
#pragma region Apply new branch node info
					EntityManager::SetComponentData(newBranchNode, lt);
					EntityManager::SetComponentData(newBranchNode, ls);
					EntityManager::SetComponentData(newBranchNode, lr);
					EntityManager::SetComponentData(newBranchNode, newBranchNodeBudList);
					EntityManager::SetComponentData(newBranchNode, newBranchNodeInfo);
#pragma endregion
				}
#pragma endregion
				DeactivateBud(branchNodeInfo, bud);
#pragma region Add inhibitor to this branchnode.
				float localInhibitor = 0;
				if (treeAge.Value <= 1) localInhibitor += treeParameters.ApicalDominanceBase;
				else {
					localInhibitor += treeParameters.ApicalDominanceBase * treeInfo.ApicalDominanceTimeVal->at(treeAge.Value);
				}
				if (bud.IsApical) {
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
#pragma region If the bud didnt flush then check whether we should remove it because of the old age.
		if(!growSucceed){
			int budAge = treeAge.Value - bud.StartAge;
			if (budAge > treeParameters.MaxBudAge) {
				DeactivateBud(branchNodeInfo, bud);
			}

		}
#pragma endregion
	}
	branchNodeInfo.Inhibitor += lateralInhibitorToAdd;
	return ret;
}

void TreeUtilities::PlantSimulationSystem::DeactivateBud(BranchNodeInfo& branchNodeInfo, Bud& bud)
{
	branchNodeInfo.ActivatedBudsAmount--;
	bud.IsActive = false;
	if (bud.IsApical) branchNodeInfo.ApicalBudExist = false;
}

void TreeUtilities::PlantSimulationSystem::ComputeSagging(Entity& branchNode, TreeParameters& treeParameters)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	if (branchNodeInfo.Pruned) return;
}

void TreeUtilities::PlantSimulationSystem::PruneBranchNode(Entity& branchNode, TreeInfo& treeInfo)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	branchNodeInfo.Pruned = true;
	treeInfo.ActiveLength -= branchNodeInfo.DistanceToParent;
	EntityManager::ForEachChild(branchNode, [this, &treeInfo](Entity child) 
		{
			PruneBranchNode(child, treeInfo);
		}
	);
}

void TreeUtilities::PlantSimulationSystem::EvaluatePruning(Entity& branchNode, TreeParameters& treeParameters, TreeAge& treeAge, TreeInfo& treeInfo)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	if (branchNodeInfo.Pruned) return;
	if (branchNodeInfo.Level == 0 && treeAge.Value < 3) return;
	if (branchNodeInfo.Level == 1 && !branchNodeInfo.IsApical) {
		float height = EntityManager::GetComponentData<LocalToWorld>(branchNode).Value[3].y;
		if (height < treeParameters.LowBranchPruningFactor && height < treeInfo.Height) {
			PruneBranchNode(branchNode, treeInfo);
			return;
		}
	}
	float normalL = branchNodeInfo.AccmulatedLength / treeParameters.InternodeLengthBase;
	float ratioScale = 1;
	float factor = ratioScale / glm::sqrt(branchNodeInfo.AccmulatedLength);
	//factor *= branchNodeInfo.AccmulatedLight;
	if (factor < treeParameters.PruningFactor) {
		PruneBranchNode(branchNode, treeInfo);
	}
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
}

void TreeUtilities::PlantSimulationSystem::UpdateBranchNodeResource(Entity& branchNode, TreeParameters& treeParameters, TreeAge& treeAge)
{
	BranchNodeInfo branchNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(branchNode);
	BranchNodeIllumination branchNodeIllumination = EntityManager::GetComponentData<BranchNodeIllumination>(branchNode);
	branchNodeInfo.AccmulatedLight = branchNodeIllumination.Value;
	branchNodeInfo.AccmulatedLength = branchNodeInfo.DistanceToParent;
	branchNodeInfo.AccmulatedActivatedBudsAmount = branchNodeInfo.ActivatedBudsAmount;
	branchNodeInfo.BranchEndNodeAmount = EntityManager::GetChildrenAmount(branchNode) == 0 ? 1 : 0;
	EntityManager::ForEachChild(branchNode, [this, &branchNodeInfo, &treeParameters, &treeAge](Entity child)
		{
			UpdateBranchNodeResource(child, treeParameters, treeAge);
			BranchNodeInfo childNodeInfo = EntityManager::GetComponentData<BranchNodeInfo>(child);
			branchNodeInfo.BranchEndNodeAmount += childNodeInfo.BranchEndNodeAmount;
			if (childNodeInfo.Pruned) return;
			branchNodeInfo.AccmulatedLight += childNodeInfo.AccmulatedLight;
			branchNodeInfo.AccmulatedActivatedBudsAmount += childNodeInfo.AccmulatedActivatedBudsAmount;
			branchNodeInfo.AccmulatedLength += childNodeInfo.AccmulatedLength;
		}
	);
	branchNodeInfo.Thickness = treeParameters.EndNodeThickness * branchNodeInfo.BranchEndNodeAmount * glm::pow(treeParameters.ThicknessControlFactor, treeAge.Value - branchNodeInfo.Level);
	
	EntityManager::SetComponentData(branchNode, branchNodeInfo);
}

void TreeUtilities::PlantSimulationSystem::UpdateBranchNodeResourceAllocation(Entity& branchNode)
{

}

void TreeUtilities::PlantSimulationSystem::OnCreate()
{
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();
	_LeafQuery = TreeManager::GetLeafQuery();
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
	std::vector<Entity> trees;
	_TreeQuery.ToEntityArray(&trees);
	for (const auto& tree : trees) {	
		GrowTree(tree);
		TreeManager::GetBranchNodeSystem()->RefreshConnections();
	}
	//GrowAllTrees();
}

Entity TreeUtilities::PlantSimulationSystem::CreateTree(TreeParameters treeParameters, TreeColor color, glm::vec3 position, bool enabled)
{
	auto treeEntity = TreeManager::CreateTree();
	Entity branchNodeEntity = TreeManager::CreateBranchNode(EntityManager::GetComponentData<TreeIndex>(treeEntity), treeEntity);
#pragma region Position & Style
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = glm::vec3(1.0f);
	Rotation r;
	r.Value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
	EntityManager::SetComponentData(treeEntity, t);
	EntityManager::SetComponentData(treeEntity, s);
	EntityManager::SetComponentData(treeEntity, r);
	EntityManager::SetComponentData(treeEntity, color);

	LocalTranslation lt;
	lt.Value = glm::vec3(0.0f);
	LocalScale ls;
	ls.Value = glm::vec3(1.0f);
	LocalRotation lr;
	lr.Value = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

	EntityManager::SetComponentData(branchNodeEntity, lt);
	EntityManager::SetComponentData(branchNodeEntity, ls);
	EntityManager::SetComponentData(branchNodeEntity, lr);

#pragma endregion
	TreeAge age;
	age.Value = 0;
	age.Enable = enabled;

	Bud bud;
	bud.EulerAngles = glm::vec3(0.0f);
	bud.IsActive = true;
	bud.IsApical = true;
	bud.StartAge = 0;

	BranchNodeBudsList list = EntityManager::GetComponentData<BranchNodeBudsList>(branchNodeEntity);
	list.Buds->push_back(bud);

	BranchNodeInfo branchNodeInfo;
	branchNodeInfo.ApicalBudExist = true;
	branchNodeInfo.Level = 0;
	branchNodeInfo.MaxActivatedChildLevel = 0;
	branchNodeInfo.ActivatedBudsAmount = 1;
	branchNodeInfo.Pruned = false;
	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(treeEntity);


	EntityManager::SetComponentData(branchNodeEntity, branchNodeInfo);
	EntityManager::SetComponentData(treeEntity, treeParameters);
	EntityManager::SetComponentData(treeEntity, treeInfo);
	EntityManager::SetComponentData(treeEntity, age);

	//CompleteTree(tree);
	return treeEntity;
}

Entity TreeUtilities::PlantSimulationSystem::CreateExampleTree(TreeColor color, glm::vec3 position, int index, bool enabled)
{
	TreeParameters tps = TreeParameters();
	switch (index)
	{
	case 1:
		tps.VarianceApicalAngle = 38;
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
		tps.GrowthRate = 0.98f;
		tps.InternodeLengthBase = 1.02f;
		tps.InternodeLengthAgeFactor = 0.97f;

		tps.ApicalControl = 2.4f;
		tps.ApicalControlAgeDescFactor = 0.85f;
		tps.ApicalControlLevelFactor = 1.0f;
		tps.Phototropism = 0.29f;
		tps.GravitropismBase = 0.061f;
		tps.PruningFactor = 0.05;
		tps.LowBranchPruningFactor = 1.3f;
		tps.GravityBendingStrength = 0.73f;
		tps.GravityBendingAngleFactor = 0.05f;
		tps.Age = 8;
		tps.EndNodeThickness = 0.005f;
		tps.ThicknessControlFactor = 0.9f;
		break;
	case 2:
		tps.VarianceApicalAngle = 0.42990970562500003;
		tps.LateralBudNumber = 2;
		tps.MeanBranchingAngle = 27.198200000000000;
		tps.VarianceBranchingAngle = 0.037388089600000000;
		tps.MeanRollAngle = 113.11000000000000;
		tps.VarianceRollAngle = 13.090141080900001;

		tps.ApicalBudExtintionRate = 0.99903945880000000;
		tps.LateralBudEntintionRate = 0.0062681600000000001;
		tps.ApicalBudLightingFactor = 0.099225700000000000;
		tps.LateralBudLightingFactor = 1.0005922199999999;
		tps.ApicalDominanceBase = 5.0524730000000000;
		tps.ApicalDominanceDistanceFactor = 0.37777800000000000;
		tps.ApicalDominanceAgeFactor = 0.44704700000000003;
		tps.GrowthRate = 1.3069500000000001;
		tps.InternodeLengthBase = 0.92382719999999996;
		tps.InternodeLengthAgeFactor = 0.95584000000000002;

		tps.ApicalControl = 0.93576000000000004;
		tps.ApicalControlAgeDescFactor = 0.91815700000000000;
		tps.ApicalControlLevelFactor = 1.0000000000000000;
		tps.Phototropism = 0.22445109999999999;
		tps.GravitropismBase = 0.039603199999999998;
		tps.PruningFactor = 0.43430900000000000;
		tps.LowBranchPruningFactor = 0.63922599999999996;
		tps.GravityBendingStrength = 0.05f;
		tps.GravityBendingAngleFactor = 0.05f;
		tps.Age = 9;
		tps.Gravity = 0.050594199999999999;
		tps.GravityMaxBending = 0.50084200000000001;
		tps.MaxBudAge = 8;
		tps.EndNodeThickness = 0.5f;
		tps.ThicknessControlFactor = 0.8f;
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
		tps.ApicalControlAgeDescFactor = 0.85f;
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
	/*case 2:
		tps.VarianceApicalAngle = 0;
		tps.LateralBudNumber = 2;
		tps.MeanBranchingAngle = 41;
		tps.VarianceBranchingAngle = 3;
		tps.MeanRollAngle = 87;
		tps.VarianceRollAngle = 2;

		tps.ApicalBudExtintionRate = 0;
		tps.LateralBudEntintionRate = 0.21f;
		tps.ApicalBudLightingFactor = 0.37f;
		tps.LateralBudLightingFactor = 1.05f;
		tps.ApicalDominanceBase = 0.37f;
		tps.ApicalDominanceDistanceFactor = 0.31f;
		tps.ApicalDominanceAgeFactor = 0.9;
		tps.GrowthRate = 1.9f;
		tps.InternodeLengthBase = 0.49f;
		tps.InternodeLengthAgeFactor = 0.98f;

		tps.ApicalControl = 0.27f;
		tps.ApicalControlAgeDescFactor = 0.9f;
		tps.ApicalControlLevelFactor = 0.9f;
		tps.Phototropism = 0.15f;
		tps.GravitropismBase = 0.17f;
		tps.PruningFactor = 0.82;
		tps.LowBranchPruningFactor = 2.83f;
		tps.GravityBendingStrength = 0.195f;
		tps.GravityBendingAngleFactor = 0.14f;
		tps.Age = 6;
		break;
	case 3:
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
		tps.InternodeLengthBase = 0.4f;
		tps.InternodeLengthAgeFactor = 0.96f;

		tps.ApicalControl = 6.2f;
		tps.ApicalControlAgeDescFactor = 0.9f;
		tps.ApicalControlLevelFactor = 1.0f;
		tps.Phototropism = 0.42f;
		tps.GravitropismBase = 0.43f;
		tps.PruningFactor = 0.12;
		tps.LowBranchPruningFactor = 1.25f;
		tps.GravityBendingStrength = 0.94f;
		tps.GravityBendingAngleFactor = 0.52f;
		tps.Age = 14;
		break;
	case 4:
		tps.VarianceApicalAngle = 5;
		tps.LateralBudNumber = 1;
		tps.MeanBranchingAngle = 45;
		tps.VarianceBranchingAngle = 5;
		tps.MeanRollAngle = 130;
		tps.VarianceRollAngle = 3;

		tps.ApicalBudExtintionRate = 0;
		tps.LateralBudEntintionRate = 0.01;
		tps.ApicalBudLightingFactor = 0.5;
		tps.LateralBudLightingFactor = 0.03f;
		tps.ApicalDominanceBase = 5.59f;
		tps.ApicalDominanceDistanceFactor = 0.5f;
		tps.ApicalDominanceAgeFactor = 0.979;
		tps.GrowthRate = 4.25f;
		tps.InternodeLengthBase = 0.55f;
		tps.InternodeLengthAgeFactor = 0.95f;

		tps.ApicalControl = 5.5f;
		tps.ApicalControlAgeDescFactor = 0.91f;
		tps.ApicalControlLevelFactor = 1.0f;
		tps.Phototropism = 0.05f;
		tps.GravitropismBase = -0.01f;
		tps.PruningFactor = 0.48;
		tps.LowBranchPruningFactor = 5.5f;
		tps.GravityBendingStrength = 0.09f;
		tps.GravityBendingAngleFactor = 0.89f;
		tps.Age = 28;
		break;
	case 5:
		tps.VarianceApicalAngle = 2;
		tps.LateralBudNumber = 6;
		tps.MeanBranchingAngle = 3;
		tps.VarianceBranchingAngle = 130;
		tps.MeanRollAngle = 10;
		tps.VarianceRollAngle = 0;

		tps.ApicalBudExtintionRate = 0.018;
		tps.LateralBudEntintionRate = 0.03;
		tps.ApicalBudLightingFactor = 0.21;
		tps.LateralBudLightingFactor = 0.5f;
		tps.ApicalDominanceBase = 0.55f;
		tps.ApicalDominanceDistanceFactor = 0.91f;
		tps.ApicalDominanceAgeFactor = 2.4;
		tps.GrowthRate = 0.7f;
		tps.InternodeLengthBase = 0.97f;
		tps.InternodeLengthAgeFactor = 5.5f;

		tps.ApicalControl = 0.92f;
		tps.ApicalControlAgeDescFactor = 0.05f;
		tps.ApicalControlLevelFactor = 1.0;
		tps.Phototropism = 0.15f;
		tps.GravitropismBase = 0.22f;
		tps.PruningFactor = 1.11;
		tps.LowBranchPruningFactor = 0.32f;
		tps.GravityBendingStrength = 0.12f;
		tps.GravityBendingAngleFactor = 0.78f;
		tps.Age = 4;
		break;
	case 6:
		break;
	case 7:
		tps.VarianceApicalAngle = 0;
		tps.LateralBudNumber = 6;
		tps.MeanBranchingAngle = 30;
		tps.VarianceBranchingAngle = 0;
		tps.MeanRollAngle = 60;
		tps.VarianceRollAngle = 0;

		tps.ApicalBudExtintionRate = 0;
		tps.LateralBudEntintionRate = 0;
		tps.ApicalBudLightingFactor = 0.5;
		tps.LateralBudLightingFactor = 0.03f;
		tps.ApicalDominanceBase = 6.0f;
		tps.ApicalDominanceDistanceFactor = 0.5f;
		tps.ApicalDominanceAgeFactor = 0.1;
		tps.GrowthRate = 4.0f;
		tps.InternodeLengthBase = 1.0f;
		tps.InternodeLengthAgeFactor = 0.50f;

		tps.ApicalControl = 5.5f;
		tps.ApicalControlAgeDescFactor = 0.8f;
		tps.ApicalControlLevelFactor = 0.8f;
		tps.Phototropism = 0.05f;
		tps.GravitropismBase = 0.48f;
		tps.PruningFactor = 0.05;
		tps.LowBranchPruningFactor = 5.5f;
		tps.GravityBendingStrength = 0.73f;
		tps.GravityBendingAngleFactor = 0.05f;
		tps.Age = 6;
		break;
		*/
	return CreateTree(tps, color, position);
}

#pragma endregion

#include "pch.h"
#include "TreeManager.h"
#include "LightEstimator.h"
#include <gtx/matrix_decompose.hpp>
using namespace TreeUtilities;

LightEstimator* TreeUtilities::TreeManager::_LightEstimator;

TreeSystem* TreeUtilities::TreeManager::_TreeSystem;
BranchNodeSystem* TreeUtilities::TreeManager::_BranchNodeSystem;
LeafSystem* TreeUtilities::TreeManager::_LeafSystem;

EntityArchetype TreeUtilities::TreeManager::_BranchNodeArchetype;
EntityArchetype TreeUtilities::TreeManager::_LeafArchetype;
EntityArchetype TreeUtilities::TreeManager::_TreeArchetype;

EntityQuery TreeUtilities::TreeManager::_TreeQuery;
EntityQuery TreeUtilities::TreeManager::_BranchNodeQuery;
EntityQuery TreeUtilities::TreeManager::_LeafQuery;

TreeIndex TreeUtilities::TreeManager::_TreeIndex;
BranchNodeIndex TreeUtilities::TreeManager::_BranchNodeIndex;
LeafIndex TreeUtilities::TreeManager::_LeafIndex;

bool TreeUtilities::TreeManager::_Ready;
#pragma region Helpers
void TreeUtilities::TreeManager::SimpleMeshGenerator(Entity& branchNode, std::vector<Vertex>& vertices, std::vector<unsigned>& indices, float resolution)
{
	auto list = EntityManager::GetComponentData<BranchNodeRingList>(branchNode);
	auto rings = list.Rings;
	int step = (rings->front().StartRadius / resolution);
	if (step < 4) step = 4;
	if (step % 2 != 0) step++;
	float angleStep = 360.0f / (float)(step);
	int vertexIndex = vertices.size();
	Vertex archetype;
	float textureXstep = 1.0f / step * 4.0f;
	for (int i = 0; i < step; i++) {
		archetype.Position = rings->at(0).GetPoint(list.NormalDir, angleStep * i, true);
		float x = i < (step / 2) ? i * textureXstep : (step - i) * textureXstep;
		archetype.TexCoords0 = glm::vec2(x, 0.0f);
		vertices.push_back(archetype);
	}
	int ringSize = rings->size();
	float textureYstep = 1.0f / ringSize * 2.0f;
	for (int ringIndex = 0; ringIndex < ringSize; ringIndex++) {
		for (int i = 0; i < step; i++) {
			archetype.Position = rings->at(ringIndex).GetPoint(list.NormalDir, angleStep * i, false);
			float x = i < (step / 2) ? i * textureXstep : (step - i) * textureXstep;
			float y = ringIndex < (ringSize / 2) ? (ringIndex + 1) * textureYstep : (ringSize - ringIndex - 1) * textureYstep;
			archetype.TexCoords0 = glm::vec2(x, y);
			vertices.push_back(archetype);
		}
		for (int i = 0; i < step - 1; i++) {
			//Down triangle
			indices.push_back(vertexIndex + ringIndex * step + i);
			indices.push_back(vertexIndex + ringIndex * step + i + 1);
			indices.push_back(vertexIndex + (ringIndex + 1) * step + i);
			//Up triangle
			indices.push_back(vertexIndex + (ringIndex + 1) * step + i + 1);
			indices.push_back(vertexIndex + (ringIndex + 1) * step + i);
			indices.push_back(vertexIndex + ringIndex * step + i + 1);
		}
		//Down triangle
		indices.push_back(vertexIndex + ringIndex * step + step - 1);
		indices.push_back(vertexIndex + ringIndex * step);
		indices.push_back(vertexIndex + (ringIndex + 1) * step + step - 1);
		//Up triangle
		indices.push_back(vertexIndex + (ringIndex + 1) * step);
		indices.push_back(vertexIndex + (ringIndex + 1) * step + step - 1);
		indices.push_back(vertexIndex + ringIndex * step);
	}
	/*
	for (int i = 0; i < step - 1; i++) {
		//Down triangle
		indices.push_back(vertexIndex + ringSize * step + i);
		indices.push_back(vertexIndex + ringSize * step + i + 1);
		indices.push_back(vertexIndex + (ringSize + 1) * step + i);
		//Up triangle
		indices.push_back(vertexIndex + (ringSize + 1) * step + i + 1);
		indices.push_back(vertexIndex + (ringSize + 1) * step + i);
		indices.push_back(vertexIndex + ringSize * step + i + 1);
	}
	//Down triangle
	indices.push_back(vertexIndex + ringSize * step + step - 1);
	indices.push_back(vertexIndex + ringSize * step);
	indices.push_back(vertexIndex + (ringSize + 1) * step + step - 1);
	//Up triangle
	indices.push_back(vertexIndex + (ringSize + 1) * step);
	indices.push_back(vertexIndex + (ringSize + 1) * step + step - 1);
	indices.push_back(vertexIndex + ringSize * step);
	*/
	/*
	if (EntityManager::GetChildrenAmount(branchNode) == 0 && !rings->empty()) {
		std::vector<Vertex> endRing;
		float angleStep = 360.0f / (float)(step);
		Vertex archetype;
		for (unsigned i = 0; i < step; i++) {
			archetype.Position = rings->back().GetPoint(list.NormalDir, angleStep * i, false);
			endRing.push_back(archetype);
		}
		Vertex center = Vertex();
		center.Position = rings->back().EndPosition;
		center.TexCoords0 = glm::vec2(1.0f, 1.0f);
		for (unsigned i = 0; i < step - 1; i++) {
			endRing[i].TexCoords0 = glm::vec2(0.0f, 0.0f);
			endRing[i + 1].TexCoords0 = glm::vec2(0.0f, 1.0f);
			vertices.push_back(endRing[i]);
			vertices.push_back(endRing[i + 1]);
			vertices.push_back(center);
		}
		vertices.push_back(endRing[step - 1]);
		vertices.push_back(endRing[0]);
		vertices.push_back(center);
	}
	*/
	EntityManager::ForEachChild(branchNode, [&vertices, &indices, resolution](Entity child)
		{
			SimpleMeshGenerator(child, vertices, indices, resolution);
		}
	);
}
/*
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
*/
void TreeUtilities::TreeManager::BranchNodeCleaner(Entity branchEntity)
{
	BudList ob = EntityManager::GetComponentData<BudList>(branchEntity);
	delete ob.Buds;
	BranchNodeRingList rml = EntityManager::GetComponentData<BranchNodeRingList>(branchEntity);
	delete rml.Rings;

	EntityManager::ForEachChild(branchEntity, [](Entity child) {
		BranchNodeCleaner(child);
		});
}
void TreeUtilities::TreeManager::Init()
{
	_LeafArchetype = EntityManager::CreateEntityArchetype(
		"Leaf",
		Translation(), Rotation(), Scale(), LocalToWorld(),
		Connection(), TreeIndex(),
		LeafIndex(), LeafInfo());
	_BranchNodeArchetype = EntityManager::CreateEntityArchetype(
		"BranchNode",
		LocalToWorld(), Connection(),
		Illumination(), Gravity(), BranchNodeRingList(),
		BranchNodeIndex(), BranchNodeInfo(), TreeIndex(), BudList()
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
	_BranchNodeQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_BranchNodeQuery, BranchNodeInfo());
	_TreeQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TreeQuery, TreeInfo());

	_TreeSystem = Application::GetWorld()->CreateSystem<TreeSystem>(SystemGroup::SimulationSystemGroup);
	_BranchNodeSystem = Application::GetWorld()->CreateSystem<BranchNodeSystem>(SystemGroup::SimulationSystemGroup);
	_LeafSystem = Application::GetWorld()->CreateSystem<LeafSystem>(SystemGroup::SimulationSystemGroup);



	_TreeIndex.Value = 0;
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
/*
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
*/
void TreeUtilities::TreeManager::CalculateBranchNodeIllumination()
{
	std::vector<Entity> branchNodes;
	_BranchNodeQuery.ToEntityArray(&branchNodes);
	TreeManager::GetLightEstimator()->TakeSnapShot(true);
	EntityManager::ForEach<Illumination, TreeIndex>(_BranchNodeQuery, [](int i, Entity leafEntity, Illumination* illumination, TreeIndex* index) 
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
							Illumination illumination = EntityManager::GetComponentData<Illumination>(index);
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
/*
void TreeUtilities::TreeManager::GenerateLeavesForAllTrees()
{
#pragma region Create leaves for all branchNodes
	std::vector<Entity> buds;
	//_BudQuery.ToEntityArray(&buds);
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
*/

Entity TreeUtilities::TreeManager::CreateTree(MeshMaterialComponent* treeSurfaceMaterial)
{
	auto entity = EntityManager::CreateEntity(_TreeArchetype);
	TreeInfo treeInfo;
	treeInfo.GravitropismLevelVal = new std::vector<float>();
	treeInfo.ApicalDominanceTimeVal = new std::vector<float>();
	treeInfo.ApicalControlTimeVal = new std::vector<float>();
	treeInfo.ApicalControlTimeLevelVal = new std::vector<std::vector<float>>();
	treeInfo.Vertices = new std::vector<Vertex>();
	treeInfo.Indices = new std::vector<unsigned>();
	EntityManager::SetComponentData(entity, treeInfo);
	EntityManager::SetComponentData(entity, _TreeIndex);
	EntityManager::SetSharedComponent(entity, treeSurfaceMaterial);
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
	if (treeInfo.Vertices != nullptr) delete treeInfo.Vertices;
	if (treeInfo.Indices != nullptr) delete treeInfo.Indices;
	if (EntityManager::HasComponentData<BranchNodeInfo>(EntityManager::GetChildren(treeEntity).at(0))) {
		BranchNodeCleaner(EntityManager::GetChildren(treeEntity).at(0));
	}
	EntityManager::DeleteEntity(treeEntity);
}

Entity TreeUtilities::TreeManager::CreateBranchNode(TreeIndex treeIndex, Entity parentEntity)
{
	auto entity = EntityManager::CreateEntity(_BranchNodeArchetype);
	BudList ob = BudList();
	ob.Buds = new std::vector<Bud>();
	BranchNodeRingList rml = BranchNodeRingList();
	rml.Rings = new std::vector<RingMesh>();
	EntityManager::SetComponentData(entity, treeIndex);
	EntityManager::SetParent(entity, parentEntity);
	EntityManager::SetComponentData(entity, _BranchNodeIndex);
	EntityManager::SetComponentData(entity, ob);
	EntityManager::SetComponentData(entity, rml);
	_BranchNodeIndex.Value++;
	BranchNodeInfo branchInfo;
	branchInfo.MaxActivatedChildLevel = 0;
	EntityManager::SetComponentData(entity, branchInfo);
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


void TreeUtilities::TreeManager::GenerateSimpleMeshForTree(Entity treeEntity, float resolution)
{
	if (resolution <= 0.0f) {
		Debug::Error("TreeManager: Resolution must be larger than 0!");
		return;
	}
	if (!_Ready) {
		Debug::Error("TreeManager: Not initialized!");
		return;
	}
	//Prepare ring mesh.
	EntityManager::ForEach<BranchNodeInfo, BranchNodeRingList>(_BranchNodeQuery, [resolution](int i, Entity branchNode, BranchNodeInfo* info, BranchNodeRingList* list) 
		{
			if (EntityManager::HasComponentData<TreeInfo>(EntityManager::GetParent(branchNode))) return;
			std::vector<RingMesh>* rings = list->Rings;
			rings->clear();
			glm::quat parentRotation = info->ParentRotation;
			glm::vec3 parentTranslation = info->ParentTranslation;
			float parentThickness = info->ParentThickness;

			glm::vec3 scale;
			glm::quat rotation;
			glm::vec3 translation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(info->GlobalTransform, scale, rotation, translation, skew, perspective);
			
			glm::vec3 parentDir = parentRotation * glm::vec3(0, 0, -1);
			glm::vec3 dir = rotation * glm::vec3(0, 0, -1);
			glm::vec3 mainChildDir = info->MainChildRotation * glm::vec3(0, 0, -1);
			glm::vec3 fromDir = info->IsMainChild ? (parentDir + dir) / 2.0f : parentDir;
			dir = (dir + mainChildDir) / 2.0f;
#pragma region Subdivision branch here.
			auto distance = glm::distance(parentTranslation, translation);
			int amount = distance / ((info->Thickness + parentThickness) * resolution * glm::pi<float>() * glm::pi<float>()); //distance / ((fromRadius + radius) / 2.0f);
			if (amount % 2 != 0) amount++;
			BezierCurve curve = BezierCurve(parentTranslation, parentTranslation + distance / 3.0f * fromDir, translation - distance / 3.0f * dir, translation);
			float posStep = 1.0f / (float)amount;
			glm::vec3 dirStep = (dir - fromDir) / (float)amount;
			float radiusStep = (info->Thickness - parentThickness) / (float)amount;

			list->NormalDir = fromDir == dir ? glm::cross(dir, glm::vec3(0, 0, 1)) : glm::cross(fromDir, dir);

			for (int i = 1; i < amount; i++) {
				rings->push_back(RingMesh(
					curve.GetPoint(posStep * (i - 1)), curve.GetPoint(posStep * i),
					fromDir + (float)(i - 1) * dirStep, fromDir + (float)i * dirStep,
					parentThickness + (float)(i - 1) * radiusStep, parentThickness + (float)i * radiusStep));
			}
			if (amount > 1)rings->push_back(RingMesh(curve.GetPoint(1.0f - posStep), translation, dir - dirStep, dir, info->Thickness - radiusStep, info->Thickness));
			else rings->push_back(RingMesh(parentTranslation, translation, fromDir, dir, parentThickness, info->Thickness));
#pragma endregion
		}
	);

	MeshMaterialComponent* mmc = EntityManager::GetSharedComponent<MeshMaterialComponent>(treeEntity);
	TreeInfo treeInfo = EntityManager::GetComponentData<TreeInfo>(treeEntity);
	treeInfo.Vertices->clear();
	treeInfo.Indices->clear();

	auto branchNode = EntityManager::GetChildren(treeEntity).at(0);
	//TODO: Finish mesh generation here.
	
	SimpleMeshGenerator(EntityManager::GetChildren(branchNode).at(0), *treeInfo.Vertices, *treeInfo.Indices, resolution);
	if (mmc->_Mesh != nullptr) delete mmc->_Mesh;
	mmc->_Mesh = new Mesh();
	mmc->_Mesh->SetVertices(17, *treeInfo.Vertices, *treeInfo.Indices);
}

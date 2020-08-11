#include "SpaceColonizationTreeSystem.h"
inline void SpaceColonizationTreeSystem::AddAttractionPoint(Translation translation)
{
	auto pointEntity = EntityManager::CreateEntity(_AttractionPointArchetype);
	EntityManager::SetComponentData(
		pointEntity,
		translation);

	EntityManager::SetComponentData(
		pointEntity,
		AttractionPointIndex(_AttractionPointMaxIndex)
	);
	Scale s;
	s.Value = glm::vec3(0.1f);
	EntityManager::SetComponentData(
		pointEntity,
		s
	);
	_AttractionPointMaxIndex++;
}

void SpaceColonizationTreeSystem::Grow()
{
	if (_AttractionPointQuery.GetEntityAmount() == 0) {
		//No more attraction points, return.
		Debug::Log("SpaceColonizationTreeSystem: Run out of attraction points!");
		_ToGrowIteration = 0;
		return;
	}
	unsigned newBudAmount = 0;
	//Retreve all buds;
	auto budEntityList = std::vector<Entity>();
	auto ltwList = std::vector<LocalToWorld>();
	_BudQuery.ToEntityArray(&budEntityList);
	_BudQuery.ToComponentDataArray(&ltwList);
	float attractionDistance = 25.0f;
	float removeDistance = 5.0f;
	float growDistance = 1.0f;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [](int i, Entity entity, AttractionPointCurrentStatus* status)
		{
			status->remove = false;
			status->budEntityIndex = 0;
			status->distance = 999999;
			status->growDirDelta = glm::vec3(0.0f);
		});
	//Assign points to buds;
	for (int i = 0; i < budEntityList.size(); i++) {
		auto budEntity = budEntityList[i];
		if (!budEntity.Enabled()) continue;
		BudType budType = EntityManager::GetComponentData<BudType>(budEntity);
		if (budType.Value == BudTypes::LATERAL_BUD && !budType.Searching) {
			continue;
		}
		unsigned budEntityIndex = budEntity.Index;
		glm::vec3 budPos = ltwList[i].value[3];
		EntityManager::ForEach<Translation, AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, budPos, attractionDistance, removeDistance](int i, Entity entity, Translation* translation, AttractionPointCurrentStatus* status)
			{
				float distance = glm::distance(translation->Value, budPos);
				if (distance < attractionDistance && distance < status->distance) {
					status->remove = distance < removeDistance;
					status->budEntityIndex = budEntityIndex;
					status->distance = distance;
					status->growDirDelta = translation->Value - budPos;
				}
			});
	}
	//Create new buds and remove points.
	for (int i = 0; i < budEntityList.size(); i++) {
		auto budEntity = budEntityList[i];
		if (!budEntity.Enabled()) continue;
		BudType budType = EntityManager::GetComponentData<BudType>(budEntity);
		if (budType.Value == BudTypes::LATERAL_BUD && !budType.Searching) {
			continue;
		}
		unsigned budEntityIndex = budEntity.Index;
		std::mutex ml;
		unsigned amount = 0;
		glm::vec3 growDir = glm::vec3(0.0f);
		float attractionDistance = 25.0f;
		float removeDistance = 5.0f;
		EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, &ml, &amount, &growDir](int i, Entity entity, AttractionPointCurrentStatus* status)
			{
				if (status->budEntityIndex == budEntityIndex) {
					std::lock_guard<std::mutex> lock(ml);
					amount++;
					growDir += status->growDirDelta;
				}
			});
		if (amount == 0) {
			if (budType.Value == BudTypes::APICAL_BUD && budType.Searching) {
				glm::vec3 budPos = ltwList[i].value[3];
				float minDistance = 999999;
				EntityManager::ForEach<Translation>(_AttractionPointQuery, [&amount, &ml, &growDir, budPos, &minDistance](int i, Entity entity, Translation* translation)
					{
						float distance = glm::distance(translation->Value, budPos);
						if (distance < minDistance) {
							std::lock_guard<std::mutex> lock(ml);
							minDistance = distance;
							growDir += translation->Value - budPos;
							amount++;
						}
					});

			}
			else if (budType.Value == BudTypes::LATERAL_BUD) {
				budType.Searching = false;
				EntityManager::SetComponentData(budEntityList[i], budType);
			}
		}
		else {
			if (budType.Value == BudTypes::APICAL_BUD) {
				//Stop overall search for apical bud if it already found the target.
				budType.Searching = false;
			}
			else {
				//Continue searching if we still have points around.
				budType.Searching = true;
			}
		}
		if (amount != 0) {
#pragma region Create New bud
			Entity currentBud = budEntityList[i];
			growDir = glm::normalize(growDir);

			LocalTranslation lt;
			LocalRotation rotation;
			rotation.value = glm::quat(0, 0, 0, 0);
			LocalScale ls;
			lt.value = growDir * growDistance;
			ls.value = glm::vec3(1.0f);
			//TODO: Check newbud is valid.
			auto childList = EntityManager::GetChildren(currentBud);
			bool tooClose = false;
			for (auto i : childList) {
				if (glm::distance(lt.value, EntityManager::GetComponentData<LocalTranslation>(i).value) < 0.05f) {
					tooClose = true;
				}
			}
			if (!tooClose) {
				newBudAmount++;
				auto newBud = TreeManager::CreateBud();
				EntityManager::SetComponentData(newBud, lt);
				EntityManager::SetComponentData(newBud, rotation);
				EntityManager::SetComponentData(newBud, ls);
				EntityManager::SetParent(newBud, currentBud);
				if (budType.Value == BudTypes::APICAL_BUD) {
					EntityManager::SetComponentData(newBud, budType);
					budType.Value = BudTypes::LATERAL_BUD;
					budType.Searching = true;
					EntityManager::SetComponentData(currentBud, budType);
				}
				else {
					EntityManager::SetComponentData(currentBud, budType);
					budType.Searching = true;
					EntityManager::SetComponentData(newBud, budType);
				}
				EntityManager::SetComponentData(newBud, EntityManager::GetComponentData<TreeIndex>(currentBud));
			}
#pragma endregion
		}
	}
#pragma region Remove points
	std::vector<Entity> points;
	std::mutex ml;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [&points, &ml](int i, Entity entity, AttractionPointCurrentStatus* status) {
		if (status->remove) {
			std::lock_guard<std::mutex> lock(ml);
			points.push_back(entity);
		}
		});
	for (auto i : points) {
		EntityManager::DeleteEntity(i);
	}
#pragma endregion

	if (newBudAmount == 0) {
		//No more attraction points, return.
		Debug::Log("SpaceColonizationTreeSystem: No new buds generated in this iteration, finish growing.");
		_ToGrowIteration = 0;
	}

}

void SpaceColonizationTreeSystem::OnCreate()
{
	if (!TreeManager::IsReady()) {
		Debug::Error("SpaceColonizationTreeSystem: TreeManager not initialized!");
	}

	_BudSystem = TreeManager::GetBudSystem();
	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();

	_AttractionPointArchetype = EntityManager::CreateEntityArchetype(
		Translation(), Scale(), LocalToWorld(),
		AttractionPointIndex(), AttractionPointCurrentStatus());
	_AttractionPointQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_AttractionPointQuery, AttractionPointIndex());
	_AttractionPointMaxIndex = 0;

	_AttractionPointMaterial = new Material();
	_AttractionPointMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto pointTex = new Texture2D(TextureType::DIFFUSE);
	pointTex->LoadTexture(FileIO::GetPath("Textures/green.png"), "");
	_AttractionPointMaterial->Textures2Ds()->push_back(pointTex);

	ResetEnvelope(60.0f, 20.0f, 80.0f);
	_ToGrowIteration = 0;
	Enable();
}

void SpaceColonizationTreeSystem::OnDestroy()
{
	delete _AttractionPointMaterial;
}

void SpaceColonizationTreeSystem::Update()
{
	auto pointLTWList = std::vector<LocalToWorld>();
	_AttractionPointQuery.ToComponentDataArray(&pointLTWList);
	if (pointLTWList.size() != 0)RenderManager::DrawGizmoPointInstanced(glm::vec4(1, 0, 0, 1), (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Application::GetMainCameraComponent()->Value);
}

void SpaceColonizationTreeSystem::FixedUpdate()
{
	if (_IterationFinishMark) {
		_BudSystem->RefreshParentTranslations();
		_BudSystem->RefreshConnections(0.05f);
		_IterationFinishMark = false;
	}
	if (_ToGrowIteration > 0) {
		_ToGrowIteration--;
		Grow();
		if (_ToGrowIteration == 0) _IterationFinishMark = true;
	}
}

void SpaceColonizationTreeSystem::ResetEnvelope(float radius, float minHeight, float maxHeight)
{
	_Envelope.Reset(glm::vec3(-radius / 2.0f, minHeight, -radius / 2.0f), glm::vec3(radius, maxHeight - minHeight, radius));
}

void SpaceColonizationTreeSystem::ResetEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
{
	_Envelope.Reset(spaceOffset, spaceSize);
}

void SpaceColonizationTreeSystem::ResetEnvelopeType(EnvelopeType type)
{
	_Envelope.ResetType(type);
}

void SpaceColonizationTreeSystem::PushAttractionPoints(size_t value)
{
	Translation translation;
	for (int i = 0; i < value; i++) {
		translation.Value = _Envelope.GetPoint();
		AddAttractionPoint(translation);
	}
}

void SpaceColonizationTreeSystem::PushGrowIterations(size_t iteration)
{
	EntityManager::ForEach<BudType>(_BudQuery, [](int i, Entity entity, BudType* type) {
		type->Searching = true;
		});
	_ToGrowIteration += iteration;
	_IterationFinishMark = false;
}

Entity SpaceColonizationTreeSystem::CreateTree(TreeColor color, glm::vec3 position, bool enabled)
{
	BudType type;
	type.Value = BudTypes::APICAL_BUD;
	type.Searching = true;
	auto treeEntity = TreeManager::CreateTree();
	Translation t;
	t.Value = position;
	LocalTranslation lt;
	lt.value = glm::vec3(0.0f);
	Scale s;
	s.Value = glm::vec3(1.0f);
	LocalScale ls;
	ls.value = glm::vec3(1.0f);
	EntityManager::SetComponentData(treeEntity, t);
	EntityManager::SetComponentData(treeEntity, s);
	EntityManager::SetComponentData(treeEntity, color);
	treeEntity.SetEnabled(enabled);
	auto rootBud = TreeManager::CreateBud();
	EntityManager::SetParent(rootBud, treeEntity);
	EntityManager::SetComponentData(rootBud, lt);
	EntityManager::SetComponentData(rootBud, ls);
	EntityManager::SetComponentData(rootBud, type);
	EntityManager::SetComponentData(rootBud, EntityManager::GetComponentData<TreeIndex>(treeEntity));
	return treeEntity;
}

void SpaceColonizationTreeSystem::ClearAttractionPoints()
{
	std::vector<Entity> points;
	std::mutex ml;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [&points, &ml](int i, Entity entity, AttractionPointCurrentStatus* status) {
		std::lock_guard<std::mutex> lock(ml);
		points.push_back(entity);
		});
	for (auto i : points) {
		EntityManager::DeleteEntity(i);
	}
}

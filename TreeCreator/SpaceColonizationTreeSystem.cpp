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
	s.value = glm::vec3(0.1f);
	EntityManager::SetComponentData(
		pointEntity,
		s
	);
	_AttractionPointMaxIndex++;
}

void SpaceColonizationTreeSystem::Grow()
{
	//Retreve all buds;
	auto budEntityList = std::vector<Entity>();
	auto ltwList = std::vector<LocalToWorld>();
	EntityManager::GetEntityArray(_BudQuery, &budEntityList);
	EntityManager::GetComponentDataArray(_BudQuery, &ltwList);
	float attractionDistance = 25.0f;
	float removeDistance = 5.0f;
	float growDistance = 1.0f;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [](int i, AttractionPointCurrentStatus* status)
		{
			status->remove = false;
			status->budEntityIndex = 0;
			status->distance = 999999;
		});
	//Assign points to buds;
	for (int i = 0; i < budEntityList.size(); i++) {
		unsigned budEntityIndex = budEntityList[i].Index;
		glm::vec3 budPos = ltwList[i].value[3];
		EntityManager::ForEach<Translation, AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, budPos, attractionDistance, removeDistance](int i, Translation* translation, AttractionPointCurrentStatus* status)
			{
				float distance = glm::distance(translation->value, budPos);
				if (distance < attractionDistance && distance < status->distance) {
					status->remove = distance < removeDistance;
					status->budEntityIndex = budEntityIndex;
					status->distance = distance;
					status->growDirDelta = translation->value - budPos;
				}
			});

	}
	//Create new buds and remove points.
	for (int i = 0; i < budEntityList.size(); i++) {
		BudTypes budType = EntityManager::GetComponentData<BudType>(budEntityList[i]).Value;
		unsigned budEntityIndex = budEntityList[i].Index;
		std::mutex ml;
		unsigned amount = 0;
		glm::vec3 growDir = glm::vec3(0.0f);
		float attractionDistance = 25.0f;
		float removeDistance = 5.0f;
		std::vector<Entity> points;
		EntityManager::ForEachWithEntity<AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, &points, &ml, &amount, &growDir](int i, Entity entity, AttractionPointCurrentStatus* status)
			{
				if (status->budEntityIndex == budEntityIndex) {
					ml.lock();
					amount++;
					if (status->remove) {
						points.push_back(entity);
					}
					growDir += status->growDirDelta;
					ml.unlock();
				}
			});
		if (amount == 0 && budType == BudTypes::APICAL_BUD)
		{
			amount = 1;
			glm::vec3 budPos = ltwList[i].value[3];
			float minDistance = 999999;
			EntityManager::ForEach<Translation>(_AttractionPointQuery, [&ml, &growDir, budPos, &minDistance](int i, Translation* translation)
				{
					float distance = glm::distance(translation->value, budPos);
					if (distance < minDistance) {
						ml.lock();
						minDistance = distance;
						growDir += translation->value - budPos;
						ml.unlock();
					}
				});
		}
		if (amount != 0) {
#pragma region Create New bud
			Entity currentBud = budEntityList[i];
			growDir = glm::normalize(growDir);
			auto newBud = EntityManager::CreateEntity(_BudArchetype);
			LocalTranslation translation;
			LocalRotation rotation;
			rotation.value = glm::quat(0, 0, 0, 0);
			LocalScale ls;
			translation.value = growDir * growDistance;
			ls.value = glm::vec3(1.0f);
			EntityManager::SetComponentData(newBud, translation);
			EntityManager::SetComponentData(newBud, rotation);
			EntityManager::SetComponentData(newBud, ls);
			EntityManager::SetParent(newBud, currentBud);
			if (budType == BudTypes::APICAL_BUD) {
				BudType type;
				type.Value = BudTypes::LATERAL_BUD;
				EntityManager::SetComponentData(currentBud, type);
				type.Value = BudTypes::APICAL_BUD;
				EntityManager::SetComponentData(newBud, type);
			}
#pragma endregion
#pragma region Remove Attraction Points
			for (auto p : points) EntityManager::DeleteEntity(p);
#pragma endregion
		}

	}
}

void SpaceColonizationTreeSystem::OnCreate()
{
	_TreeBudSystem = _World->GetSystem<TreeBudSystem>();

	_BudArchetype = _TreeBudSystem->GetBudArchetype();
	_LeafArchetype = _TreeBudSystem->GetLeafArchetype();
	_TreeArchetype = _TreeBudSystem->GetTreeArchetype();
	_LeafQuery = _TreeBudSystem->GetLeafQuery();
	_BudQuery = _TreeBudSystem->GetBudQuery();
	_TreeQuery = _TreeBudSystem->GetTreeQuery();

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

	BudType type;
	type.Value = BudTypes::APICAL_BUD;


	_Trees.push_back(EntityManager::CreateEntity(_TreeArchetype));
	Translation t;
	t.value = glm::vec3(-10.0f, 0.0f, 0.0f);
	LocalTranslation lt;
	lt.value = glm::vec3(0.0f);
	Scale s;
	s.value = glm::vec3(1.0f);
	LocalScale ls;
	ls.value = glm::vec3(1.0f);
	EntityManager::SetComponentData(_Trees[0], t);
	EntityManager::SetComponentData(_Trees[0], s);
	auto rootBud = EntityManager::CreateEntity(_BudArchetype);
	EntityManager::SetParent(rootBud, _Trees[0]);
	EntityManager::SetComponentData(rootBud, lt);
	EntityManager::SetComponentData(rootBud, ls);
	EntityManager::SetComponentData(rootBud, type);
	t.value = glm::vec3(10.0f, 0.0f, 0.0f);
	_Trees.push_back(EntityManager::CreateEntity(_TreeArchetype));
	EntityManager::SetComponentData(_Trees[1], t);
	EntityManager::SetComponentData(_Trees[1], s);
	rootBud = EntityManager::CreateEntity(_BudArchetype);
	EntityManager::SetParent(rootBud, _Trees[1]);
	EntityManager::SetComponentData(rootBud, lt);
	EntityManager::SetComponentData(rootBud, ls);
	EntityManager::SetComponentData(rootBud, type);

	Enable();
}

void SpaceColonizationTreeSystem::OnDestroy()
{
	delete _AttractionPointMaterial;
}

void SpaceColonizationTreeSystem::Update()
{
	auto pointLTWList = std::vector<LocalToWorld>();
	EntityManager::GetComponentDataArray(_AttractionPointQuery, &pointLTWList);
	if (pointLTWList.size() != 0)RenderManager::DrawGizmoPointInstanced(glm::vec4(1, 0, 0, 1), glm::mat4(1.0f), (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Engine::GetMainCameraComponent()->Value);
}

void SpaceColonizationTreeSystem::FixedUpdate()
{
	if (_ToGrowIteration > 0) {
		_ToGrowIteration--;
		Grow();
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

void SpaceColonizationTreeSystem::PushAttractionPoints(unsigned value)
{
	Translation translation;
	for (int i = 0; i < value; i++) {
		translation.value = _Envelope.GetPoint();
		AddAttractionPoint(translation);
	}
}

void SpaceColonizationTreeSystem::PushGrowIterations(unsigned iteration)
{
	_ToGrowIteration += iteration;
}

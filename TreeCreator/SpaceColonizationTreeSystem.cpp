#include "SpaceColonizationTreeSystem.h"
#include "Envelope.h"
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
	pointTex->LoadTexture(FileIO::GetPath("Textures/white.png"), "");
	_AttractionPointMaterial->Textures2Ds()->push_back(pointTex);

	_EnvelopeRadius = 60.0f;
	_MinHeight = 0.0f;
	_MaxHeight = 60.0f;

	Envelope envelope = Envelope(glm::vec3(-_EnvelopeRadius / 2.0f, _MinHeight, -_EnvelopeRadius / 2.0f), glm::vec3(_EnvelopeRadius, _MaxHeight - _MinHeight, _EnvelopeRadius));
	Translation translation;
	for (int i = 0; i < 10000; i++) {
		translation.value = envelope.GetPoint();
		AddAttractionPoint(translation);
	}
	_GrowTrees = true;

	_Trees.push_back(EntityManager::CreateEntity(_TreeArchetype));
	Translation t;
	t.value = glm::vec3(0.0f, 10.0f, 0.0f);
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
}

void SpaceColonizationTreeSystem::OnDestroy()
{
	delete _AttractionPointMaterial;
}

void SpaceColonizationTreeSystem::Update()
{
	auto pointLTWList = std::vector<LocalToWorld>();
	EntityManager::GetComponentDataArray(_AttractionPointQuery, &pointLTWList);
	if (pointLTWList.size() != 0)RenderManager::DrawMeshInstanced(Default::Primitives::Sphere, _AttractionPointMaterial, glm::mat4(1.0f), (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Engine::GetMainCameraComponent()->Value);
}

void SpaceColonizationTreeSystem::FixedUpdate()
{
	if (_GrowTrees) {
		Grow();
	}
}

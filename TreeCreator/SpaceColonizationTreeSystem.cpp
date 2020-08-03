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
	_AttractionPointMaxIndex++;
}

void SpaceColonizationTreeSystem::Grow()
{
	//Retreve all buds;
	auto positionList = std::vector<Translation>();
	EntityManager::GetComponentDataArray(_BudQuery, &positionList);

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
		AttractionPointIndex());
	_AttractionPointQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_AttractionPointQuery, AttractionPointIndex());
	_AttractionPointMaxIndex = 0;
}

void SpaceColonizationTreeSystem::OnDestroy()
{
}

void SpaceColonizationTreeSystem::Update()
{
	auto pointLTWList = std::vector<LocalToWorld>();
	EntityManager::GetComponentDataArray(_AttractionPointQuery, &pointLTWList);
	//RenderManager::DrawMeshInstanced(Default::Primitives::Sphere, _StarMaterial, glm::mat4(1.0f), (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Engine::GetMainCameraComponent()->Value);
}

void SpaceColonizationTreeSystem::FixedUpdate()
{
}

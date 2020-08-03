#include "TreeBudSystem.h"

void TreeCreator::TreeBudSystem::OnCreate()
{
	_LeafArchetype = _BudArchetype = EntityManager::CreateEntityArchetype(
		LocalPosition(), LocalRotation(), LocalScale(), LocalToParent(), LocalToWorld(),
		Mass(), Position(), Direction(),
		LeafIndex(),
		Phototropism(), Gravitropism()
	);
	_BudArchetype = EntityManager::CreateEntityArchetype(
		LocalPosition(), LocalRotation(), LocalScale(), LocalToParent(), LocalToWorld(),
		Mass(), Position(), Direction(),
		Radius(), BudIndex(), Iteration(), Level(),
		Phototropism(), Gravitropism()
	);
	_TreeArchetype = EntityManager::CreateEntityArchetype(
		Position(), Rotation(), Scale(), LocalToWorld(),
		TreeIndex()
	);
	_LeafQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LeafQuery, LeafIndex());
	_BudQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_BudQuery, BudIndex());
	_TreeQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TreeQuery, TreeIndex());
}

void TreeCreator::TreeBudSystem::OnDestroy()
{
}

void TreeCreator::TreeBudSystem::Update()
{

}

void TreeCreator::TreeBudSystem::FixedUpdate()
{
}

EntityArchetype TreeCreator::TreeBudSystem::GetBudArchetype()
{
	return _BudArchetype;
}

EntityArchetype TreeCreator::TreeBudSystem::GetLeafArchetype()
{
	return _LeafArchetype;
}

EntityArchetype TreeCreator::TreeBudSystem::GetTreeArchetype()
{
	return _TreeArchetype;
}

EntityQuery TreeCreator::TreeBudSystem::GetBudQuery()
{
	return _BudQuery;
}

EntityQuery TreeCreator::TreeBudSystem::GetTreeQuery()
{
	return _TreeQuery;
}

EntityQuery TreeCreator::TreeBudSystem::GetLeafQuery()
{
	return _LeafQuery;
}

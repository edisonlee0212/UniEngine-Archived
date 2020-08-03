#include "TreeBudSystem.h"

void TreeCreator::TreeBudSystem::OnCreate()
{
	_LeafArchetype = _BudArchetype = EntityManager::CreateEntityArchetype(
		LocalTranslation(), LocalRotation(), LocalScale(), LocalToParent(), LocalToWorld(),
		Mass(), Position(), Direction(),
		LeafIndex(),
		Phototropism(), Gravitropism()
	);
	_BudArchetype = EntityManager::CreateEntityArchetype(
		LocalTranslation(), LocalRotation(), LocalScale(), LocalToParent(), LocalToWorld(),
		Mass(), Position(), Direction(),
		Radius(), BudIndex(), Iteration(), Level(),
		Phototropism(), Gravitropism()
	);
	_TreeArchetype = EntityManager::CreateEntityArchetype(
		Translation(), Rotation(), Scale(), LocalToWorld(),
		TreeIndex()
	);
	_LeafQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LeafQuery, LeafIndex());
	_BudQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_BudQuery, BudIndex());
	_TreeQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TreeQuery, TreeIndex());

	_BudMaterial = new Material();
	_BudMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto pointTex = new Texture2D(TextureType::DIFFUSE);
	pointTex->LoadTexture(FileIO::GetPath("Textures/red.png"), "");
	_BudMaterial->Textures2Ds()->push_back(pointTex);

	_DrawBuds = true;
}

void TreeCreator::TreeBudSystem::OnDestroy()
{
}

void TreeCreator::TreeBudSystem::Update()
{
	if (_DrawBuds) {
		auto pointLTWList = std::vector<LocalToWorld>();
		EntityManager::GetComponentDataArray(_BudQuery, &pointLTWList);
		if (pointLTWList.size() != 0)RenderManager::DrawMeshInstanced(Default::Primitives::Sphere, _BudMaterial, glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Engine::GetMainCameraComponent()->Value);
	}
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

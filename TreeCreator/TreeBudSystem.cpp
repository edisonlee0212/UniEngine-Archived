#include "TreeBudSystem.h"
#include "TreeManager.h"
void TreeCreator::TreeBudSystem::OnCreate()
{
	_LeafArchetype = _BudArchetype = EntityManager::CreateEntityArchetype(
		LocalTranslation(), LocalRotation(), LocalScale(), LocalToParent(), LocalToWorld(),
		Mass(), Position(), Direction(), ParentTranslation(), Connection(), TreeIndex(),
		LeafIndex(), LeafType(),
		Phototropism(), Gravitropism()
	);
	_BudArchetype = EntityManager::CreateEntityArchetype(
		LocalTranslation(), LocalRotation(), LocalScale(), LocalToParent(), LocalToWorld(),
		Mass(), Position(), Direction(), ParentTranslation(), Connection(),
		Radius(), BudIndex(), Iteration(), Level(), BudType(), TreeIndex(),
		Phototropism(), Gravitropism()
	);
	_TreeArchetype = EntityManager::CreateEntityArchetype(
		Translation(), Rotation(), Scale(), LocalToWorld(),
		TreeIndex(), TreeType(), TreeColor()
	);

	

	_LeafQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LeafQuery, LeafType());
	_BudQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_BudQuery, BudType());
	_TreeQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TreeQuery, TreeType());
	_ParentTranslationQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_ParentTranslationQuery, ParentTranslation());
	_ConnectionQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_ConnectionQuery, Connection());

	TreeManager::Init(_TreeQuery);

	_BudMaterial = new Material();
	_BudMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto pointTex = new Texture2D(TextureType::DIFFUSE);
	pointTex->LoadTexture(FileIO::GetPath("Textures/red.png"), "");
	_BudMaterial->Textures2Ds()->push_back(pointTex);

	_DrawBuds = true;
	_DrawConnections = true;
	Enable();
}

void TreeCreator::TreeBudSystem::OnDestroy()
{
}

void TreeCreator::TreeBudSystem::Update()
{
	std::vector<TreeIndex> treeIndices;
	_TreeQuery.ToComponentDataArray(&treeIndices);
	std::vector<TreeColor> treeColors;
	_TreeQuery.ToComponentDataArray(&treeColors);
	if (_DrawBuds) {
		for (int i = 0; i < treeIndices.size(); i++) {
			auto pointLTWList = std::vector<LocalToWorld>();
			_BudQuery.ToComponentDataArray(treeIndices[i], &pointLTWList);
			if (pointLTWList.size() != 0)RenderManager::DrawGizmoCubeInstanced(treeColors[i].BudColor, (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Engine::GetMainCameraComponent()->Value, glm::mat4(1.0f), 0.1f);
		}
	}
	if (_DrawConnections) {
		for (int i = 0; i < treeIndices.size(); i++) {
			auto connectionLTWList = std::vector<Connection>();
			_BudQuery.ToComponentDataArray(treeIndices[i], &connectionLTWList);
			if (connectionLTWList.size() != 0)RenderManager::DrawGizmoCubeInstanced(treeColors[i].ConnectionColor, (glm::mat4*)connectionLTWList.data(), connectionLTWList.size(), Engine::GetMainCameraComponent()->Value, glm::mat4(1.0f), 1.0f);
		}
	}
}

void TreeCreator::TreeBudSystem::FixedUpdate()
{
}

void TreeCreator::TreeBudSystem::RefreshParentTranslations()
{
	EntityManager::ForEachWithEntity<ParentTranslation>(_ParentTranslationQuery, [](int i, Entity entity, ParentTranslation* pt) {
		Entity pe = EntityManager::GetParent(entity);
		pt->Value = EntityManager::GetComponentData<LocalToWorld>(pe).value[3];
		});
}

void TreeCreator::TreeBudSystem::RefreshConnections(float lineWidth)
{
	EntityManager::ForEach<ParentTranslation, LocalToWorld, Connection>(_ConnectionQuery, [lineWidth](int i, ParentTranslation* pt, LocalToWorld* ltw, Connection* c) {
		glm::vec3 pos = ltw->value[3];
		glm::vec3 diff = pos - pt->Value;
		glm::quat rotation = glm::quatLookAt(diff, glm::vec3(0, 1, 0));
		c->Value = glm::translate((pos + pt->Value) / 2.0f) * glm::mat4_cast(rotation) * glm::scale(glm::vec3(lineWidth, lineWidth, glm::distance(pos, pt->Value) / 2.0f));
		});
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

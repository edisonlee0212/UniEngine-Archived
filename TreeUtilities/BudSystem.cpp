#include "pch.h"
#include "BudSystem.h"
#include "TreeManager.h"
inline void TreeUtilities::BudSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Bud System", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Bud Amount: %d ", _BudQuery.GetEntityAmount());
		ImGui::Separator();
		ImGui::InputFloat("Bud Connection Width", &_ConnectionWidth);
		if (ImGui::Button("Regenerate connections")) {
			RefreshConnections();
		}
		ImGui::Separator();
		ImGui::CheckboxFlags("Draw Buds", &_ConfigFlags, BudSystem_DrawBuds);
		ImGui::CheckboxFlags("Draw Connections", &_ConfigFlags, BudSystem_DrawConnections);
	}
	ImGui::End();
}
void TreeUtilities::BudSystem::OnCreate()
{
	_BudEntities.clear();
	_BudQuery.ToEntityArray(&_BudEntities);

	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();

	_ParentTranslationQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_ParentTranslationQuery, Direction());
	_ConnectionQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_ConnectionQuery, Connection());

	_BudMaterial = new Material();
	_BudMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto pointTex = new Texture2D(TextureType::DIFFUSE);
	pointTex->LoadTexture(FileIO::GetPath("Textures/red.png"), "");
	_BudMaterial->Textures2Ds()->push_back(pointTex);

	_BudLTWList = std::vector<LocalToWorld>();
	_ConnectionList = std::vector<Connection>();

	_ConfigFlags = 0;
	_ConfigFlags += BudSystem_DrawBuds;
	_ConfigFlags += BudSystem_DrawConnections;
	Enable();
}

void TreeUtilities::BudSystem::OnDestroy()
{
}

void TreeUtilities::BudSystem::Update()
{
	_BudEntities.clear();
	_BudQuery.ToEntityArray(&_BudEntities);

	std::vector<TreeIndex> treeIndices;
	_TreeQuery.ToComponentDataArray(&treeIndices);
	std::vector<TreeColor> treeColors;
	_TreeQuery.ToComponentDataArray(&treeColors);
	auto treeEntities = TreeManager::GetTreeSystem()->GetTreeEntities();
	if (_ConfigFlags & BudSystem_DrawBuds) {
		for (int i = 0; i < treeEntities->size(); i++) {
			if (treeEntities->at(i).Enabled()) {
				_BudLTWList.clear();
				_BudQuery.ToComponentDataArray(treeIndices[i], &_BudLTWList);
				if (_BudLTWList.size() != 0)RenderManager::DrawGizmoCubeInstanced(treeColors[i].BudColor, (glm::mat4*)_BudLTWList.data(), _BudLTWList.size(), Application::GetMainCameraComponent()->Value, glm::mat4(1.0f), 0.1f);
			}

		}
	}
	if (_ConfigFlags & BudSystem_DrawConnections) {
		for (int i = 0; i < treeEntities->size(); i++) {
			if (treeEntities->at(i).Enabled()) {
				_ConnectionList.clear();
				_BudQuery.ToComponentDataArray(treeIndices[i], &_ConnectionList);
				if (_ConnectionList.size() != 0)RenderManager::DrawGizmoCubeInstanced(treeColors[i].ConnectionColor, (glm::mat4*)_ConnectionList.data(), _ConnectionList.size(), Application::GetMainCameraComponent()->Value, glm::mat4(1.0f), 1.0f);
			}
		}
	}
	DrawGUI();
}

void TreeUtilities::BudSystem::FixedUpdate()
{
}

void TreeUtilities::BudSystem::RefreshDirection()
{
	EntityManager::ForEach<Direction, Translation>(_ParentTranslationQuery, [](int i, Entity entity, Direction* d, Translation* t) {
		Entity pe = EntityManager::GetParent(entity);
		d->Value = t->Value - EntityManager::GetComponentData<Translation>(pe).Value;
		});
}

void TreeUtilities::BudSystem::RefreshConnections()
{
	RefreshDirection();
	float lineWidth = _ConnectionWidth;
	EntityManager::ForEach<Direction, LocalToWorld, Connection>(_ConnectionQuery, [lineWidth](int i, Entity entity, Direction* d, LocalToWorld* ltw, Connection* c) {
		glm::vec3 pos = ltw->Value[3];
		glm::vec3 diff = d->Value;
		glm::quat rotation = glm::quatLookAt(diff, glm::vec3(0, 1, 0));
		if (glm::any(glm::isnan(rotation))) {
			rotation = glm::quatLookAt(diff, glm::vec3(0, 0, 1));
		}
		c->Value = glm::translate(pos - (d->Value) / 2.0f) * glm::mat4_cast(rotation) * glm::scale(glm::vec3(lineWidth, lineWidth, glm::distance(glm::vec3(0), d->Value) / 2.0f));
		});
}

std::vector<Entity>* TreeUtilities::BudSystem::GetBudEntities()
{
	return &_BudEntities;
}


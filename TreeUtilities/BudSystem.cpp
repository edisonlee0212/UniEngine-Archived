#include "pch.h"
#include "BudSystem.h"
#include "TreeManager.h"
inline void TreeUtilities::BudSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Bud System", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Bud Amount: %d ", _BudQuery.GetEntityAmount());
		ImGui::Separator();
		ImGui::CheckboxFlags("Draw Buds", &_ConfigFlags, BudSystem_DrawBuds);
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

	_ConnectionQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_ConnectionQuery, Connection());

	_BudMaterial = new Material();
	_BudMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto pointTex = new Texture2D(TextureType::DIFFUSE);
	pointTex->LoadTexture(FileIO::GetPath("Textures/red.png"), "");
	_BudMaterial->Textures2Ds()->push_back(pointTex);

	_BudLTWList = std::vector<LocalToWorld>();

	_ConfigFlags = 0;
	//_ConfigFlags += BudSystem_DrawBuds;
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
				if (_BudLTWList.size() != 0)RenderManager::DrawGizmoCubeInstanced(treeColors[i].BudColor, (glm::mat4*)_BudLTWList.data(), _BudLTWList.size(), Application::GetMainCameraComponent()->Value, glm::mat4(1.0f), 0.01f);
			}

		}
	}
	DrawGUI();
}

void TreeUtilities::BudSystem::FixedUpdate()
{
}


std::vector<Entity>* TreeUtilities::BudSystem::GetBudEntities()
{
	return &_BudEntities;
}


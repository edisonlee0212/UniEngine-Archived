#include "pch.h"
#include "TreeSystem.h"
#include "TreeManager.h"
void TreeUtilities::TreeSystem::BudListHelper(Entity budEntity)
{
	BudIndex index = EntityManager::GetComponentData<BudIndex>(budEntity);
	std::string title = "Bud ";
	title += std::to_string(index.Value);
	if (ImGui::TreeNodeEx(title.c_str(), (ImGuiTreeNodeFlags)ImGuiTreeNodeFlags_NoTreePushOnOpen)) {
		auto childList = EntityManager::GetChildren(budEntity);
		if (childList.size() > 1) {
			ImGui::TreePush();
		}
		for (auto childbud : childList) {
			BudListHelper(childbud);
		}
		if (childList.size() > 1) {
			ImGui::TreePop();
		}
	}
}
void TreeUtilities::TreeSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Tree System")) {
		ImGui::Text("Tree Amount: %d ", 4);
		ImGui::Separator();
	}
	ImGui::End();

	ImGui::Begin("Tree Manager");
	TreeIndex index;
	TreeColor color;
	for (auto tree : _TreeEntities) {
		index = EntityManager::GetComponentData<TreeIndex>(tree);
		color = EntityManager::GetComponentData<TreeColor>(tree);
		std::string title = "Tree ";
		title += std::to_string(index.Value);
		if (ImGui::CollapsingHeader(title.c_str())) {
			ImGui::Text("Tree Color: [%d, %d, %d]", (int)(color.BudColor.x * 256.0f), (int)(color.BudColor.y * 256.0f), (int)(color.BudColor.z * 256.0f));
			ImGui::Separator();
			Entity rootBud = EntityManager::GetChildren(tree).at(0);
			BudListHelper(rootBud);
		}
	}
	ImGui::End();

	ImGui::Begin("Tree Inspector");
	ImGui::End();
}
void TreeUtilities::TreeSystem::OnCreate()
{
	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();

	Enable();
}

void TreeUtilities::TreeSystem::OnDestroy()
{
}

void TreeUtilities::TreeSystem::Update()
{
	_TreeEntities.clear();
	_TreeQuery.ToEntityArray(&_TreeEntities);


	DrawGUI();
}

void TreeUtilities::TreeSystem::FixedUpdate()
{
}

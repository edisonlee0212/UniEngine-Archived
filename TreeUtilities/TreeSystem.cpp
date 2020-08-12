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
		ImGui::Text("Tree Amount: %d ", _TreeEntities.size());
		ImGui::Separator();

	}
	ImGui::End();

	ImGui::Begin("Tree Manager");
	TreeIndex index;
	TreeColor color;
	for (auto tree : _TreeEntities) {
		index = EntityManager::GetComponentData<TreeIndex>(tree);
		std::string title = "Tree ";
		title += std::to_string(index.Value);
		bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedTreeEntity == tree ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
			_SelectedTreeEntity = tree;
		}
		if (opened) {
			color = EntityManager::GetComponentData<TreeColor>(tree);
			bool enabled = tree.Enabled();
			bool setEnabled = enabled;
			title = "Tree Color: [%d, %d, %d]##";
			title += std::to_string(index.Value);
			ImGui::Text(title.c_str(), (int)(color.BudColor.x * 256.0f), (int)(color.BudColor.y * 256.0f), (int)(color.BudColor.z * 256.0f));
			ImGui::Separator();
			title = "Enable##";
			title += std::to_string(index.Value);
			ImGui::Checkbox(title.c_str(), &setEnabled);
			if (setEnabled != enabled)tree.SetEnabled(setEnabled);

			title = "Delete##";
			title += std::to_string(index.Value);
			if (ImGui::Button(title.c_str())) {
				if (_SelectedTreeEntity == tree) _SelectedTreeEntity.Index = 0;
				EntityManager::DeleteEntity(tree);
				_TreeEntities.clear();
				_TreeQuery.ToEntityArray(&_TreeEntities);
			}
		}
		
	}
	ImGui::End();

	ImGui::Begin("Tree Inspector");
	if (!_SelectedTreeEntity.IsNull()) {
		index = EntityManager::GetComponentData<TreeIndex>(_SelectedTreeEntity);
		color = EntityManager::GetComponentData<TreeColor>(_SelectedTreeEntity);
		std::string title = "Tree ";
		title += std::to_string(index.Value);
		ImGui::Text(title.c_str());
		ImGui::Separator();

		ImGui::Separator();
		title = "Bud Hierarchy:##";
		title += std::to_string(index.Value);
		ImGui::Text(title.c_str());
		Entity rootBud = EntityManager::GetChildren(_SelectedTreeEntity).at(0);
		BudListHelper(rootBud);
		ImGui::Separator();
	}
	ImGui::End();
}
void TreeUtilities::TreeSystem::OnCreate()
{
	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();


	_SelectedTreeEntity.Version = _SelectedTreeEntity.Index = 0;

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

std::vector<Entity>* TreeUtilities::TreeSystem::GetTreeEntities()
{
	return &_TreeEntities;
}

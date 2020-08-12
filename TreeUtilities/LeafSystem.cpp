#include "pch.h"
#include "LeafSystem.h"
#include "TreeManager.h"
void TreeUtilities::LeafSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Leaf System")) {
		ImGui::Text("Leaf Amount: %d ", _LeafEntities.size());
		ImGui::Separator();
	}
	ImGui::End();
}
void TreeUtilities::LeafSystem::OnCreate()
{
	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();

	Enable();
}

void TreeUtilities::LeafSystem::OnDestroy()
{
}

void TreeUtilities::LeafSystem::Update()
{
	_LeafEntities.clear();
	_LeafQuery.ToEntityArray(&_LeafEntities);

	DrawGUI();
}

void TreeUtilities::LeafSystem::FixedUpdate()
{
}

std::vector<Entity>* TreeUtilities::LeafSystem::GetTreeEntities()
{
	return &_LeafEntities;
}

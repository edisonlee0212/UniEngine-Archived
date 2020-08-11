#include "pch.h"
#include "LeafSystem.h"
#include "TreeManager.h"
void TreeUtilities::LeafSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Leaf System")) {
		ImGui::Text("Leaf Amount: %d ", 0);
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
	DrawGUI();
}

void TreeUtilities::LeafSystem::FixedUpdate()
{
}

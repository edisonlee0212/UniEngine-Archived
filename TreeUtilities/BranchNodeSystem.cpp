#include "pch.h"
#include "BranchNodeSystem.h"
#include "TreeManager.h"
void TreeUtilities::BranchNodeSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Branch Node System", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Branch Nodes Amount: %d ", _BranchNodeQuery.GetEntityAmount());
		ImGui::Separator();
		ImGui::InputFloat("Branch Node Connection Width", &_ConnectionWidth);
		if (ImGui::Button("Regenerate connections for Branch Nodes")) {
			RefreshConnections();
		}
		ImGui::Separator();
		ImGui::CheckboxFlags("Draw Branch Nodes", &_ConfigFlags, BranchNodeSystem_DrawBranchNodes);
		ImGui::CheckboxFlags("Draw Branch Node Connections", &_ConfigFlags, BranchNodeSystem_DrawConnections);
	}
	ImGui::End();
}

void TreeUtilities::BranchNodeSystem::OnCreate()
{
	_BranchNodeLTWList.clear();
	_BranchNodeQuery = TreeManager::GetBranchNodeQuery();
	_ConfigFlags = BranchNodeSystem_DrawBranchNodes;
	Enable();
}

void TreeUtilities::BranchNodeSystem::OnDestroy()
{
}

void TreeUtilities::BranchNodeSystem::Update()
{
	_BranchNodeLTWList.clear();
	if (_ConfigFlags & BranchNodeSystem_DrawBranchNodes) {
		_BranchNodeQuery.ToComponentDataArray(&_BranchNodeLTWList);
		if (_BranchNodeLTWList.size() != 0)RenderManager::DrawGizmoCubeInstanced(glm::vec4(0, 0, 1, 1), (glm::mat4*)_BranchNodeLTWList.data(), _BranchNodeLTWList.size(), Application::GetMainCameraComponent()->Value, glm::mat4(1.0f), 0.02f);
	}
	if (_ConfigFlags & BranchNodeSystem_DrawConnections) {
		_ConnectionList.clear();
		_BranchNodeQuery.ToComponentDataArray(&_ConnectionList);
		if (_ConnectionList.size() != 0)RenderManager::DrawGizmoCubeInstanced(glm::vec4(0.6f, 0.3f, 0, 1), (glm::mat4*)_ConnectionList.data(), _ConnectionList.size(), Application::GetMainCameraComponent()->Value, glm::mat4(1.0f), 1.0f);
	}
	DrawGUI();
}

void TreeUtilities::BranchNodeSystem::RefreshConnections()
{
	float lineWidth = _ConnectionWidth;
	EntityManager::ForEach<LocalToWorld, Rotation, Connection, BranchNodeInfo>(_BranchNodeQuery, [lineWidth](int i, Entity entity, LocalToWorld* ltw, Rotation* r, Connection* c, BranchNodeInfo* info) {
		glm::vec3 pos = ltw->Value[3];
		glm::vec3 diff = info->DistanceToParent * (r->Value * glm::vec3(0, 0, -1));
		c->Value = glm::translate(pos - diff / 2.0f) * glm::mat4_cast(r->Value) * glm::scale(glm::vec3(lineWidth, lineWidth, glm::distance(glm::vec3(0), diff) / 2.0f));
		});
}

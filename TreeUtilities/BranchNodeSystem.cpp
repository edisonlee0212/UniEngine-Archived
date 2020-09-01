#include "pch.h"
#include "BranchNodeSystem.h"
#include "TreeManager.h"

#include <gtx/matrix_decompose.hpp>

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
	_ConfigFlags = BranchNodeSystem_DrawConnections;
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
	EntityManager::ForEach<LocalToWorld, Connection, BranchNodeInfo>(_BranchNodeQuery, [lineWidth](int i, Entity entity, LocalToWorld* ltw, Connection* c, BranchNodeInfo* info) {
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(ltw->Value, scale, rotation, translation, skew, perspective);
		glm::vec3 parentTranslation = translation + (rotation * glm::vec3(0, 0, 1)) * info->DistanceToParent; //EntityManager::GetComponentData<LocalToWorld>(EntityManager::GetParent(entity)).Value[3];
		glm::mat4 rotationMat = glm::mat4_cast(rotation);
		c->Value = glm::translate((translation + parentTranslation) / 2.0f) * rotationMat * glm::scale(glm::vec3(lineWidth, lineWidth, glm::distance(translation, parentTranslation) / 2.0f));
		});
}

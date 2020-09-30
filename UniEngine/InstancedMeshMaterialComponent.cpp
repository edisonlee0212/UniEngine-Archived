#include "pch.h"
#include "InstancedMeshMaterialComponent.h"

size_t UniEngine::InstancedMeshMaterialComponent::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::InstancedMeshMaterialComponent::OnGui()
{
	ImGui::Checkbox("Cast shadow", &CastShadow);
	ImGui::Checkbox("Receive shadow", &ReceiveShadow);
	ImGui::Checkbox("Back Culling", &BackCulling);
	ImGui::Text(("Instance count: " + std::to_string(Matrices.size())).c_str());
}

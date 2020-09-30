#include "pch.h"
#include "MeshMaterialComponent.h"

size_t UniEngine::MeshMaterialComponent::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::MeshMaterialComponent::OnGui()
{
	ImGui::Checkbox("Cast shadow", &CastShadow);
	ImGui::Checkbox("Receive shadow", &ReceiveShadow);
	ImGui::Checkbox("Back Culling", &BackCulling);
}

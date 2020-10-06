#include "pch.h"
#include "InstancedMeshRenderer.h"

size_t UniEngine::InstancedMeshRenderer::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::InstancedMeshRenderer::OnGui()
{
	ImGui::Checkbox("Cast shadow", &CastShadow);
	ImGui::Checkbox("Receive shadow", &ReceiveShadow);
	ImGui::Checkbox("Back Culling", &BackCulling);
	ImGui::Text(("Instance count: " + std::to_string(Matrices.size())).c_str());
}

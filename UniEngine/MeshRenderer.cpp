#include "pch.h"
#include "MeshRenderer.h"

size_t UniEngine::MeshRenderer::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::MeshRenderer::OnGui()
{
	ImGui::Checkbox("Cast shadow", &CastShadow);
	ImGui::Checkbox("Receive shadow", &ReceiveShadow);
	ImGui::Checkbox("Back Culling", &BackCulling);
	if (Material) {
		if (ImGui::TreeNode("Material")) {
			Material->OnGui();
			ImGui::TreePop();
		}
	}
	if (Mesh) {
		if (ImGui::TreeNode("Mesh")) {
			Mesh->OnGui();
		}
	}
}

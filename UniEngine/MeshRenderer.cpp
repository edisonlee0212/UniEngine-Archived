#include "pch.h"
#include "MeshRenderer.h"

size_t UniEngine::MeshRenderer::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::MeshRenderer::OnGui()
{
	ImGui::Checkbox("Forward Rendering", &ForwardRendering);
	if(ForwardRendering){
		//Disable shadow receiving only allowed in forward rendering.
		ImGui::Checkbox("Receive shadow", &ReceiveShadow);
		ImGui::Checkbox("Enable Transparency", &Transparency);
	}
	ImGui::Checkbox("Cast shadow", &CastShadow);
	ImGui::Checkbox("Back Culling", &BackCulling);
	if (Material) {
		if (ImGui::TreeNode("Material##1")) {
			Material->OnGui();
			ImGui::TreePop();
		}
	}
	if (Mesh) {
		if (ImGui::TreeNode("Mesh##1")) {
			Mesh->OnGui();
			ImGui::TreePop();
		}
	}
}

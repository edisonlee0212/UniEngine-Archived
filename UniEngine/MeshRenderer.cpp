#include "pch.h"
#include "MeshRenderer.h"
#include "UniEngine.h"
#include "RenderManager.h"
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
			ImGui::Checkbox("Display bounds", &DisplayBound);
			if (DisplayBound)
			{
				ImGui::ColorEdit4("Color: ", (float*)(void*)&DisplayBoundColor);
				auto transform = _Owner.GetComponentData<LocalToWorld>().Value;
				RenderManager::DrawGizmoCube(DisplayBoundColor, transform * (glm::translate(Mesh->_Bound.Center) * glm::scale(Mesh->_Bound.Size)), 1);
			}
			Mesh->OnGui();
			ImGui::TreePop();
		}
	}
}

UniEngine::MeshRenderer::MeshRenderer()
{
	SetEnabled(true);
}

UniEngine::MeshRenderer::~MeshRenderer()
{
}

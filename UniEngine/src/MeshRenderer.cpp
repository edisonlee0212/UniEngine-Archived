#include "pch.h"
#include "MeshRenderer.h"
#include "UniEngine.h"
#include "RenderManager.h"

void UniEngine::MeshRenderer::RenderBound(glm::vec4& color) const
{
	const auto transform = GetOwner().GetComponentData<GlobalTransform>().Value;
	glm::vec3 size = Mesh->_Bound.Size();
	if (size.x < 0.01f) size.x = 0.01f;
	if (size.z < 0.01f) size.z = 0.01f;
	if (size.y < 0.01f) size.y = 0.01f;
	RenderManager::DrawGizmoCube(color, transform * (glm::translate(Mesh->_Bound.Center()) * glm::scale(size)), 1);
}

void UniEngine::MeshRenderer::OnGui()
{
	ImGui::Checkbox("Forward Rendering##MeshRenderer", &ForwardRendering);
	ImGui::Checkbox("Receive shadow##MeshRenderer", &ReceiveShadow);
	ImGui::Checkbox("Cast shadow##MeshRenderer", &CastShadow);
	ImGui::Text("Material:");
	ImGui::SameLine();
	EditorManager::DragAndDrop(Material);
	if (Material) {
		if (ImGui::TreeNode("Material##MeshRenderer")) {
			Material->OnGui();
			ImGui::TreePop();
		}
	}
	ImGui::Text("Mesh:");
	ImGui::SameLine();
	EditorManager::DragAndDrop(Mesh);
	if (Mesh) {
		if (ImGui::TreeNode("Mesh##MeshRenderer")) {
			ImGui::Checkbox("Display bounds##MeshRenderer", &DisplayBound);
			if (DisplayBound)
			{
				ImGui::ColorEdit4("Color:##MeshRenderer", (float*)(void*)&DisplayBoundColor);
				RenderBound(DisplayBoundColor);
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

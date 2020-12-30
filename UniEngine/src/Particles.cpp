#include "pch.h"
#include "Particles.h"
#include "UniEngine.h"
#include "RenderManager.h"

UniEngine::Particles::Particles()
{
	BoundingBox = Bound();
	SetEnabled(true);
}

void UniEngine::Particles::RecalculateBoundingBox()
{
	if(Matrices.empty())
	{
		BoundingBox.Min = glm::vec3(0.0f);
		BoundingBox.Max = glm::vec3(0.0f);
		return;
	}
	glm::vec3 minBound = glm::vec3((int)INT_MAX);
	glm::vec3 maxBound = glm::vec3((int)INT_MIN);
	auto meshBound = Mesh->GetBound();
	for(auto& i : Matrices)
	{
		glm::vec3 center = i * glm::vec4(meshBound.Center(), 1.0f);
		glm::vec3 size = glm::vec4(meshBound.Size(), 0) * i / 2.0f;
		minBound = glm::vec3(
			glm::min(minBound.x, center.x - size.x),
			glm::min(minBound.y, center.y - size.y),
			glm::min(minBound.z, center.z - size.z));

		maxBound = glm::vec3(
			glm::max(maxBound.x, center.x + size.x),
			glm::max(maxBound.y, center.y + size.y),
			glm::max(maxBound.z, center.z + size.z));
	}
	BoundingBox.Max = maxBound;
	BoundingBox.Min = minBound;
}


void UniEngine::Particles::OnGui()
{
	ImGui::Checkbox("Forward Rendering##Particles", &ForwardRendering);
	ImGui::Checkbox("Receive shadow##Particles", &ReceiveShadow);
	ImGui::Checkbox("Cast shadow##Particles", &CastShadow);
	ImGui::Text(("Instance count:##Particles" + std::to_string(Matrices.size())).c_str());
	ImGui::Checkbox("Display bounds##Particles", &DisplayBound);
	if(ImGui::Button("Calculate bounds##Particles"))
	{
		RecalculateBoundingBox();
	}
	if (DisplayBound)
	{
		RecalculateBoundingBox();
		ImGui::ColorEdit4("Color:##Particles", (float*)(void*)&DisplayBoundColor);
		auto transform = GetOwner().GetComponentData<GlobalTransform>().Value;
		RenderManager::DrawGizmoCube(DisplayBoundColor, transform * glm::translate(BoundingBox.Center()) * glm::scale(BoundingBox.Size()), 1);
	}
	ImGui::Text("Material:##Particles");
	ImGui::SameLine();
	EditorManager::DragAndDrop(Material);
	if (Material) {
		if (ImGui::TreeNode("Material##Particles")) {
			Material->OnGui();
			ImGui::TreePop();
		}
	}
	ImGui::Text("Mesh:##Particles");
	ImGui::SameLine();
	EditorManager::DragAndDrop(Mesh);
	if (Mesh) {
		if (ImGui::TreeNode("Mesh##Particles")) {
			Mesh->OnGui();
			ImGui::TreePop();
		}
	}
}

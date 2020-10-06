#include "pch.h"
#include "InstancedMeshRenderer.h"

void UniEngine::InstancedMeshRenderer::RecalculateBoundingBox()
{
	glm::vec3 minBound = glm::vec3((int)INT_MAX);
	glm::vec3 maxBound = glm::vec3((int)INT_MIN);
	auto meshBound = Mesh->GetBound();
	for(auto& i : Matrices)
	{
		glm::vec3 center = i * glm::vec4(meshBound.Center, 1.0f);
		glm::vec3 size = glm::vec4(meshBound.Size, 0) * i / 2.0f;
		minBound = glm::vec3(
			glm::min(minBound.x, center.x - size.x),
			glm::min(minBound.y, center.y - size.y),
			glm::min(minBound.z, center.z - size.z));

		maxBound = glm::vec3(
			glm::max(maxBound.x, center.x + size.x),
			glm::max(maxBound.y, center.y + size.y),
			glm::max(maxBound.z, center.z + size.z));
	}
	BoundingBox.Size = (maxBound - minBound) / 2.0f;
	BoundingBox.Center = (maxBound + minBound) / 2.0f;
	BoundingBox.Radius = glm::length(BoundingBox.Size);
}

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

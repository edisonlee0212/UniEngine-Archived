#include "pch.h"
#include "CameraComponent.h"

std::size_t UniEngine::CameraComponent::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::CameraComponent::OnGui()
{
	ImGui::Checkbox("Skybox", &DrawSkyBox);
	Value->OnGui();
}

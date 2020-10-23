#include "pch.h"
#include "CameraComponent.h"

void UniEngine::CameraComponent::OnGui()
{
	ImGui::Checkbox("Skybox", &DrawSkyBox);
	Value->OnGui();
}

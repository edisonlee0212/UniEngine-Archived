#include "pch.h"
#include "CameraComponent.h"

void UniEngine::CameraComponent::OnGui()
{
	ImGui::Checkbox("Skybox", &DrawSkyBox);
	if(!DrawSkyBox)
	{
		ImGui::ColorEdit3("Clear Color", (float*)(void*)&ClearColor);
	}
	Value->OnGui();
}

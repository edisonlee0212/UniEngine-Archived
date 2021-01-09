#include "pch.h"
#include "DirectionalLight.h"

void UniEngine::DirectionalLight::Init()
{
	SetEnabled(true);
}

void UniEngine::DirectionalLight::OnGui()
{
	ImGui::Checkbox("Cast Shadow", &CastShadow);
	ImGui::ColorEdit3("Color", &diffuse[0]);
	ImGui::DragFloat("Intensity", &diffuseBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::DragFloat("Bias", &bias, 0.001f, 0.0f, 999.0f);
	ImGui::DragFloat("Normal Offset", &normalOffset, 0.001f, 0.0f, 999.0f);
	ImGui::DragFloat("Light Size", &lightSize, 0.01f, 0.0f, 999.0f);
}

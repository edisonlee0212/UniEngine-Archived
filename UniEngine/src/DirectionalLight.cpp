#include "pch.h"
#include "DirectionalLight.h"

void UniEngine::DirectionalLight::OnGui()
{
	ImGui::ColorEdit3("Diffuse", &diffuse[0]);
	ImGui::DragFloat("Diffuse Brightness", &diffuseBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::ColorEdit3("Specular", &specular[0]);
	ImGui::DragFloat("Specular Brightness", &specularBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::DragFloat("Bias", &bias, 0.001f, 0.0f, 999.0f);
	ImGui::DragFloat("Normal Offset", &normalOffset, 0.001f, 0.0f, 999.0f);
	ImGui::DragFloat("Light Size", &lightSize, 0.01f, 0.0f, 999.0f);
}

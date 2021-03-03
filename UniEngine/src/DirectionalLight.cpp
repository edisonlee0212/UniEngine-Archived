#include "pch.h"
#include "DirectionalLight.h"

void UniEngine::DirectionalLight::Init()
{
	SetEnabled(true);
}

void UniEngine::DirectionalLight::OnGui()
{
	ImGui::Checkbox("Cast Shadow", &m_castShadow);
	ImGui::ColorEdit3("Color", &m_diffuse[0]);
	ImGui::DragFloat("Intensity", &m_diffuseBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::DragFloat("Bias", &m_bias, 0.001f, 0.0f, 999.0f);
	ImGui::DragFloat("Normal Offset", &m_normalOffset, 0.001f, 0.0f, 999.0f);
	ImGui::DragFloat("Light Size", &m_lightSize, 0.01f, 0.0f, 999.0f);
}

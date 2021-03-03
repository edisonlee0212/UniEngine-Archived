#include "pch.h"
#include "SpotLight.h"
using namespace UniEngine;

void SpotLight::OnGui()
{
	ImGui::Checkbox("Cast Shadow", &m_castShadow);
	ImGui::ColorEdit3("Color", &m_diffuse[0]);
	ImGui::DragFloat("Intensity", &m_diffuseBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::DragFloat("Bias", &m_bias, 0.001f, 0.0f, 999.0f);

	ImGui::DragFloat("Constant", &m_constant, 0.01f, 0.0f, 999.0f);
	ImGui::DragFloat("Linear", &m_linear, 0.001f, 0, 1, "%.3f");
	ImGui::DragFloat("Quadratic", &m_quadratic, 0.001f, 0, 10, "%.4f");

	ImGui::DragFloat("Inner Degrees", &m_innerDegrees, 0.1f, 0.0f, m_outerDegrees);
	ImGui::DragFloat("Outer Degrees", &m_outerDegrees, 0.1f, m_innerDegrees, 180.0f);
	ImGui::DragFloat("Light Size", &m_lightSize, 0.01f, 0.0f, 999.0f);
}

void SpotLight::Init()
{
	SetEnabled(true);
}
